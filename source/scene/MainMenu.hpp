#pragma once

#include "nsmb/entity/scene.h"

class MainMenu : public Scene
{
public:
	static ObjectProfile profile;

	s32 onCreate() override;
	s32 onUpdate() override;
	s32 onRender() override;
	s32 onDestroy() override;

	static void initTopScreen();
	static void initBottomScreen();

	void onButtonClicked();

	u8 selectedButton;
	bool buttonClicked;
	bool isFirstExecute;
};
