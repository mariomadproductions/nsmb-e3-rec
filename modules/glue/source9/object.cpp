#include "glue/object.hpp"

#include "object_registry.hpp"
#include "scene_overlay_registry.hpp"

#include "generated/glue/extended_profiles.hpp"

// mainExtPT and currentExtPT are defined in extended_profiles.hpp

namespace Glue::Object {

ncp_jump(0x0204C9FC) // Base::spawn
NTR_NAKED void extendBaseSpawn() {asm(R"(
#ifdef GLUE_OBJECT_DEBUG
	print	"Base spawned [ID: %r0% Settings: %r5%]\n"
#endif
	cmp		r0, #0x180
	ldrls	r0, =0x0208FB98
	ldrhi	r0, =_ZN4Glue6Object12currentExtPTE
	subhi	r7, r7, #0x180
	subhi	r7, r7, #0x2
	b		0x0204C9FC + 4
)");}

ncp_jump(0x0204D378) // Base::Base
NTR_NAKED void extendBaseCtor() {asm(R"(
	ldr		r1, [r4, #0xC]
	cmp		r1, #0x180
	ldrls	r0, =0x0208FB98
	ldrhi	r0, =_ZN4Glue6Object12currentExtPTE
	subhi	r1, r1, #0x180
	subhi	r1, r1, #0x2
	b		0x0204D380
)");}

#ifndef GLUE_OBJECT_NO_SCENE_IN_OVERLAY

ncp_jump(0x0200E42C) // Game::getSceneOverlay
u32 extendGetSceneOverlay(u16 sceneID, u32 overlayID) {

	return getSceneOverlayID(sceneID, overlayID);

}

#endif

} // namespace Glue::Object
