#pragma once

#include "nitro/types.h"
#include "nsmb/vector.h"

#define isDSiMode ((*((u8*)0x4004000)) & 1)

#define nkeysHeld ((u16*)0x02087650)
#define nkeysDown ((u16*)0x02087652)
#define nkeysUp ((u16*)0x02087640)
#define dashWithX ((u32*)0x02085AD4)

#define penHeld ((u8*)0x20888E5)
#define penX ((u8*)0x20888E6)
#define penY ((u8*)0x20888E7)
#define penXDown ((u8*)0x208B4E8)
#define penYDown ((u8*)0x208B4F4)

#define SCENE_INFO ((s32*)0x02088F48)

typedef enum Scene {
	BOOT_SCENE,
	CONNECT_SCENE,
	DEBUG_SCENE,
	STAGE_SCENE,
	MAIN_MENU_SCENE,
	MvsL_SETUP_SCENE,
	MvsL_MAIN_MENU_SCENE,
	SAVE_SCENE,
	WORLD_SCENE,
	WORLDMAP_SCENE,
	MvsL_RESULTS_SCENE,
	CORRUPTED_FILE_SCENE,
	ENDING_SCENE,
	STAGE_INTRO_SCENE,
	GAMEOVER_SCENE,
	MvsL_STAGE_INTRO_SCENE,
	SOUNDTEST_SCENE,
	KEY_SCENE,
	MINIGAMES_SCENE = 326,
} Scene;

typedef struct SaveData
{
	u32 header; //0
	u32 field_04; //4
	u32 Completion; //8
	u32 lives; //12
	u32 coins; //16
	u32 field_14; //24
	u32 starCoinsInSave; //32
	u32 spentStarCoins; //40
	u32 currentWorld; //42
	u32 field_24;
	u32 currentWorldMapNode;
	u32 field_2C;
	u32 currentPowerup;
	u32 score;
	u32 currentBottomScreenBackground;
	u32 field_3C;
	u32 field_40;
	u32 field_44;
	u32 field_48;
	u32 field_4C;
	u32 field_50;
	u32 field_54;
	u32 field_58;
	u8 inventoryItem;
	u8 field_5D;
	u8 field_5E;
	u8 field_5F;
	u16 worlds[8];
	u8 starCoins[200];
	u8 levels[240];
	u8 unk[32];
} SaveData;

extern SaveData saveData;

typedef struct Entrance {
	u16 x;
	u16 y;
	u16 cameraX;
	u16 cameraY;
	u8 id;
	u8 destArea_dpEnd; // destination area OR direct-pipe "end" flag
	u8 destLevel_path; // destination level OR direct-pipe path ID
	u8 destWorld;
	u8 destEntranceID;
	s8 zoom;
	u8 type;
	u8 settings;
	// settings & 0x80: non-enterable
	// settings & 0x10: use wavy wipe instead of Mario head transition
	// settings & 0x08: direct pipe
	// settings & 0x01: use bottom screen
	u8 unk10;
	u8 unk11;
	s8 view;
	u8 destWorldMapNode; // on current world map; destWorld value is ignored
} Entrance;

typedef struct View
{
	u16 x;
	u16 y;
	u16 width;
	u16 height;
	u8 id;
	u8 camID;
	u8 musicID;
	u8 unk1;
	u8 unk2;
	u8 unk3;
	u8 lightingID;
	u8 progressPathID;
} View;

typedef struct Zone
{
	u16 x;
	u16 y;
	u16 width;
	u16 height;
	u8 id;
	u8 field_9;
	u8 field_A;
	u8 field_B;
} Zone;

typedef struct FxRectangle
{
	fx32 x;
	fx32 y;
	fx32 width;
	fx32 height;
} FxZone;

