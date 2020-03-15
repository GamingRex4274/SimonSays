/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	grid(gfx.GetRect().GetCenter())
{
	grid.AddWndToPtrn();
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();

	if (grid.GetState() != Grid::State::GameOver)
	{
		if (cooldownOn)
		{
			curWaitTime += dt;
			if (curWaitTime > selectWaitTime)
			{
				grid.ResetWindows();
				curWaitTime = 0.0f;
				cooldownOn = false;
				showingWaitText = true;
			}
		}

		if (grid.GetState() == Grid::State::Playing)
		{
			showingWaitText = false;

			while (!wnd.mouse.IsEmpty())
			{
				const auto e = wnd.mouse.Read();
				if (e.GetType() == Mouse::Event::Type::LPress)
				{
					mousePos = e.GetPos();
					if (grid.GetRect().Contains(mousePos))
					{
						grid.OnSelectClick(mousePos, cooldownOn);
						cooldownOn = true;
					}
				}
			}
		}
		else if (grid.GetState() == Grid::State::Waiting)
		{
			grid.ShowPtrnSelection(cooldownOn);
			cooldownOn = true;
		}
	}
	else
	{
		const std::string score = std::to_string(grid.GetCurrentRound());
		finalTally = roundHeaderTxt + score;
	}
}

void Game::ComposeFrame()
{
	switch (grid.GetState())
	{
	case Grid::State::Waiting:
		if (showingWaitText)
		{
			bigFont.DrawText(waitTxt, Vei2((Graphics::ScreenWidth - (int(waitTxt.size()) * bigFont.GetGlyphWidth())) / 2, bigFont.GetGlyphHeight() / 2), { 0,135,255 }, gfx);
		}
		break;
	case Grid::State::Playing:
		bigFont.DrawText(repeatTxt, Vei2((Graphics::ScreenWidth - (int(repeatTxt.size()) * bigFont.GetGlyphWidth())) / 2, bigFont.GetGlyphHeight() / 2), Colors::Red, gfx);
		break;
	case Grid::State::GameOver:
		boldFont.DrawText(gameOverTxt, Vei2((Graphics::ScreenWidth - (int(gameOverTxt.size()) * boldFont.GetGlyphWidth())) / 2, boldFont.GetGlyphHeight() / 4), Colors::White, gfx);
		smallFont.DrawText(finalTally, Vei2((Graphics::ScreenWidth - (int(finalTally.size()) * smallFont.GetGlyphWidth())) / 2, (boldFont.GetGlyphHeight() / 4) * 5), Colors::White, gfx);
		break;
	}
	grid.Draw(gfx);
}