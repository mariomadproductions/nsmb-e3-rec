#include "collisionviewer.hpp"

namespace CollisionViewer {

	constexpr u16 ColorActiveCollider	= GX_RGB(0xFF >> 3, 0x80 >> 3, 0xA0 >> 3);
	constexpr u16 ColorCollider			= GX_RGB(0x00 >> 3, 0x00 >> 3, 0xFF >> 3);
	constexpr u16 ColorPlatform			= GX_RGB(0x00 >> 3, 0xFF >> 3, 0x00 >> 3);
	constexpr u16 ColorSensorBottom		= GX_RGB(0xFF >> 3, 0xFF >> 3, 0xFF >> 3);
	constexpr u16 ColorSensorTop		= GX_RGB(0xFF >> 3, 0xFF >> 3, 0xFF >> 3);
	constexpr u16 ColorSensorSide		= GX_RGB(0xFF >> 3, 0xFF >> 3, 0xFF >> 3);
	constexpr u16 ColorSensorClimb		= GX_RGB(0xFF >> 3, 0xFF >> 3, 0xFF >> 3);
	constexpr u16 ColorActiveBox		= GX_RGB(0xFF >> 3, 0xFF >> 3, 0xFF >> 3);
	constexpr u16 ColorRenderBox		= GX_RGB(0xFF >> 3, 0xBF >> 3, 0x7F >> 3);
	constexpr u16 ColorPolygonCollider	= GX_RGB(0xFF >> 3, 0x00 >> 3, 0xFF >> 3);

	u8 fillAlpha = 15;
	Flags renderFlags = Flags::ActiveCollider | Flags::Collider | Flags::Platform | Flags::CollisionSensor | Flags::RenderBox;

	void renderLine(const Vec2& pt1, const Vec2& pt2, u16 color) {

		G3_LoadMtx43(&Game::viewMatrix);
		G3_Translate(pt1.x, pt1.y, 512.0fx);
		G3_Scale(pt2.x - pt1.x, pt2.y - pt1.y, 1.0fx);

		G3_Direct1(G3OP_TEXIMAGE_PARAM, 0);

		G3_PolygonAttr(GX_LIGHTMASK_NONE, GX_POLYGONMODE_MODULATE, GX_CULL_NONE, 0, 31, GX_POLYGON_ATTR_MISC_DISP_1DOT);
		G3_Color(color);

		G3_Begin(GX_BEGIN_TRIANGLES);
		G3_Vtx( 0.0fxs,  0.0fxs, 0);
		G3_Vtx( 1.0fxs,  1.0fxs, 0);
		G3_Vtx( 1.0fxs,  1.0fxs, 0);
		G3_End();

	}

	void renderBox(const FxRect& rect, u16 color, bool wireframe) {

		G3_LoadMtx43(&Game::viewMatrix);
		G3_Translate(rect.x, rect.y, 512.0fx);
		G3_Scale(rect.halfWidth, rect.halfHeight, 1.0fx);

		G3_Direct1(G3OP_TEXIMAGE_PARAM, 0);

		G3_PolygonAttr(GX_LIGHTMASK_NONE, GX_POLYGONMODE_MODULATE, GX_CULL_NONE, 0, 0, 0);
		G3_Color(color);

		G3_Begin(GX_BEGIN_QUADS);
		G3_Vtx(-1.0fxs,  1.0fxs, 0);
		G3_Vtx( 1.0fxs,  1.0fxs, 0);
		G3_Vtx( 1.0fxs, -1.0fxs, 0);
		G3_Vtx(-1.0fxs, -1.0fxs, 0);
		G3_End();

		if (!wireframe) {
			G3_PolygonAttr(GX_LIGHTMASK_NONE, GX_POLYGONMODE_MODULATE, GX_CULL_NONE, 0, fillAlpha, GX_POLYGON_ATTR_MISC_XLU_DEPTH_UPDATE);
			G3_Color(color);

			G3_Begin(GX_BEGIN_QUADS);
			G3_Vtx(-1.0fxs,  1.0fxs, 0);
			G3_Vtx( 1.0fxs,  1.0fxs, 0);
			G3_Vtx( 1.0fxs, -1.0fxs, 0);
			G3_Vtx(-1.0fxs, -1.0fxs, 0);
			G3_End();
		}

	}

