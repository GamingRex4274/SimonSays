#pragma once

#include "Graphics.h"
#include "Vei2.h"

class SpriteCodex
{
public:
	static void DrawWaitText(Graphics& gfx); // 378x60
	static void DrawPlayRptTxt(Graphics& gfx); // 160x60
	static void DrawGameOver(Graphics& gfx); // 250x40
	static void DrawRoundHeader(Graphics& gfx); // 123x15
	static void DrawNum(int n, Graphics& gfx); // All numbers: 9x14
private:
	static void DrawNum0(const Vei2& topLeft, Graphics& gfx);
	static void DrawNum1(const Vei2& topLeft, Graphics& gfx);
	static void DrawNum2(const Vei2& topLeft, Graphics& gfx);
	static void DrawNum3(const Vei2& topLeft, Graphics& gfx);
	static void DrawNum4(const Vei2& topLeft, Graphics& gfx);
	static void DrawNum5(const Vei2& topLeft, Graphics& gfx);
	static void DrawNum6(const Vei2& topLeft, Graphics& gfx);
	static void DrawNum7(const Vei2& topLeft, Graphics& gfx);
	static void DrawNum8(const Vei2& topLeft, Graphics& gfx);
	static void DrawNum9(const Vei2& topLeft, Graphics& gfx);
private:
	static constexpr int waitTxtWidth = 378;
	static constexpr int playTxtWidth = 160;
	static constexpr int waitAndPlayTxtHeight = 60;
	static constexpr int gameOverTxtWidth = 250;
	static constexpr int gameOverTxtHeight = 40;
	static constexpr int rndHeaderWidth = 123;
	static constexpr int rndHeaderHeight = 15;
	static constexpr int rndHeaderOffset = 50;
	static constexpr int numWidth = 9;
	static constexpr int numHeight = 14;
	static constexpr int numPadding = 9;
};