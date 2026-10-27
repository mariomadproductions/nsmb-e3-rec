#pragma once

#include <nsmb/game/stage/entity.hpp>
#include <nsmb/game/stage/misc.hpp>
#include <nsmb/game/stage/layout/data/object.hpp>

#include "glue/runtime.hpp"

// The generated table is written as MODULE_OBJ rows so the editor-facing name
// can be dropped from a release build without the generator having to know
// which build it is generating for.
#ifdef GLUE_STAGEOBJECT_DEBUG
#define MODULE_OBJ(hash, objectId, runtime, info, name) { hash, objectId, runtime, info, name }
#else
#define MODULE_OBJ(hash, objectId, runtime, info, name) { hash, objectId, runtime, info }
#endif

namespace Glue::StageObject {

// Where the vanilla stage object tables end. All three hold 326 entries,
// indices 0..325, confirmed four ways:
//
//   - the reference declares `extern const u16 objectIDTable[326]`;
//   - objectBankTable (0x020C5010) ends exactly where objectInfoTable
//     (0x020C529C) begins, 326 * 2 bytes on;
//   - objectInfoTable ends at 0x020C6C14, 326 * 20 bytes on;
//   - row 325 is populated in all three, not padding.
//
// The 325 the game compares actor IDs against is NoActorID below: a value
// stored in objectIDTable, not a bound on it. Stage object 325 is a real
// vanilla object, spawning actor 300.
constexpr u16 BaseObjectID = 326;

// The value objectIDTable holds for a stage object that spawns nothing. The
// spawn paths test for it at 0x0209BF38 and 0x0209C194, and 57 of the 326
// vanilla rows carry it. beforeLoadSprites writes it into any slot whose hash
// this build does not have.
constexpr u16 NoActorID = 325;

// One row per stage: variant, generated into extended_stageobjects.hpp.
//
// `objectId` is the other ID space: 0x182 + n, allocated by nsmbtool at build
// time, one per object, naming the class this stage object spawns. It is what
// the extension of objectIDTable is filled from. Two stage: variants of one
// object share an objectId and differ only in their ObjectInfo.
//
// `runtime` is the index in Glue::Runtime::runtimeModules of the module the
// object is in, which has to be loaded before it can spawn, or
// Glue::Runtime::None for an object in the binary.
struct ModuleStageObjectInfo {
	u32 hash;
	u16 objectId;
	u8 runtime;
	const ObjectInfo* info;
#ifdef GLUE_STAGEOBJECT_DEBUG
	const char* name;
#endif
};

// ---------------------------------------------------------------------------
// How a level places a module object
//
// The placement is an ordinary `StageObject` in the vanilla StageObjs block,
// with an `id` of BaseObjectID + n. That block is the only one the game walks,
// so being in it is what makes the object exist.
//
// The glue block supplies what those IDs mean. `glue.stageObjects` is a flat
// `u32[?]` of hashes: entry n is the hash of the object that ID BaseObjectID + n
// spawns. The index is the ID, so the array holds no IDs itself, and one entry
// covers however many placements refer to it.
//
// A level that places a module object is therefore only meaningful on a patched
// ROM. On a vanilla one the three tables end at 325 and those IDs read past them.
// ---------------------------------------------------------------------------

// The three extensions the patches below read. Declared here because the naked
// stubs reach them by mangled name.
//
// Both arrays are indexed by stage object ID minus BaseObjectID, which is the
// same index the level's hash array uses. moduleStageObjectCount slots covers
// any level, since every hash it names is one of the generated rows.
//
// alignas because MI_CpuCopyFast wants a word-aligned destination and
// ObjectInfo is only halfword-aligned. It has to be stated on the declaration
// as well as the definition or the two disagree.
alignas(4) extern ObjectInfo extObjInfos[];
extern u16 extObjIDs[];
extern const ObjectBank moduleObjectBank;

// Fills the two arrays from the level's glue block. Hooked into
// Stage::loadAreaObjects after it has loaded the stage blocks and before it
// reads any of the three tables.
void beforeLoadSprites();

}
