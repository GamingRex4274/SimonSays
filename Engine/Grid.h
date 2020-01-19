#pragma once

#include "Graphics.h"
#include "Vei2.h"
#include "Beveler.h"
#include <random>
#include <vector>

class Grid
{
public:
	enum class State
	{
		Waiting,
		Playing,
		GameOver
	};
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
		void Draw(Graphics& gfx, Color windowColor, Grid::State gridState);
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
	void AddWndToPtrn();
	void ResetWindows();
	void ShowPtrnSelection(bool cooldown);
	void OnSelectClick(const Vei2& screenPos, bool cooldown);
	int GetCurrentRound() const;
	RectI GetRect() const;
	State GetState() const;
private:
	void ProcessSelection(const Vei2& gridPos);
	int GetWndNum(const Vei2& gridPos) const;
	Window& WinAt(const Vei2& gridPos); // Returns reference to a window on the grid.
	Vei2 ScreenToGrid(const Vei2& screenPos);
private:
	// Colors for each window: cyan, yellow, green and magenta.
	static constexpr Color windowColors[4] = { {25,230,230},{230,230,25},{25,230,25},{230,25,230} };
	static constexpr int width = 2; // Width and height = amount of windows on grid.
	static constexpr int height = 2;
	static constexpr int windowSize = 200; // Dimensions of each window.
	static constexpr int nMaxRounds = 15;
	Vei2 topLeft;
	Window grid[width * height];
	State state = State::Waiting;
	std::vector<int> wndPattern;
	int ptrnIndex = 0;
	int curRound = 0;
	bool lockedOnWin = false; // Indicates whether to stay on one window or to select a new window.
};