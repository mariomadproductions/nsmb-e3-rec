#pragma once

#include <nsmb/core/filesystem/file.hpp>

#include "fid.hpp"

namespace E3Rec {

// The FS::fileIDOffset that ""fid's ids are relative to: the 131 overlay files
// in front of NitroFS.
constexpr u16 GameFileIDOffset = 131;

// Runs `load` with FS::fileIDOffset pinned to GameFileIDOffset. The top screen
// is set up from the boot scene as well as from the menu, and the original
// code read its files there by FAT index with the offset cleared, so the offset
// is set for the duration rather than assumed.
template<class F>
void withGameFileIDs(F load)
{
	u16 offset = FS::fileIDOffset;
	FS::fileIDOffset = GameFileIDOffset;
	load();
	FS::fileIDOffset = offset;
}

}
