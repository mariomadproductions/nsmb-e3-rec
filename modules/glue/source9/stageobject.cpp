#include <nsmb/extra/assert.hpp>
#include <nsmb/extra/log.hpp>

#include "glue/stageobject.hpp"
#include "glue/object.hpp"
#include "glue/level.hpp"

// Defines GLUE_STAGEOBJECT_NONE when no module declares a stage: variant, in
// which case there is no table and nothing below has anything to do.
#include "generated/glue/extended_stageobjects.hpp"
#include "generated/glue/runtime_modules.hpp"

#ifndef GLUE_STAGEOBJECT_NONE

namespace Glue::StageObject {

// Extends Stage::objectInfoTable: the geometry of each extended stage object
// ID. The rows are copied rather than pointed at, because the game indexes the
// table directly and the ObjectInfo a module supplies may sit in an overlay
// that is not resident.
ObjectInfo extObjInfos[moduleStageObjectCount];

// Extends Stage::objectIDTable: which object (0x182 + n) each extended stage
// object ID spawns. beforeLoadSprites writes every slot the level uses,
// unresolved ones included -- those get NoActorID.
u16 extObjIDs[moduleStageObjectCount];

// Extends Stage::objectBankTable. Module objects are compiled into module code
// rather than into one of the game's ten object-bank overlays, so they require
// no bank: bank 0 is what loadAreaObjects reads as "no requirement", and slot is
// unused at bank 0. Every module object gives the same answer, so getObjectBank
// returns this one entry for all of them.
const ObjectBank moduleObjectBank = { 0, 0 };

static const ModuleStageObjectInfo* findModuleStageObject(u32 hash)
{
	for (u32 i = 0; i < moduleStageObjectCount; i++) {
		if (moduleStageObjectInfos[i].hash == hash) {
			return &moduleStageObjectInfos[i];
		}
	}
	return nullptr;
}

void beforeLoadSprites()
{
	// Entry n is the hash of the object that stage object ID BaseObjectID + n
	// spawns. A level that places no module object omits the key, and has no
	// extended ID in its sprites block for anything to read.
	auto stageObjHashesOpt = Level::get<"glue.stageObjects">();
	if (!stageObjHashesOpt) {
		return;
	}

	Level::SizedArray<u32> stageObjHashesArray = stageObjHashesOpt.value();

	u32 stageObjHashCount = stageObjHashesArray.size;
	const u32* stageObjHashes = stageObjHashesArray.values;

#ifdef NTR_DEBUG
	// An empty array means the generator wrote a key it should have omitted.
	if (stageObjHashCount == 0) {
		ntr_terminate(
			"glue.stageObjects array is present but empty.\n"
			"This is not allowed. If there are no custom stage objects, the array should be omitted entirely.\n"
			"Check your level or data generator to ensure glue.stageObjects is only created when it contains objects."
		);
		return;
	}

	if (stageObjHashCount > moduleStageObjectCount) {
		ntr_terminate(
			"glue.stageObjects names %u objects but this build only has %u.\n"
			"The level was made for a build with more module stage objects than this one.\n",
			stageObjHashCount, moduleStageObjectCount
		);
	}
#endif

	for (u32 i = 0; i < stageObjHashCount; i++) {

		u32 hash = stageObjHashes[i];

		const ModuleStageObjectInfo* modObjInfo = findModuleStageObject(hash);

		if (modObjInfo == nullptr) {
			// The hash is not in this build. loadAreaObjects still reads
			// spawnSettings out of the untouched geometry slot, but the spawn
			// paths check the ID against NoActorID before constructing
			// anything.
#ifdef NTR_DEBUG
			ntr_terminate("Unknown module stage object hash: 0x%08X\n", hash);
#endif
			extObjIDs[i] = NoActorID;
			continue;
		}

#ifdef GLUE_STAGEOBJECT_DEBUG
		Log::print("Loading custom stage object %s as %u\n", modObjInfo->name, BaseObjectID + i);
#endif

#ifndef GLUE_RUNTIME_NONE
		// An object in a runtime module has no profile until the module is
		// loaded. One that cannot be loaded spawns nothing, as an unknown
		// hash does; require has already said why in a debug build.
		if (modObjInfo->runtime != Runtime::None && !Runtime::require(modObjInfo->runtime)) {
			extObjIDs[i] = NoActorID;
			continue;
		}
#endif

		// By halfwords: ObjectInfo is only halfword-aligned, and a word copy
		// from one that is not word-aligned starts two bytes early.
		MI_CpuCopy16(modObjInfo->info, &extObjInfos[i], sizeof(ObjectInfo));
		extObjIDs[i] = modObjInfo->objectId;
	}

#ifdef NTR_DEBUG
	// The placements are in the vanilla block, which the loop above never looks
	// at, so an ID with no hash behind it reaches the game as an untouched
	// slot. Catching that means walking the sprites block, hence debug-only.
	//
	// stageBlocks.stageObjs is read directly rather than through
	// Stage::getBlock: StageBlocks::operator[] returns the address of the
	// pointer rather than the pointer.
	u32 placedCount = Stage::getBlockElementCount(u32(StageBlockID::StageObjs));
	const ::StageObject* placed = Stage::stageBlocks.stageObjs;

	for (u32 i = 0; i < placedCount; i++) {
		u16 id = placed[i].id;
		if (id >= BaseObjectID && u32(id - BaseObjectID) >= stageObjHashCount) {
			ntr_terminate(
				"Stage object %u places ID %u, but glue.stageObjects only defines up to %u.\n",
				i, id, BaseObjectID + stageObjHashCount - 1
			);
		}
	}
#endif
}

// Stage::loadStageObjsResources (0x0201F3A4) calls loadResources once for every
// stage object ID the area places. It marks the placed IDs in a byte array on
// its stack and then walks the array, both loops bounded by the literal at
// 0x0201F458. Three things kept it from working for module objects, and each
// is patched in place:
//
//   - the bound is 326, so module IDs were never walked: it becomes idCount,
//     and the array grows to match;
//   - the marking loop does not check the ID, so a placed ID of 332 or more
//     wrote past the array: it now skips those, beforeLoadSprites having
//     already stopped a debug build on them;
//   - the profile comes from currentProcessTable alone, which ends before the
//     module objects: a stub picks the table.

constexpr u32 loadResourcesIDCount = BaseObjectID + moduleStageObjectCount;

// Keeps sp 8-aligned under the five registers the function pushes, as the
// game's 332 does for 326 entries.
constexpr u32 loadResourcesStackSize = ((loadResourcesIDCount + 4 + 7) & ~7u) - 4;

// sub/add sp, sp, #imm take an 8-bit immediate rotated right by 30 here, which
// reaches every multiple of 4 up to 1020.
static_assert(loadResourcesStackSize <= 1020);

ncp_over(0x0201F3A8) const u32 loadResourcesSubSp = 0xE24DDF00 | (loadResourcesStackSize >> 2); // sub sp, sp, #size
ncp_over(0x0201F450) const u32 loadResourcesAddSp = 0xE28DDF00 | (loadResourcesStackSize >> 2); // add sp, sp, #size
ncp_over(0x0201F458) const u32 loadResourcesBound = loadResourcesIDCount;

// The marking loop, rewritten in its own eight slots. Storing through sp frees
// the instruction that pointed r0 at the array, which loads the bound into r6
// instead; the function reloads r6 with the same value after the loop.
ncp_asmfunc void loadResourcesMarkPlaced() {asm(R"(
ncp_over(0x0201F3E4)
	ldr		r6, [pc, #0x6C] @ the bound at 0x0201F458
	mov		r2, #1
1:	ldrh	r1, [r5], #12
	add		r3, r3, #1
	cmp		r1, r6
	strblo	r2, [sp, r1]
	cmp		r3, r4
	blt		1b
ncp_endover()
)");}

// Replaces ldr r1, [r7], with the actor ID in r0, &currentProcessTable in r7
// and r2 free. Returns to the game's null check with loadResources in r0.
//
// A null row is an object in a runtime module that did not load, and
// beforeLoadSprites gave it NoActorID, but check anyway: this is the one place
// that reads the profile before anything spawns.
//
// 0x182 is not an encodable immediate, so the subtraction is split.
ncp_jump(0x0201F428)
NTR_NAKED void loadResourcesPickProfile() {asm(R"(
	sub		r2, r0, #0x180
	subs	r2, r2, #0x2
	ldrmi	r1, [r7]
	ldrmi	r0, [r1, r0, lsl #2]
	ldrpl	r1, =_ZN4Glue6Object12currentExtPTE
	ldrpl	r1, [r1]
	ldrpl	r0, [r1, r2, lsl #2]
	cmp		r0, #0
	ldrne	r0, [r0, #8]
	b		0x0201F434
)");}

} // namespace Glue::StageObject

// ---------------------------------------------------------------------------
// Making the game read the extensions
//
// Three tables are indexed by stage object ID, and a placed module object needs
// all three: objectBankTable decides whether loadAreaObjects considers it at
// all, objectIDTable says which class to spawn, and objectInfoTable carries the
// geometry. They sit contiguously and are all 326 entries -- see BaseObjectID.
//
// Every read site uses one of two idioms, and each patch replaces the single
// instruction that combines base and index, choosing the base first:
//
//   objectInfoTable   ldr <base>,=table ; mov <k>,#20 ; mla <dest>,<id>,<k>,<base>
//   objectIDTable     ldr <base>,=table ; mov <idx>,<id>,lsl #1 ; ldrh <dest>,[<base>,<idx>]
//
// The extension pointer is pre-biased by BaseObjectID entries, so the untouched
// index arithmetic lands on element zero. The ID register is left alone; only
// the base changes.
//
// The scratch register is the replaced instruction's own destination, which is
// dead on entry by definition. Where destination and base are the same register
// the stub reloads the base, so clobbering it costs nothing.
//
// 326 is not an encodable ARM data-processing immediate (nor are 324 and 325),
// so the mla sites split the comparison: subtract 320, which is encodable, and
// compare the remainder against 6 -- signed, because an ID below 320 makes the
// difference negative. The ldrh sites compare the already-doubled index against
// 652 instead, which is encodable, and unsigned, since a doubled u16 cannot go
// negative.
//
// Every stub clobbers the flags. That is safe at all thirteen sites: each one's
// next conditional instruction is preceded by its own flag-setting instruction,
// or by a bl, across which the flags are caller-clobbered anyway.
//
// Addresses are Ghidra addresses; overlay_offsets[0] and overlay_offsets[54] are
// both 0, so no translation applies. The stubs live in main ARM9 -- overlay 0
// sits at exactly its 0x33C00 maxsize and has no room for them -- which works
// because NCPatcher tracks a patch's source and destination regions separately.
// ---------------------------------------------------------------------------

// The biases below are BaseObjectID * sizeof(ObjectInfo) = 326 * 20 = 6520 for
// extObjInfos, and BaseObjectID * sizeof(u16) = 652 for extObjIDs. They are
// spelled out because the assembler cannot see the C++ constants.

// --- objectInfoTable: eight sites in seven functions -----------------------

// Stage::loadAreaObjects, reading spawnSettings for the MvsL/single-player test.
ncp_jump(0x0201F804)
NTR_NAKED void extendObjectInfoLoadAreaObjectsA() {asm(R"(
	sub		r1, r0, #320
	cmp		r1, #6
	ldrlt	r1, =0x020C529C
	ldrge	r1, =(_ZN4Glue11StageObject11extObjInfosE - 6520)
	mla		r1, r0, r2, r1
	b		0x0201F804 + 4
)");}

// Stage::loadAreaObjects, reading spawnSettings for the IgnoreView test.
ncp_jump(0x0201F8F0)
NTR_NAKED void extendObjectInfoLoadAreaObjectsB() {asm(R"(
	sub		r0, r2, #320
	cmp		r0, #6
	ldrlt	r0, =0x020C529C
	ldrge	r0, =(_ZN4Glue11StageObject11extObjInfosE - 6520)
	mla		r0, r2, r1, r0
	b		0x0201F8F0 + 4
)");}

// StageEntity::spawnEntitiesOnReturn.
ncp_jump(0x0209B164, 0)
NTR_NAKED void extendObjectInfoRespawnSprites() {asm(R"(
	sub		r8, r2, #320
	cmp		r8, #6
	ldrlt	r8, =0x020C529C
	ldrge	r8, =(_ZN4Glue11StageObject11extObjInfosE - 6520)
	mla		r8, r2, r1, r8
	b		0x0209B164 + 4
)");}

// StageEntity::spawnEntitiesOnStart.
ncp_jump(0x0209B40C, 0)
NTR_NAKED void extendObjectInfoSpawnSpriteMvsL() {asm(R"(
	sub		r10, r2, #320
	cmp		r10, #6
	ldrlt	r10, =0x020C529C
	ldrge	r10, =(_ZN4Glue11StageObject11extObjInfosE - 6520)
	mla		r10, r2, r1, r10
	b		0x0209B40C + 4
)");}

// StageEntity::spawnAllEntities. The `ldr` here is hoisted out of the loop, so
// the base in r11 is shared by every ID the loop visits. The mla is what carries
// the per-iteration ID, in r1, and patching it leaves r11 as it was.
ncp_jump(0x0209B6CC, 0)
NTR_NAKED void extendObjectInfoSpawnSprites() {asm(R"(
	sub		r9, r1, #320
	cmp		r9, #6
	ldrlt	r9, =0x020C529C
	ldrge	r9, =(_ZN4Glue11StageObject11extObjInfosE - 6520)
	mla		r9, r1, r4, r9
	b		0x0209B6CC + 4
)");}

// StageEntity::spawnEntityOnBound, reading spawnOffset and viewOffset to place
// the sprite.
ncp_jump(0x0209BB80, 0)
NTR_NAKED void extendObjectInfoPlaceSprite() {asm(R"(
	sub		r6, r2, #320
	cmp		r6, #6
	ldrlt	r6, =0x020C529C
	ldrge	r6, =(_ZN4Glue11StageObject11extObjInfosE - 6520)
	mla		r6, r2, r1, r6
	b		0x0209BB80 + 4
)");}

// StageEntity::spawnEntity_1.
ncp_jump(0x0209C1AC, 0)
NTR_NAKED void extendObjectInfoSpawnObject() {asm(R"(
	sub		r4, r5, #320
	cmp		r4, #6
	ldrlt	r4, =0x020C529C
	ldrge	r4, =(_ZN4Glue11StageObject11extObjInfosE - 6520)
	mla		r4, r5, r3, r4
	b		0x0209C1AC + 4
)");}

// FUN_02168BAC, in overlay 54.
ncp_jump(0x02168BFC, 54)
NTR_NAKED void extendObjectInfoOv54() {asm(R"(
	sub		r6, r8, #320
	cmp		r6, #6
	ldrlt	r6, =0x020C529C
	ldrge	r6, =(_ZN4Glue11StageObject11extObjInfosE - 6520)
	mla		r6, r8, r12, r6
	b		0x02168BFC + 4
)");}

// --- objectIDTable: four sites ---------------------------------------------

// StageEntity::getActorID. The index is in r0, which is also the destination, so
// the base register r1 is the only scratch available -- safe, because this is a
// leaf returning in r0 and r1 is caller-saved.
ncp_jump(0x02099598, 0)
NTR_NAKED void extendObjectIDGetActorID() {asm(R"(
	cmp		r0, #652
	ldrhs	r1, =(_ZN4Glue11StageObject9extObjIDsE - 652)
	ldrh	r0, [r1, r0]
	b		0x02099598 + 4
)");}

// StageEntity::spawnEntity_2, testing the ID against NoActorID. The stub uses
// the dead destination r12 as scratch and leaves the base in r4 untouched.
ncp_jump(0x0209BF2C, 0)
NTR_NAKED void extendObjectIDSpawnSpriteA() {asm(R"(
	cmp		r5, #652
	movlo	r12, r4
	ldrhs	r12, =(_ZN4Glue11StageObject9extObjIDsE - 652)
	ldrh	r12, [r12, r5]
	b		0x0209BF2C + 4
)");}

// StageEntity::spawnEntity_2, the actual spawn.
ncp_jump(0x0209C04C, 0)
NTR_NAKED void extendObjectIDSpawnSpriteB() {asm(R"(
	cmp		r2, #652
	ldrhs	r0, =(_ZN4Glue11StageObject9extObjIDsE - 652)
	ldrh	r0, [r0, r2]
	b		0x0209C04C + 4
)");}

// StageEntity::spawnEntity_1.
ncp_jump(0x0209C18C, 0)
NTR_NAKED void extendObjectIDSpawnObject() {asm(R"(
	cmp		r3, #652
	ldrhs	r0, =(_ZN4Glue11StageObject9extObjIDsE - 652)
	ldrh	r0, [r0, r3]
	b		0x0209C18C + 4
)");}

// --- calling into beforeLoadSprites ----------------------------------------

// Stage::loadAreaObjects, right after LoadBlocks has made the level's stage
// blocks -- and so the glue block -- available, and after both early returns,
// but before anything reads one of the three tables.
//
// A plain jump rather than ncp_hook: the bridge preserves r0-r3/r12/lr, and all
// six are dead here. The bl four instructions earlier already clobbered r12 and
// lr (this function returns through a pop into pc), and r0-r3 are each written
// before they are next read, at 0x0201F6D4 through 0x0201F6E0. So the stub has
// only the replaced instruction to re-execute.
ncp_jump(0x0201F6D0)
NTR_NAKED void callBeforeLoadSprites() {asm(R"(
	bl		_ZN4Glue11StageObject17beforeLoadSpritesEv
	mov		r4, #0 // Keep replaced instruction
	b		0x0201F6D0 + 4 // Return to code
)");}

// --- objectBankTable: one site ---------------------------------------------

// StageEntity::getObjectBank, whose only caller is loadAreaObjects. It is
// `return objectBankTable + id`, so a module ID returns moduleObjectBank. r1
// already holds the vanilla base, so r2 is borrowed as scratch; both are
// caller-saved and this is a leaf.
ncp_jump(0x0209878C, 0)
NTR_NAKED void extendObjectBank() {asm(R"(
	sub		r2, r0, #320
	cmp		r2, #6
	addlt	r0, r1, r0, lsl #1
	ldrge	r0, =_ZN4Glue11StageObject16moduleObjectBankE
	b		0x0209878C + 4
)");}

#endif // GLUE_STAGEOBJECT_NONE