#ifdef __cplusplus
extern "C" {
#endif

	// Fades to another scene.
	// WARNING: Do not call if current scene is stage scene (level), use NSMB_ChangeToSceneFromLevel instead.
	void ChangeToScene(u16 SceneID, u32 SceneParameters);

	// Fades to another scene from the level (stage scene).
	void ChangeToSceneFromLevel(u16 SceneID, u32 SceneParameters);

	// Fades the scene to a level (SceneID: 13 = Singleplayer, 15 = Mario Vs Luigi)
	void ChangeSceneToLevel(u16 SceneID, u32 MvsLMode, u32 World, u32 Level, u8 Area, u8 PlayerNumber, u8 SpawnBitmask, u8 P1Character, u8 P2Character, u8 StartingPowerup, u8 EntranceID, u8 a12, u32 a13, u32 a14, u32 a15, u32 a16, u32 a17);

	// Reloads the level into a new area.
	void ChangeSceneForEntrance();

	// Reloads the level into a new area.
	inline void ChangeLevelArea(int destEntrance, int destArea) {
		*(int*)0x0208B084 = destEntrance;
		*(int*)0x0208B09C = destArea;
		ChangeSceneForEntrance();
	}

	// Leaves the level and goes to the worldmap or the mvsl menu
	void ExitLevel(BOOL Completed);

	// Writes saveData to the the backup file
	void SaveSave(int fileNo, SaveData* saveData);

	/* Reads a backup file to saveData and sets the counters, returns 1 if load succeeded
		if(lives != 0)
		saveData.lives = lives;
		saveData.currentPowerup = 0;*/
	int LoadSaveAndSetCounters(int fileNo, int lives, SaveData* saveData);

	// Gets the file ID for a BMG
	int GetFileIDForBMG(int bmgNo);

	// Waits for video blanking
	void WaitForVBlank();

	// Flushes DC Range or All
	void DC_FlushRangeOrAll(const void* startAddr, u32 nBytes);

	void InitEntranceData(Vec3* entranceData, u32 entranceId, u32 playerNo);

	// Gets the tile behavior at the position
	u32 GetTileBehaviorAtPos(int x, int y);

	// Gets if the player starts from midway or not
	BOOL GetStartingFromMidway();

	// 8 = 1-Up
	void GiveScoreItemForPlayer(int item, int playerNo);

	// Returns how many consoles are connected
	int GetConsoleCount();

	// Gets the pointer to an entrance
	Entrance* GetPtrToEntranceById(int entranceId, int entranceId2);

	// Spawns a growing entrance vine at specified position
	void SpawnGrowingEntranceVine(Vec3* pos);

	// Setups fading for scene
	void SetSceneFadingArguments(void* sceneInfo, u8 fade_mode, BOOL fade_white, int a4);

	// Sets the background visibility upon scene fading start
	inline void nGX_SetVisiblePlaneSceneStart(int plane) {
		*(int*)0x2085A88 = plane;
	}

	BOOL GetSceneFadingFinished(void* sceneInfo);

	// Initializes BNCD, BNCL and BNBL file data pointers for the sub screen
	void BNXX_InitSub(void* bncd, void* bncl, void* bnbl);

	// Updates the bottom screen inventory powerup
	void UpdateInventoryPowerup(int playerNo, u8 powerup);

	// Initializes WiFi
	void WiFi_Init();

	// Updates the touched position
	void UpdatePenTouchPositions();

	// Spawns a particle at a position
	void SpawnParticle(int particleId, Vec3* pos);

	// Spawns a particle at a position for a duration
	void SpawnAndEndParticle(int frames, int particleId, Vec3* pos, int a4, int a5, int a6, int a7);

	// Spawns a coin particle at a position
	void SpawnCoinParticle(fx32 x, fx32 y, fx32 z);

	// Gets the pointer to a view (also gets the area if not null)
	View* GetPtrToViewByID(u8 id, FxRectangle* area);

	// Gets the pointer to a zone (also gets the area if not null)
	Zone* GetPtrToZoneByID(u8 id, FxRectangle* area);

	// Returns a random number
	int RNG();

#ifdef __cplusplus
}
#endif