/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "Grid.h"
#include "Font.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	FrameTimer ft;
	Grid grid;
	static constexpr float selectWaitTime = 0.5f;
	float curWaitTime = 0.0f;
	bool cooldownOn = false;
	bool showingWaitText = true;
	Vei2 mousePos;
	Font boldFont = "Fonts\\ConsolasBold27x50.bmp";
	Font bigFont = "Fonts\\Consolas27x50.bmp";
	Font smallFont = "Fonts\\Consolas11x21.bmp";
	const std::string titleTxt = "SIMON SAYS!";
	const std::string promptTxt = "Press ENTER";
	const std::string noticeTxt = "(C) 2020 Sebastendo. This is a Beta version.";
	const std::string waitTxt = "Watch carefully...";
	const std::string repeatTxt = "REPEAT!";
	const std::string gameOverTxt = "GAME OVER";
	const std::string roundHeaderTxt = "Rounds beaten: ";
	std::string finalTally;
	bool onTitleScreen = true;
	/********************************/
};