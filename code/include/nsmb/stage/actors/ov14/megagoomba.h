#pragma once

#include "nsmb/stage/entity3danm.h"
#include "nsmb/graphics/3d/animationctrl.h"
#include "nsmb/physics/segmentplatform.h"

class MegaGoomba : public StageEntity3DAnm
{
public:
	using StateFunction = bool(MegaGoomba::*)();

	// C1: 0x02132E94
	MegaGoomba();

	// D0: 0x0212F9D0
	// D1: 0x0212F900
	virtual ~MegaGoomba();

	s32 onCreate() override;
	s32 onDestroy() override;
	bool onPrepareResources() override;

	// 0x02132D68
	void switchState(StateFunction function);

	AnimationCtrl animationCtrl;
	ActiveCollider activeCollider2;
	FxRect nextActiveColliderRect;
	StateFunction updateFunc;
	StateFunction unkFunc;
	SegmentPlatform segPlat1;
	SegmentPlatform segPlat2;
	SegmentPlatform segPlat3;
	Vec3 unk708;
	Vec3 unk718;
	Vec3 unk728;
	Vec3 unk738;
	fx32 spawnPosX;
	u32 unk74C;
	u32 unk750;
	s32 unk754;
	u32 unk758;
	fx32 playerVelY;
	u32 unk760;
	u8 unk764;
	u8 unk765;
	u8 unk766;
	u8 unk767;
	u32 unk768;
	u32 unk76C;
	u32 unk770;
	u16 unk774;
	u16 unk776;
	u16 unk778;
	u16 unk77A;
	u16 unk77C;
	u16 unk77E;
	u16 unk780;
	u16 unk782;
	u16 unk784;
	u16 unk786;
	u32 unk788;
	u8 unk78C;
	u8 unk78D;
	u8 unk78E;
	u8 unk78F;
	u16 unk790;
	u16 unk792;
	u16 unk794;
	u16 unk796;
	u16 unk798;
	u16 unk79A;
	u16 collidersLinked;
	u16 unk79E;
	u16 unk7A0;
	u16 unk7A2;
	u16 unk7A4;
	u16 growthTimer;
	u16 growsInstantly;
	u16 isPlayerMega;
	u8 unk7AC;
	u8 unk7AD;
	u16 unk7AE;
	u8 isPlayerInView;
	u8 unk7B1;
	u8 unk7B2;
	u8 unk7B3;
	s8 stateStep;
	u8 unk7B5;
	u8 unk7B6;
	u8 unk7B7;
	u32 fogTable[8];
	u8 unk7D8;
	u8 unk7D9;
	u8 unk7DA;
	u8 unk7DB;
	u8 unk7DC;
	u8 unk7DD;
	u8 unk7DE;
	u8 unk7DF;
};

NTR_SIZE_GUARD(MegaGoomba, 0x7E0);
