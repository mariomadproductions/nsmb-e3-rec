#pragma once

#include "nitro/types.h"
#include "nsmb/vector.h"

typedef struct
{
	void* dtor;
	void* dtorFree;
	void* null;
	void* beforeDraw1;
	void* beforeDraw2;
	void* draw;
}	vtable_model3d;

typedef struct
{
	u32 nothing0;
	u32 mdlSet;
	u32 nothing1;
	u32* ptrToFunc;
	u32 HMRFsmth;
	u32* AnmBlendJnt;
	u32 nothing2;
	u32* ptrToFunc2;
	u32* ptrToFunc3;
	u8 A, B, C, D;
}	modelFunctions;

typedef struct
{
	u32 scaleX, rotZ, negRotY;
	u32 negRotZ, scaleY, rotX;
	u32 rotY, negRotX, scaleZ;
	u32 posX, posY, posZ;
}	MTX_43;

typedef struct
{
	vtable_model3d* vtable;
	modelFunctions mFun;
	u32 field_0x2c;
	void* owner;
	u32 field_0x34;
	u32 field_0x38;
	u32 field_0x3c;
	u32 field_0x40;
	u32 field_0x44;
	u32 field_0x48;
	u32 field_0x4c;
	u32 field_0x50;
	u32 something;
	u32 mdlSet;
	u32* texturePtr;
	MTX_43 matrix;
}	Model3d;

typedef struct  // Size: 0x18
{
	u32 bigValue;
	u8 timer;
	u8 unk1;
	u8 unk2;
	u8 unk3;
	u32 speed;
	u32* AnimFile;
	u32* HMRFsmth;
	u32 ID;
} Anim3d;

typedef struct  // Size: 0xA8
{
	Model3d model;  // 0x00
	Anim3d anim;    // 0x90
} ModelAnim3d;

#ifdef __cplusplus
extern "C"
{
#endif

	// Functions for Models without animation
	void model3d_ctor(Model3d* model);
	BOOL model3d_setup(Model3d* model, void* modelFile, u32 modelId);
	void model3d_dtor(Model3d* model);

	// Functions for Models with character animation
	// These functions call all above functions (model3d)
	void modelAnim3d_ctor(ModelAnim3d* model);
	BOOL modelAnim3d_setup(ModelAnim3d* model, void* modelFile, void* animationFile, u32 modelId, u32 animationId);
	void modelAnim3d_setAnimation(ModelAnim3d* model, u32 animationId, u32 settings, u32 animationSpeed, u32 startFrame);

	void anim3d_update(Anim3d* animation);

	void model3d_draw(Model3d* model, Vec3* position, S16Vec3* rotation, Vec3* scale);

#ifdef __cplusplus
}
#endif