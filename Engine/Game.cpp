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
#include <fstream>
#include "SpriteEffect.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	sndTitle(L"Sounds\\title.wav", 1.567f, 12.522f),
	sndVictory(L"Sounds\\victory.wav", 4.325f, 22.727f)
{
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

	if (!onTitleScreen)
	{
		if (cooldownOn)
		{
			curWaitTime += dt;
			if (curWaitTime > waitTime)
			{
				switch (pGrid->GetState())
				{
				case Grid::State::Waiting:
				case Grid::State::Playing:
					pGrid->ResetWindows();
					break;
				}

				curWaitTime = 0.0f;
				cooldownOn = false;
				showingWaitText = true;
			}
		}

		if (sndTitlePlaying)
		{
			sndTitle.StopAll();
			sndTitlePlaying = false;
		}

		switch(pGrid->GetState())
		{
		case Grid::State::Win:
			if (!sndVictoryPlaying)
			{
				sndVictory.Play(1.0f, 0.125f);
				sndVictoryPlaying = true;
			}
		case Grid::State::GameOver:
			waitTime = 1.0f;
			if (highScore < pGrid->GetScore())
			{
				highScore = pGrid->GetScore();
				std::ofstream bestScore("score.dat", std::ios::binary);
				bestScore.write(reinterpret_cast<char*>(&highScore), sizeof(highScore));
			}

			while (!wnd.mouse.IsEmpty())
			{
				const auto e = wnd.mouse.Read();
				if (e.GetType() == Mouse::Event::Type::LPress && !cooldownOn)
				{
					ResetGame();
				}
			}
			break;
		default:
			if (pGrid->GetState() == Grid::State::Playing)
			{
				showingWaitText = false;

				while (!wnd.mouse.IsEmpty())
				{
					const auto e = wnd.mouse.Read();
					if (e.GetType() == Mouse::Event::Type::LPress)
					{
						mousePos = e.GetPos();
						if (pGrid->GetRect().Contains(mousePos))
						{
							pGrid->OnSelectClick(mousePos, cooldownOn);
							cooldownOn = true;
						}
					}
				}
			}
			else if (pGrid->GetState() == Grid::State::Waiting)
			{
				pGrid->ShowPtrnSelection(cooldownOn);
				cooldownOn = true;
			}

			const std::string score = std::to_string(pGrid->GetScore());
			fullScore = roundHeaderTxt + score;
			break;
		}
	}
	else
	{
		if (sndVictoryPlaying)
		{
			sndVictory.StopAll();
			sndVictoryPlaying = false;
		}

		if (!sndTitlePlaying)
		{
			sndTitle.Play(1.0f, 0.125f);
			sndTitlePlaying = true;
		}

		std::ifstream inBestScore("score.dat", std::ios::binary);
		if (inBestScore)
		{
			inBestScore.read(reinterpret_cast<char*>(&highScore), sizeof(highScore));
		}
		else
		{
			highScore = 0;
		}

		while (!wnd.mouse.IsEmpty())
		{
			const auto e = wnd.mouse.Read();

			const SelectionMenu::Size s = menu.ProcessMouse(e);
			switch (s)
			{
			case SelectionMenu::Size::Small: // Total score: 1450
				CreateGrid(2, 2);
				onTitleScreen = false;
				break;
			case SelectionMenu::Size::Medium: // Total score: 1950
				CreateGrid(3, 3);
				onTitleScreen = false;
				break;
			case SelectionMenu::Size::Large: // Total score: 2650
				CreateGrid(4, 4);
				onTitleScreen = false;
				break;
			}
		}
	}
}

void Game::CreateGrid(int width, int height)
{
	pGrid = std::make_unique<Grid>(gfx.GetRect().GetCenter(), width, height);
	pGrid->AddWndToPtrn();
}

void Game::ResetGame()
{
	pGrid.reset();
	curWaitTime = 0.0f;
	waitTime = 0.5f;
	cooldownOn = false;
	showingWaitText = true;
	onTitleScreen = true;
}

void Game::ComposeFrame()
{
	if (!onTitleScreen)
	{
		switch (pGrid->GetState())
		{
		case Grid::State::Waiting:
			if (showingWaitText)
			{
				bigFont.DrawText(waitTxt, { (Graphics::ScreenWidth - (int(waitTxt.size()) * bigFont.GetGlyphWidth())) / 2, bigFont.GetGlyphHeight() / 2 }, { 0,135,255 }, gfx);
			}
			smallFont.DrawText(fullScore, { 0, 0 }, Colors::White, gfx);
			pGrid->Draw(gfx);
			break;
		case Grid::State::Playing:
			bigFont.DrawText(repeatTxt, { (Graphics::ScreenWidth - (int(repeatTxt.size()) * bigFont.GetGlyphWidth())) / 2, bigFont.GetGlyphHeight() / 2 }, Colors::Red, gfx);
			smallFont.DrawText(fullScore, { 0, 0 }, Colors::White, gfx);
			pGrid->Draw(gfx);
			break;
		case Grid::State::GameOver:
			boldFont.DrawText(gameOverTxt, { (Graphics::ScreenWidth - (int(gameOverTxt.size()) * boldFont.GetGlyphWidth())) / 2, boldFont.GetGlyphHeight() / 4 }, Colors::White, gfx);
			smallFont.DrawText(fullScore, { (Graphics::ScreenWidth - (int(fullScore.size()) * smallFont.GetGlyphWidth())) / 2, (boldFont.GetGlyphHeight() / 4) * 5 }, Colors::White, gfx);
			if (!cooldownOn)
			{
				smallFont.DrawText(prompt2Txt, { (Graphics::ScreenWidth - (int(prompt2Txt.size()) * smallFont.GetGlyphWidth())) / 2, Graphics::ScreenHeight - smallFont.GetGlyphHeight() * 2 }, Colors::Yellow, gfx);
			}
			pGrid->Draw(gfx);
			break;
		case Grid::State::Win:
			smallFont.DrawText(fullScore, { (Graphics::ScreenWidth - (int(fullScore.size()) * smallFont.GetGlyphWidth())) / 2, (boldFont.GetGlyphHeight() / 4) * 5 }, Colors::White, gfx);
			if (!cooldownOn)
			{
				smallFont.DrawText(prompt2Txt, { (Graphics::ScreenWidth - (int(prompt2Txt.size()) * smallFont.GetGlyphWidth())) / 2, Graphics::ScreenHeight - smallFont.GetGlyphHeight() * 2 }, Colors::Yellow, gfx);
			}
			gfx.DrawSprite((Graphics::ScreenWidth - 411) / 2, (Graphics::ScreenHeight - 301) / 2, victory, SpriteEffect::Chroma{ Colors::Black });
		}
	}
	else
	{
		gfx.DrawSprite((Graphics::ScreenWidth - 263) / 2, (Graphics::ScreenHeight - 89) / 4, title, SpriteEffect::Chroma{ Colors::Black });
		smallFont.DrawText(prompt1Txt, { (Graphics::ScreenWidth - (int(prompt1Txt.size()) * smallFont.GetGlyphWidth())) / 2, bigFont.GetGlyphHeight() * 5 }, Colors::Red, gfx);
		smallFont.DrawText(noticeTxt, { (Graphics::ScreenWidth - (int(noticeTxt.size()) * smallFont.GetGlyphWidth())) / 2, Graphics::ScreenHeight - smallFont.GetGlyphHeight() }, Colors::White, gfx);
		smallFont.DrawText(highScoreTxt + std::to_string(highScore), { 0, 0 }, Colors::White, gfx);
		menu.Draw(gfx);
	}
}