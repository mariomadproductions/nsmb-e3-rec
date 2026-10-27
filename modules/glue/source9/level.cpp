#include "glue/level.hpp"

#include <nsmb/game/stage.hpp>

namespace Glue::Level {

GlueBlock::DataEntry* GlueBlock::getDataEntries() {
	// Skip flags section: flag count (u32) + flags (u32 each)
	return rcast<DataEntry*>(rcast<u8*>(this) + sizeof(u32) + (flagCount * sizeof(u32)));
}

bool GlueBlock::hasFlag(u32 hash) {
	u8* ptr = rcast<u8*>(this) + sizeof(u32); // Skip flag count

	for (u32 i = 0; i < this->flagCount; i++) {
		GlueBlock::FlagInfo* flagInfo = rcast<GlueBlock::FlagInfo*>(ptr);
		if (flagInfo->hash == hash) {
			return true;
		}
		ptr += sizeof(GlueBlock::FlagInfo);
	}

	return false;
}

GlueBlock::DataEntry* GlueBlock::findDataEntry(u32 hash) {
	GlueBlock::DataEntry* dataEntry = this->getDataEntries();

	while (true) {
		// End
		if (dataEntry->hash == 0) {
			break;
		}

		// Value found
		if (dataEntry->hash == hash) {
			return dataEntry;
		}

		// Move to next ValueInfo
		dataEntry++;
	}

	return nullptr;
}

bool hasGlueBlock() {
	// Check if header block was extended
	return Stage::stageBlocksSize[scast<u32>(StageBlockID::Header)] > 32;
}

GlueBlock* getGlueBlock() {
	if (!hasGlueBlock()) {
		return nullptr;
	}
	return rcast<GlueBlock*>(rcast<u8*>(Stage::stageBlocks.header) + 32);
}

bool hasFlag(Hash hash) {
	GlueBlock* block = getGlueBlock();
	if (block == nullptr) {
		return false;
	}
	return block->hasFlag(hash.value);
}

void* findData(Hash hash) {
	GlueBlock* block = getGlueBlock();
	if (block == nullptr) {
		return nullptr;
	}
	GlueBlock::DataEntry* dataEntry = block->findDataEntry(hash.value);
	if (dataEntry == nullptr) {
		return nullptr;
	}
	return rcast<void*>(rcast<u8*>(block) + dataEntry->offset);
}

}
