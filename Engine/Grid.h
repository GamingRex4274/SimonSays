#pragma once

#include "Graphics.h"
#include "Vei2.h"
#include "Beveler.h"
#include <random>

class Grid
{
private:
	class Window
	{
	private:
		enum class State
		{
			Selected,
			Unselected
		};
	public:
		Window() = default;
		Window(const RectI& rect);
		void Draw(Graphics& gfx, Color windowColor);
		void ToggleSelect();
		bool IsSelected() const;
	private:
		RectI rect;
		Beveler bev;
		State state = State::Unselected;
		static constexpr int padding = 5; // Space between windows.
		static constexpr int bevelSize = 16; // Size of shading.
	};
public:
	Grid(const Vei2& center);
	void Draw(Graphics& gfx);
	void RandomSelection(bool cooldown);
	void OnSelectClick(const Vei2& screenPos);
	RectI GetRect() const;
private:
	Window& WinAt(const Vei2& gridPos); // Returns reference to a window on the grid.
	Vei2 ScreenToGrid(const Vei2& screenPos);
private:
	Vei2 topLeft;
	static constexpr int width = 2; // Width and height = amount of windows on grid.
	static constexpr int height = 2;
	static constexpr int windowSize = 200; // Dimensions of each window.
	// Colors for each window: cyan, yellow, green and magenta.
	static constexpr Color windowColors[4] = { {25,230,230},{230,230,25},{25,230,25},{230,25,230} };
	Window grid[width * height];
	std::mt19937 rng;
	std::uniform_int_distribution<int> nDist;
	int randomTimes = 0;
	int rw;
};