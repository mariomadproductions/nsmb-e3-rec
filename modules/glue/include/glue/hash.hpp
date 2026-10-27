#pragma once

#include <nsmb_nitro.hpp>
#include <cstdint>

namespace Glue {

// FNV-1a, 32-bit. This must keep agreeing with nsmbtool's fnv1a byte for byte:
// a level stores the hash of module.Object.Variant, so a change here does not
// fail a build, it invalidates every level already published.
consteval u32 hash(const char* str) {
	u32 hash = 2166136261u;
	while (*str) {
		hash ^= static_cast<u8>(*str++);
		hash *= 16777619u;
	}
	return hash;
}

struct Hash {
	template<std::size_t N>
	consteval Hash(const char (&string)[N]) : value(hash(string)) {}

	consteval Hash(u32 raw) : value(raw) {}

	u32 value;
};

}
