#pragma once

#include <nsmb/core/entity/object.hpp>
#include <nsmb/core/filesystem/cache.hpp>

namespace Glue::Runtime {

// ---------------------------------------------------------------------------
// Objects in a runtime module
//
// A component that targets arm9(rt:<name>) is not in the binary. Its code is
// linked into an image, written to NitroFS, and loaded by beforeLoadSprites
// when a level places one of its stage objects. Until then the object's row in
// mainExtPT is null, so the object ID exists but cannot be spawned.
//
// The image is loaded into the file cache table the level file is in, and
// detached when that table is cleared, which every path that frees the level
// data goes through. A module therefore lives exactly as long as the level
// that asked for it.
// ---------------------------------------------------------------------------

// The runtime field of a stage object whose object is in the binary.
constexpr u8 None = 0xFF;

// One row of the generated runtimeModules table. fileId is in the game's
// numbering, the one FS::Cache::loadFile takes.
struct ModuleFile {
	u16 fileId;
	const char* name;
};

// An object the module holds, and the profile that goes in its mainExtPT row.
struct Entry {
	u16 objectId;
	const ObjectProfile* profile;
};

// What every module gives Glue, generated into runtime/<name>.hpp.
struct Exports {
	u32 count;
	const Entry* entries;
};

// Loads and attaches a module from the generated table, unless it is loaded
// already, and fills its objects' rows in mainExtPT. Returns whether its
// objects can be spawned.
bool require(u32 module);

// Detaches every module whose image is in a cache table, and empties its
// objects' rows. Called as that table is cleared.
void unloadTable(FS::Cache::CacheEntry* cache, u32 entries);

}
