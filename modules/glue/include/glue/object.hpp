#pragma once

#include <nsmb/core/entity/process.hpp>
#include <nsmb/core/entity/actor.hpp>


namespace Glue::Object {

	// The first object ID past the game's own table. nsmbtool allocates custom
	// objects upward from here and emits the same literal into the generated
	// headers, so both sides keep seeing one number.
	static constexpr u32 ObjectsExtStart = 0x182;


	extern const ObjectProfile* mainExtPT[];

	extern constinit const ObjectProfile* const* currentExtPT;


	constexpr const ObjectProfile& getObjectProfile(u16 objectID) {
		return objectID >= ObjectsExtStart ? *mainExtPT[objectID - ObjectsExtStart] : *Game::mainProcessTable[objectID];
	}

	constexpr const ActorProfile& getActorProfile(u16 objectID) {
		return static_cast<const ActorProfile&>(getObjectProfile(objectID));
	}

}
