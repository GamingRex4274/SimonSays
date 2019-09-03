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
		bev.SetBaseColor(windowColor); // Sets color of unselected window to its assigned color.
		break;
	case State::Selected:
		bev.SetBaseColor({ 230,230,230 }); // Sets color of selected window to white.
		break;
	}
	bev.DrawBeveledBrick(rect.GetExpanded(-padding), bevelSize, gfx);
}

void Grid::Window::ToggleSelect()
{
	if (state == State::Unselected)
	{
		state = State::Selected;
	}
	else
	{
		state = State::Unselected;
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

void Grid::OnSelectClick(const Vei2& screenPos)
{
	const Vei2 gridPos = ScreenToGrid(screenPos);
	assert(gridPos.x >= 0 && gridPos.x < width && gridPos.y >= 0 && gridPos.y < height);
	WinAt(gridPos).ToggleSelect();
}

RectI Grid::GetRect() const
{
	return RectI(topLeft, width * windowSize, height * windowSize);
}

Grid::Window& Grid::WinAt(const Vei2& gridPos)
{
	// Returns index of 2D array for one window.
	return grid[gridPos.y * width + gridPos.x];
}

Vei2 Grid::ScreenToGrid(const Vei2& screenPos)
{
	return (screenPos - topLeft) / windowSize;
}