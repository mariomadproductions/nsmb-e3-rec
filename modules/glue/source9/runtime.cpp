#include <nsmb/extra/assert.hpp>
#include <nsmb/extra/log.hpp>

#include "glue/runtime.hpp"
#include "glue/object.hpp"

// Defines GLUE_RUNTIME_NONE when no object is in a runtime module, in which
// case there is nothing to load.
#include "generated/glue/runtime_modules.hpp"

#ifndef GLUE_RUNTIME_NONE

namespace Glue::Runtime {

// Where each module of the generated table is while it is loaded: the data of
// its file's cache entry.
static void* loadedImages[runtimeModuleCount];

// The modules loaded, in the order they were attached, so that they are
// detached in reverse. Two modules patching one address need that.
static u8 attachOrder[runtimeModuleCount];
static u32 attachedCount;

static void setProfiles(const void* image, bool attached)
{
	const Exports* exports = ncprt_exports_as(const Exports, image);
	if (exports == nullptr) {
		return;
	}

	for (u32 i = 0; i < exports->count; i++) {
		const Entry& entry = exports->entries[i];
		Object::mainExtPT[entry.objectId - Object::ObjectsExtStart] = attached ? entry.profile : nullptr;
	}
}

bool require(u32 module)
{
	if (loadedImages[module] != nullptr) {
		return true;
	}

	const ModuleFile& file = runtimeModules[module];

	void* image = FS::Cache::loadFile(file.fileId, false);
	if (image == nullptr) {
#ifdef NTR_DEBUG
		ntr_terminate("Runtime module %s (file %u) could not be read.\n", file.name, file.fileId);
#endif
		return false;
	}

	int result = ncprt_attach(image);
	if (result != NCPRT_OK) {
		FS::Cache::unloadFile(file.fileId);
#ifdef NTR_DEBUG
		ntr_terminate("Runtime module %s (file %u) could not be attached: error %d.\n", file.name, file.fileId, result);
#endif
		return false;
	}

#ifdef GLUE_STAGEOBJECT_DEBUG
	Log::print("Attached runtime module %s at 0x%08X\n", file.name, u32(image));
#endif

	loadedImages[module] = image;
	attachOrder[attachedCount++] = module;

	setProfiles(image, true);
	return true;
}

static bool isInTable(const void* image, const FS::Cache::CacheEntry* cache, u32 entries)
{
	for (u32 i = 0; i < entries; i++) {
		if (cache[i].data == image) {
			return true;
		}
	}
	return false;
}

void unloadTable(FS::Cache::CacheEntry* cache, u32 entries)
{
	u32 kept = 0;

	for (u32 i = attachedCount; i-- > 0;) {
		u32 module = attachOrder[i];
		void* image = loadedImages[module];

		if (!isInTable(image, cache, entries)) {
			continue;
		}

		setProfiles(image, false);
		ncprt_detach(image);

#ifdef GLUE_STAGEOBJECT_DEBUG
		Log::print("Detached runtime module %s\n", runtimeModules[module].name);
#endif

		loadedImages[module] = nullptr;
	}

	// Close the gaps the modules left, keeping the order of the rest.
	for (u32 i = 0; i < attachedCount; i++) {
		if (loadedImages[attachOrder[i]] != nullptr) {
			attachOrder[kept++] = attachOrder[i];
		}
	}
	attachedCount = kept;
}

} // namespace Glue::Runtime

// FS::Cache::Internal::clear, which empties a cache table and frees every file
// in it. The modules a level asked for are loaded into the table its file is
// in, and every path that frees the level data comes through here, so this is
// where they go too, before their memory does.
//
// A jump rather than ncp_hook: the hook bridge does not keep lr, and the
// replaced instruction is the push that saves it. So the stub runs the push
// first, then borrows r4 and r5, which it has just saved and which the function
// overwrites before reading, to keep the arguments across the call.
ncp_jump(0x02009D30)
NTR_NAKED void callUnloadTable() {asm(R"(
	stmdb	sp!, {r4, r5, r6, lr} // Keep replaced instruction
	mov		r4, r0
	mov		r5, r1
	bl		_ZN4Glue7Runtime11unloadTableEPN2FS5Cache10CacheEntryEm
	mov		r0, r4
	mov		r1, r5
	b		0x02009D30 + 4 // Return to code
)");}

#endif // GLUE_RUNTIME_NONE