	void renderArc(const FxRect& rect, s32 start, s32 arc, u16 color, bool wireframe) {

		if (arc < 0)
			return;

		if (!arc)
			arc = 0x10000;

		G3_LoadMtx43(&Game::viewMatrix);
		G3_Translate(rect.x, rect.y, 512.0fx);
		G3_Scale(rect.halfWidth, rect.halfHeight, 1.0fx);

		G3_Direct1(G3OP_TEXIMAGE_PARAM, 0);

		G3_PolygonAttr(GX_LIGHTMASK_NONE, GX_POLYGONMODE_MODULATE, GX_CULL_NONE, 0, 0, 0);
		G3_Color(color);

		constexpr u32 precision = 16;
		constexpr s16 step = 0x10000 / precision;

		G3_Begin(GX_BEGIN_TRIANGLES);

		fx16 prevX = Math::cos(start);
		fx16 prevY = Math::sin(start);

		for (s32 i = start + step; i <= start + arc; i += step) {

			fx16 x = Math::cos(i);
			fx16 y = Math::sin(i);

			G3_Vtx(prevX, prevY, 0);
			G3_Vtx(x, y, 0);
			G3_Vtx(x, y, 0);

			prevX = x;
			prevY = y;

		}

		G3_End();

		if (!wireframe) {
			G3_PolygonAttr(GX_LIGHTMASK_NONE, GX_POLYGONMODE_MODULATE, GX_CULL_NONE, 0, fillAlpha, GX_POLYGON_ATTR_MISC_XLU_DEPTH_UPDATE);
			G3_Color(color);

			G3_Begin(GX_BEGIN_TRIANGLES);

			fx16 prevX = Math::cos(start);
			fx16 prevY = Math::sin(start);

			for (s32 i = start + step; i <= start + arc; i += step) {

				fx16 x = Math::cos(i);
				fx16 y = Math::sin(i);

				G3_Vtx(0.0fxs, 0.0fxs, 0);
				G3_Vtx(prevX, prevY, 0);
				G3_Vtx(x, y, 0);

				prevX = x;
				prevY = y;

			}

			G3_End();
		}

	}

	void renderCircle(const FxRect& rect, u16 color, bool wireframe) {
		renderArc(rect, 0deg, 180deg, color, wireframe);
	}

	void renderTrapezoidH(const Vec2& pos, fx32 height, const fx32 (&points)[4], u16 color, bool wireframe) {

		fx32 t = Math::abs(points[1] - points[0]);
		fx32 b = Math::abs(points[3] - points[2]);
		fx32 max = MATH_MAX(t, b);

		fx32 tl = max ? Math::div(points[0], max) : 0;
		fx32 tr = max ? Math::div(points[1], max) : 0;
		fx32 bl = max ? Math::div(points[2], max) : 0;
		fx32 br = max ? Math::div(points[3], max) : 0;

		G3_LoadMtx43(&Game::viewMatrix);
		G3_Translate(pos.x, pos.y, 512.0fx);
		G3_Scale(max, height, 1.0fx);

		G3_Direct1(G3OP_TEXIMAGE_PARAM, 0);

		G3_PolygonAttr(GX_LIGHTMASK_NONE, GX_POLYGONMODE_MODULATE, GX_CULL_NONE, 0, 0, 0);
		G3_Color(color);

		G3_Begin(GX_BEGIN_QUADS);
		G3_Vtx(tl,  1.0fxs, 0);
		G3_Vtx(tr,  1.0fxs, 0);
		G3_Vtx(br, -1.0fxs, 0);
		G3_Vtx(bl, -1.0fxs, 0);
		G3_End();

		if (!wireframe) {
			G3_PolygonAttr(GX_LIGHTMASK_NONE, GX_POLYGONMODE_MODULATE, GX_CULL_NONE, 0, fillAlpha, GX_POLYGON_ATTR_MISC_XLU_DEPTH_UPDATE);
			G3_Color(color);

			G3_Begin(GX_BEGIN_QUADS);
			G3_Vtx(tl, 1.0fxs, 0);
			G3_Vtx(tr, 1.0fxs, 0);
			G3_Vtx(br, -1.0fxs, 0);
			G3_Vtx(bl, -1.0fxs, 0);
			G3_End();
		}

	}

