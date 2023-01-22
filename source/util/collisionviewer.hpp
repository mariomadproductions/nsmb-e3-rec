#pragma once

#include "nsmb/stage/entity.h"
#include "nsmb/physics.h"
#include "nsmb/game.h"

enum class CollisionViewerFlags : u32 {

	None,

	RectActiveCollider = 1 << 0,
	RoundActiveCollider = 1 << 1,
	TrapHActiveCollider = 1 << 2,
	TrapVActiveCollider = 1 << 3,

	Collider = 1 << 4,

	RotatingPlatform = 1 << 5,
	SegmentPlatform = 1 << 6,
	DeformingPlatform = 1 << 7,
	RoundExtPlatform = 1 << 8,
	RoundIntPlatform = 1 << 9,

	BottomCollisionSensor = 1 << 10,
	TopCollisionSensor = 1 << 11,
	SideCollisionSensor = 1 << 12,
	ClimbCollisionSensor = 1 << 13,

	ActiveBox = 1 << 14,
	RenderBox = 1 << 15,

	ActiveCollider = RectActiveCollider | RoundActiveCollider | TrapHActiveCollider | TrapVActiveCollider,
	Platform = RotatingPlatform | SegmentPlatform | DeformingPlatform | RoundExtPlatform | RoundIntPlatform,
	CollisionSensor = BottomCollisionSensor | TopCollisionSensor | SideCollisionSensor | ClimbCollisionSensor,
	EntityBox = ActiveBox | RenderBox

};
IMPL_ENUMCLASS_OPERATORS(CollisionViewerFlags);

namespace CollisionViewer {

	using Flags = CollisionViewerFlags;

	extern u8 fillAlpha;
	extern Flags renderFlags;

	NTR_INLINE void enableUnit(Flags flag) {
		renderFlags |= flag;
	}

	NTR_INLINE void disableUnit(Flags flags) {
		renderFlags &= ~flags;
	}

	NTR_INLINE void setFillAlpha(u8 alpha) {
		fillAlpha = alpha;
	}

	void renderLine(const Vec2& pt1, const Vec2& pt2, u16 color);
	void renderBox(const FxRect& rect, u16 color, bool wireframe = false);
	void renderArc(const FxRect& rect, s32 start, s32 end, u16 color, bool wireframe = false);
	void renderCircle(const FxRect& rect, u16 color, bool wireframe = false);
	void renderTrapezoidH(const Vec2& pos, fx32 height, const fx32(&points)[4], u16 color, bool wireframe = false);
	void renderTrapezoidV(const Vec2& pos, fx32 width, const fx32(&points)[4], u16 color, bool wireframe = false);
	void renderHorizontalSensor(const Vec2& pos, const Sensor* sensor, u16 color);
	void renderVerticalSensor(const Vec2& pos, const Sensor* sensor, u16 color);
	void renderClimbSensor(const Vec2& pos, const LineSensorV* sensor, u16 color);

	void renderActiveCollider(const ActiveCollider& u, Flags flags);
	void renderCollider(const Collider& u, Flags flags);
	void renderPlatform(const Platform& u, Flags flags);
	void renderCollisionSensor(const CollisionMgr& u, Flags flags);
	void renderEntityBox(const StageEntity& u, Flags flags);

	void renderActiveColliders(Flags flags);
	void renderColliders(Flags flags);
	void renderPlatforms(Flags flags);
	void renderCollisionSensors(Flags flags);
	void renderEntityBoxes(Flags flags);

	void render();

}
