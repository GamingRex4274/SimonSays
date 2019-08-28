#pragma once

#include "Graphics.h"
#include "Vei2.h"

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
		void Draw(Graphics& gfx, Color windowColor) const;
		void ToggleSelect();
		bool IsSelected() const;
	private:
		RectI rect;
		State state = State::Unselected;
		static constexpr int padding = 5; // Space between windows.
	};
public:
	Grid(const Vei2& center);
	void Draw(Graphics& gfx);
	void OnSelectClick(const Vei2& screenPos);
	RectI GetRect() const;
private:
	Window& WinAt(const Vei2& gridPos);
	Vei2 ScreenToGrid(const Vei2& screenPos);
private:
	Vei2 topLeft;
	static constexpr int width = 2; // Width and height = amount of windows on grid.
	static constexpr int height = 2;
	static constexpr int windowSize = 200; // Dimensions of each window.
	static constexpr Color windowColors[4] = { Colors::Cyan,Colors::Yellow,Colors::Green,Colors::Magenta };
	Window grid[width * height];
};