	void renderTrapezoidV(const Vec2& pos, fx32 width, const fx32(&points)[4], u16 color, bool wireframe) {

		fx32 l = Math::abs(points[1] - points[0]);
		fx32 r = Math::abs(points[3] - points[2]);
		fx32 max = MATH_MAX(l, r);

		fx32 lt = max ? Math::div(points[0], max) : 0;
		fx32 lb = max ? Math::div(points[1], max) : 0;
		fx32 rt = max ? Math::div(points[2], max) : 0;
		fx32 rb = max ? Math::div(points[3], max) : 0;

		G3_LoadMtx43(&Game::viewMatrix);
		G3_Translate(pos.x, pos.y, 512.0fx);
		G3_Scale(width, max, 1.0fx);

		G3_Direct1(G3OP_TEXIMAGE_PARAM, 0);

		G3_PolygonAttr(GX_LIGHTMASK_NONE, GX_POLYGONMODE_MODULATE, GX_CULL_NONE, 0, 0, 0);
		G3_Color(color);

		G3_Begin(GX_BEGIN_QUADS);
		G3_Vtx(-1.0fxs, lt, 0);
		G3_Vtx( 1.0fxs, rt, 0);
		G3_Vtx( 1.0fxs, rb, 0);
		G3_Vtx(-1.0fxs, lb, 0);
		G3_End();

		if (!wireframe) {
			G3_PolygonAttr(GX_LIGHTMASK_NONE, GX_POLYGONMODE_MODULATE, GX_CULL_NONE, 0, fillAlpha, GX_POLYGON_ATTR_MISC_XLU_DEPTH_UPDATE);
			G3_Color(color);

			G3_Begin(GX_BEGIN_QUADS);
			G3_Vtx(-1.0fxs, lt, 0);
			G3_Vtx( 1.0fxs, rt, 0);
			G3_Vtx( 1.0fxs, rb, 0);
			G3_Vtx(-1.0fxs, lb, 0);
			G3_End();
		}

	}

	void renderHorizontalSensor(const Vec2& pos, const Sensor* sensor, u16 color) {

		Vec2 t = pos;
		Game::wrapPosition(t);

		Vec2 a = t;
		Vec2 b = t;

		if (bool(sensor->flags & SensorFlags::Line)) {

			const LineSensorH* ls = static_cast<const LineSensorH*>(sensor);

			a.x += ls->left;
			b.x += ls->right;

			a.y += ls->y;
			b.y += ls->y;

			renderLine(a, b, color);

			if (Game::wrapType == WrapType::Static) {

				if (a.x >= 256.0fx && b.x >= 256.0fx)
					return;

				a.x += 256.0fx;
				b.x += 256.0fx;

				renderLine(a, b, color);

			}

		}
		else {

			const PointSensor* ps = static_cast<const PointSensor*>(sensor);

			a.x += ps->x;
			a.y += ps->y;

			renderLine(a, a, color);

			if (Game::wrapType == WrapType::Static) {

				if (a.x >= 256.0fx && b.x >= 256.0fx)
					return;

				a.x += 256.0fx;
				b.x += 256.0fx;

				renderLine(a, a, color);

			}

		}


	}

	void renderVerticalSensor(const Vec2& pos, const Sensor* sensor, u16 color) {

		Vec2 a = pos;
		Vec2 b = pos;

		if (bool(sensor->flags & SensorFlags::Line)) {

			const LineSensorV* ls = static_cast<const LineSensorV*>(sensor);

			a.x -= ls->x;
			b.x -= ls->x;

			a.y += ls->top;
			b.y += ls->bottom;

			Game::wrapPosition(a);
			Game::wrapPosition(b);

			renderLine(a, b, color);

			a.x += ls->x * 2;
			b.x += ls->x * 2;

			Game::wrapPosition(a);
			Game::wrapPosition(b);

			renderLine(a, b, color);

			if (Game::wrapType == WrapType::Static) {

				a.x -= ls->x * 2;
				b.x -= ls->x * 2;

				if (a.x >= 256.0fx && b.x >= 256.0fx)
					return;

				a.x += 256.0fx;
				b.x += 256.0fx;

				renderLine(a, b, color);

				a.x += ls->x * 2;
				b.x += ls->x * 2;

				renderLine(a, b, color);

			}

		}
		else {

			const PointSensor* ps = static_cast<const PointSensor*>(sensor);

			a.x += ps->x;
			a.y += ps->y;

			Game::wrapPosition(a);
			Game::wrapPosition(b);

			renderLine(a, a, color);

			if (Game::wrapType == WrapType::Static) {

				if (a.x >= 256.0fx && b.x >= 256.0fx)
					return;

				a.x += 256.0fx;
				b.x += 256.0fx;

				renderLine(a, a, color);

			}

		}


	}

