#include "Grid.h"
#include <assert.h>

Grid::Window::Window(const RectI& rect)
	:
	rect(rect)
{
}

void Grid::Window::Draw(Graphics& gfx, Color windowColor)
{
	// Draws a window with top-left origin.
	switch (state)
	{
	case State::Unselected:
		bev.SetBaseColor(windowColor); // Gives unselected window its assigned color.
		break;
	case State::Selected:
		bev.SetBaseColor({ 230,230,230 }); // Gives selected window a white color.
		break;
	}
	bev.DrawBeveledBrick(rect.GetExpanded(-padding), bevelSize, gfx);
}

void Grid::Window::ToggleSelect()
{
	switch (state)
	{
	case State::Unselected:
		state = State::Selected;
		break;
	case State::Selected:
		state = State::Unselected;
		break;
	}
}

bool Grid::Window::IsSelected() const
{
	return state == State::Selected;
}

Grid::Grid(const Vei2& center)
	:
	topLeft(center - Vei2(width, height) * windowSize / 2) // Center of screen.
{
	for (Vei2 gridPos = { 0,0 }; gridPos.y < height; gridPos.y++)
	{
		for (gridPos.x = 0; gridPos.x < width; gridPos.x++)
		{
			// Temporary window object gets constructed and stored in reference.
			WinAt(gridPos) = Window(RectI(gridPos * windowSize + topLeft, windowSize, windowSize));
		}
	}
}

void Grid::Draw(Graphics& gfx)
{
	for (Vei2 gridPos = { 0,0 }; gridPos.y < height; gridPos.y++)
	{
		for (gridPos.x = 0; gridPos.x < width; gridPos.x++)
		{
			WinAt(gridPos).Draw(gfx, windowColors[gridPos.y * width + gridPos.x]);
		}
	}
}

void Grid::AddWndToPtrn()
{
	assert(curRound < nMaxRounds);
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> nDist(0, width * height - 1);
	wndPattern.push_back(nDist(rng));
}

void Grid::ResetWindows()
{
	for (Window& w : grid)
	{
		if (w.IsSelected())
		{
			w.ToggleSelect();
			break; // Stop checking remaining windows if one selected window has been found.
		}
	}
}

void Grid::ShowPtrnSelection(bool cooldown)
{
	assert(!wndPattern.empty());
	if (!cooldown) // If the grid is not on cooldown, execute next window selection.
	{
		if (!lockedOnWin)
		{
			if (ptrnIndex <= curRound)
			{
				grid[wndPattern[ptrnIndex++]].ToggleSelect();
				lockedOnWin = true;
			}
			else
			{
				ptrnIndex = 0;
				state = State::Playing;
			}
		}
		else
		{
			lockedOnWin = false;
		}
	}
}

void Grid::OnSelectClick(const Vei2& screenPos, bool cooldown)
{
	if (!cooldown)
	{
		const Vei2 gridPos = ScreenToGrid(screenPos);
		assert(gridPos.x >= 0 && gridPos.x < width && gridPos.y >= 0 && gridPos.y < height);
		WinAt(gridPos).ToggleSelect();
		ProcessSelection(gridPos);
	}
}

RectI Grid::GetRect() const
{
	return RectI(topLeft, width * windowSize, height * windowSize);
}

Grid::State Grid::GetState() const
{
	return state;
}

void Grid::ProcessSelection(const Vei2& gridPos)
{
	assert(!wndPattern.empty());
	ptrnIndex++;
	if (ptrnIndex <= curRound)
	{
		if (GetWndNum(gridPos) != wndPattern[ptrnIndex - 1])
		{
			state = State::GameOver;
		}
	}
	else
	{
		ptrnIndex = 0;
		curRound++;
		AddWndToPtrn();
		state = State::Waiting;
	}
}

int Grid::GetWndNum(const Vei2& gridPos) const
{
	// Returns value of window at a certain gridPos.
	return gridPos.y * width + gridPos.x;
}

Grid::Window& Grid::WinAt(const Vei2& gridPos)
{
	// Returns index of 2D array for one window.
	return grid[gridPos.y * width + gridPos.x];
}

Vei2 Grid::ScreenToGrid(const Vei2& screenPos)
{
	// Converts screen position into a grid position.
	return (screenPos - topLeft) / windowSize;
}