#include "Grid.h"

Grid::Window::Window(const RectI& rect)
	:
	rect(rect)
{
}

void Grid::Window::Draw(Graphics& gfx, Color windowColor) const
{
	switch (state)
	{
	case State::Unselected:
		gfx.DrawRect(rect.GetExpanded(-padding), windowColor);
		break;
	case State::Selected:
		gfx.DrawRect(rect.GetExpanded(-padding), Colors::White);
		break;
	}
}

Grid::Grid(const Vei2& center)
	:
	topLeft(center - Vei2(width, height) * windowSize / 2)
{
	for (Vei2 gridPos = { 0,0 }; gridPos.y < height; gridPos.y++)
	{
		for (gridPos.x = 0; gridPos.x < width; gridPos.x++)
		{
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

Grid::Window& Grid::WinAt(const Vei2& gridPos)
{
	return grid[gridPos.y * width + gridPos.x];
}