	void renderClimbSensor(const Vec2& pos, const LineSensorV* sensor, u16 color) {

		fx32 bottom = sensor->bottom;
		if (bottom <= sensor->top)
			bottom = sensor->top;

		Vec2 t = pos;
		Game::wrapPosition(t);

		fx32 x1 = t.x + sensor->x;
		fx32 x2 = t.x - sensor->x - 1.0fx;
		fx32 y1 = t.y + bottom;
		fx32 y2 = t.y + 1.0fx;

		renderLine(Vec2(x1, y1), Vec2(x2, y1), color);
		renderLine(Vec2(x2, y1), Vec2(x2, y2), color);
		renderLine(Vec2(x2, y2), Vec2(x1, y2), color);
		renderLine(Vec2(x1, y2), Vec2(x1, y1), color);

		if (Game::wrapType == WrapType::Static) {

			if (x1 >= 256.0fx && x2 >= 256.0fx)
				return;

			x1 += 256.0fx;
			x2 += 256.0fx;

			renderLine(Vec2(x1, y1), Vec2(x2, y1), color);
			renderLine(Vec2(x2, y1), Vec2(x2, y2), color);
			renderLine(Vec2(x2, y2), Vec2(x1, y2), color);
			renderLine(Vec2(x1, y2), Vec2(x1, y1), color);

		}

	}



	void renderActiveCollider(const ActiveCollider& u, Flags flags) {

		FxRect box = u.hitbox.rect;
		StageActor* owner = u.owner;
		box.x += owner->position.x;
		box.y += owner->position.y;

		switch (u.shape) {

		case ActiveColliderShape::Rectangle:

			if ((flags & Flags::RectActiveCollider) != Flags::None) {

				Game::wrapPosition(box.x);

				renderBox(box, ColorActiveCollider, false);

				if (Game::wrapType == WrapType::Static) {

					if (box.x >= 256.0fx)
						return;

					box.x += 256.0fx;

					renderBox(box, ColorActiveCollider, false);

				}

			}

			break;

		case ActiveColliderShape::Round:

			if ((flags & Flags::RoundActiveCollider) != Flags::None) {

				Game::wrapPosition(box.x);

				renderCircle(box, ColorActiveCollider, false);

				if (Game::wrapType == WrapType::Static) {

					if (box.x >= 256.0fx)
						return;

					box.x += 256.0fx;

					renderCircle(box, ColorActiveCollider, false);

				}

			}

			break;

		case ActiveColliderShape::TrapezoidH:
		case ActiveColliderShape::TrapezoidV:
		{
			Vec2 pos(box.x, box.y);
			fx32 points[4];

			points[0] = u.trapezoid.topLeftX;
			points[1] = u.trapezoid.topRightX;
			points[2] = u.trapezoid.botLeftX;
			points[3] = u.trapezoid.botRightX;

			if (u.shape == ActiveColliderShape::TrapezoidH) {

				if ((flags & Flags::TrapHActiveCollider) != Flags::None) {

					Game::wrapPosition(pos.x);

					renderTrapezoidH(pos, box.halfHeight, points, ColorActiveCollider);

					if (Game::wrapType == WrapType::Static) {

						if (pos.x >= 256.0fx)
							return;

						pos.x += 256.0fx;

						renderTrapezoidH(pos, box.halfHeight, points, ColorActiveCollider);

					}

				}

			}
			else {

				if ((flags & Flags::TrapVActiveCollider) != Flags::None) {

					Game::wrapPosition(pos.x);

					renderTrapezoidV(pos, box.halfWidth, points, ColorActiveCollider);

					if (Game::wrapType == WrapType::Static) {

						if (pos.x >= 256.0fx)
							return;

						pos.x += 256.0fx;

						renderTrapezoidV(pos, box.halfWidth, points, ColorActiveCollider);

					}

				}

			}

			break;
		}

		}

	}

	void renderCollider(const Collider& u, Flags flags) {

		FxRect box;
		box.halfWidth = (u.endPoint.x - u.originPoint.x) / 2;
		box.halfHeight = (u.endPoint.y - u.originPoint.y) / 2;
		box.x = u.originPoint.x + box.halfWidth;
		box.y = u.originPoint.y + box.halfHeight;

		StageActor* owner = u.owner;
		box.x += owner->position.x;
		box.y += owner->position.y;

		Game::wrapPosition(box.x);

		renderBox(box, ColorCollider, false);

		if (Game::wrapType == WrapType::Static) {

			if (box.x >= 256.0fx)
				return;

			box.x += 256.0fx;

			renderBox(box, ColorCollider, false);

		}

	}

