#pragma once

#include "Graphics.h"
#include "Vei2.h"

class SpriteCodex
{
public:
	static void DrawWaitText(const Vei2& topLeft, Graphics& gfx);
	static void DrawPlayRptTxt(const Vei2& topLeft, Graphics& gfx);
	static void DrawGameOver(const Vei2& topLeft, Graphics& gfx);
public:
	static constexpr int waitTxtWidth = 378;
	static constexpr int playTxtWidth = 160;
	static constexpr int txtHeight = 60;
};