	void renderPlatform(const Platform& u, Flags flags) {

		fx32 dx = u.pointEnd.x - u.pointStart.x;
		fx32 tx = u.pointEnd.x;

		Game::wrapPosition(tx);

		Vec2 s(tx - dx, u.pointStart.y);
		Vec2 e(tx, u.pointEnd.y);

		switch (u.type) {

		case PlatformType::Rotating:
		case PlatformType(1):

			if ((flags & Flags::RotatingPlatform) != Flags::None) {

				renderLine(s, e, ColorPlatform);

				if (Game::wrapType == WrapType::Static) {

					if (s.x >= 256.0fx && e.x >= 256.0fx)
						return;

					s.x += 256.0fx;
					e.x += 256.0fx;

					renderLine(s, e, ColorPlatform);

				}

			}

			break;

		case PlatformType::Segment:
		case PlatformType(3):

			if ((flags & Flags::SegmentPlatform) != Flags::None) {

				renderLine(s, e, ColorPlatform);

				if (Game::wrapType == WrapType::Static) {

					if (s.x >= 256.0fx && e.x >= 256.0fx)
						return;

					s.x += 256.0fx;
					e.x += 256.0fx;

					renderLine(s, e, ColorPlatform);

				}

			}

			break;

		case PlatformType::Deforming:

			if ((flags & Flags::DeformingPlatform) != Flags::None) {

				const DeformingPlatform& dp = static_cast<const DeformingPlatform&>(u);

				Vec2 a = dp.bendPoint1Abs;
				Vec2 b = dp.bendPoint2Abs;

				Game::wrapPosition(a);
				Game::wrapPosition(b);

				renderLine(s, a, ColorPlatform);
				renderLine(a, b, ColorPlatform);
				renderLine(b, e, ColorPlatform);

				if (Game::wrapType == WrapType::Static) {

					if (s.x >= 256.0fx && e.x >= 256.0fx && a.x >= 256.0fx && b.x >= 256.0fx)
						return;

					s.x += 256.0fx;
					e.x += 256.0fx;
					a.x += 256.0fx;
					b.x += 256.0fx;

					renderLine(s, a, ColorPlatform);
					renderLine(a, b, ColorPlatform);
					renderLine(b, e, ColorPlatform);

				}

			}

			break;

		case PlatformType::RoundExternal:
		case PlatformType::RoundInternal:
		{
			const RoundPlatform& rp = static_cast<const RoundPlatform&>(u);

			FxRect box;
			box.x = rp.center.x + u.owner->position.x;
			box.y = rp.center.y + u.owner->position.y;
			box.halfWidth  = rp.radius;
			box.halfHeight = rp.radius;

			Vec2 a, b;
			a.x = box.x;
			a.y = box.y;

			b.x = box.x + Math::mul(Math::cos(rp.angle), rp.radius);
			b.y = box.y + Math::mul(Math::sin(rp.angle), rp.radius);

			if (u.type == PlatformType::RoundExternal) {

				if ((flags & Flags::RoundExtPlatform) != Flags::None) {

					Game::wrapPosition(box.x);

					renderArc(box, 0deg, 180deg, ColorPlatform, true);

					if (Game::wrapType == WrapType::Static && box.x < 256.0fx) {

						box.x += 256.0fx;
						renderArc(box, 0deg, 180deg, ColorPlatform, true);

					}

					Game::wrapPosition(a);
					Game::wrapPosition(b);

					renderLine(a, b, ColorPlatform);

					if (Game::wrapType == WrapType::Static) {

						if (a.x >= 256.0fx && b.x >= 256.0fx)
							return;

						a.x += 256.0fx;
						b.x += 256.0fx;

						renderLine(a, b, ColorPlatform);

					}

				}

			}
			else {

				if ((flags & Flags::RoundIntPlatform) != Flags::None) {

					Game::wrapPosition(box.x);

					renderArc(box, 180deg, 180deg, ColorPlatform, true);

					if (Game::wrapType == WrapType::Static && box.x < 256.0fx) {

						box.x += 256.0fx;
						renderArc(box, 180deg, 180deg, ColorPlatform, true);

					}

					Game::wrapPosition(a);
					Game::wrapPosition(b);

					renderLine(a, b, ColorPlatform);

					if (Game::wrapType == WrapType::Static) {

						if (a.x >= 256.0fx && b.x >= 256.0fx)
							return;

						a.x += 256.0fx;
						b.x += 256.0fx;

						renderLine(a, b, ColorPlatform);

					}

				}

			}

			break;
		}

		}

	}

	void renderCollisionSensor(const CollisionMgr& u, Flags flags) {

		StageActor* sa = u.owner;

		if (u.bottomSensor && (flags & Flags::BottomCollisionSensor) != Flags::None)
			renderHorizontalSensor(sa->position, u.bottomSensor, ColorSensorBottom);

		if (u.topSensor && (flags & Flags::TopCollisionSensor) != Flags::None)
			renderHorizontalSensor(sa->position, u.topSensor, ColorSensorTop);

		if (u.sideSensor && (flags & Flags::SideCollisionSensor) != Flags::None)
			renderVerticalSensor(sa->position, u.sideSensor, ColorSensorSide);

		if (u.climbSensor && (flags & Flags::ClimbCollisionSensor) != Flags::None)
			renderClimbSensor(sa->position, u.climbSensor, ColorSensorClimb);

	}

	void renderEntityBox(const StageEntity& u, Flags flags) {

		FxRect box;
		box.x = Fx32::cast(u.viewOffset.x) + u.position.x;
		box.y = Fx32::cast(u.viewOffset.y) + u.position.y;

		if ((flags & Flags::RenderBox) != Flags::None) {

			box.halfWidth  = Fx32::cast(u.renderSize.x / 2);
			box.halfHeight = Fx32::cast(u.renderSize.y / 2);

			Game::wrapPosition(box.x);

			renderBox(box, ColorRenderBox);

			if (Game::wrapType == WrapType::Static) {

				if (box.x >= 256.0fx)
					return;

				box.x += 256.0fx;

				renderBox(box, ColorRenderBox);

			}

			return;
		}

		if ((flags & Flags::ActiveBox) != Flags::None) {

			box.halfWidth  = Fx32::cast(u.activeSize.x / 2);
			box.halfHeight = Fx32::cast(u.activeSize.y / 2);

			Game::wrapPosition(box.x);

			renderBox(box, ColorActiveBox);

			if (Game::wrapType == WrapType::Static) {

				if (box.x >= 256.0fx)
					return;

				box.x += 256.0fx;

				renderBox(box, ColorActiveBox);

			}

		}

	}

	void renderActiveColliders(Flags flags) {

		const ActiveCollider* ac = ActiveCollider::listHead;
		while (ac) {
			renderActiveCollider(*ac, flags);
			ac = ac->next;
		}

	}

	void renderColliders(Flags flags) {

		const Collider* c = Collider::listHead;
		while (c) {
			renderCollider(*c, flags);
			c = c->next;
		}

	}

	void renderPlatforms(Flags flags) {

		const Platform* p = Platform::listHead;
		while (p) {
			renderPlatform(*p, flags);
			p = p->next;
		}

	}

	void renderCollisionSensors(Flags flags) {

		const Actor* a = ProcessManager::getNextActor();
		while (a) {

			if (a->actorType == ActorType::Entity || a->actorType == ActorType::Player) {
				renderCollisionSensor(static_cast<const StageActor*>(a)->collisionMgr, flags);
			}

			a = ProcessManager::getNextActor(a);

		}

	}

	void renderEntityBoxes(Flags flags) {

		const Actor* a = ProcessManager::getNextActor();
		while (a) {

			if (a->actorType == ActorType::Entity) {
				renderEntityBox(*static_cast<const StageEntity*>(a), flags);
			}

			a = ProcessManager::getNextActor(a);

		}

	}


	void render() {

		NNS_G3dGeFlushBuffer();
		G3X_AntiAlias(false);

		if ((renderFlags & Flags::ActiveCollider) != Flags::None)
			renderActiveColliders(renderFlags);

		if ((renderFlags & Flags::Collider) != Flags::None)
			renderColliders(renderFlags);

		if ((renderFlags & Flags::Platform) != Flags::None)
			renderPlatforms(renderFlags);

		if ((renderFlags & Flags::CollisionSensor) != Flags::None)
			renderCollisionSensors(renderFlags);

		if ((renderFlags & (Flags::EntityBox)) != Flags::None)
			renderEntityBoxes(renderFlags);

	}

}
