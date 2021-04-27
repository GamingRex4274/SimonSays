#pragma once

#include "Graphics.h"
#include "Vei2.h"
#include "Beveler.h"
#include <random>
#include <vector>
#include <memory>
#include "Sound.h"

class Grid
{
public:
	enum class State
	{
		Waiting,
		Playing,
		GameOver,
		Win
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
		Window(const RectI& rect, Color color, float sndPitch);
		void Draw(Graphics& gfx, int bevelSize, Grid::State gridState);
		void ToggleSelect();
		bool IsSelected() const;
	private:
		Color color;
		RectI rect;
		Beveler bev;
		State state = State::Unselected;
		Sound sndSelect = L"Sounds\\window.wav";
		float sndPitch;
		static constexpr int padding = 5; // Space between windows.
	};
public:
	Grid(const Vei2& center, int width, int height, bool freeplayOn = false);
	void Draw(Graphics& gfx);
	void AddWndToPtrn();
	void ResetWindows();
	void ShowPtrnSelection(bool cooldown);
	void OnSelectClick(const Vei2& screenPos, bool cooldown);
	int GetScore() const;
	RectI GetRect() const;
	State GetState() const;
private:
	void ProcessSelection(const Vei2& gridPos);
	int GetWndNum(const Vei2& gridPos) const;
	Window& WinAt(const Vei2& gridPos); // Returns reference to a window on the grid.
	Vei2 ScreenToGrid(const Vei2& screenPos);
private:
	int width; // Width and height = amount of windows on grid.
	int height;
	int windowSize; // Dimensions of each window.
	int wndBevelSize; // Size of shading.
	int nMaxRounds;
	Vei2 topLeft;
	std::unique_ptr<Window[]> grid;
	State state = State::Waiting;
	std::vector<int> wndPattern;
	int ptrnIndex = 0;
	int curRound = 0;
	int score = 0;
	bool lockedOnWin = false; // Indicates whether to stay on one window or to select a new window.
	static constexpr int nWndColors = 16;
	// Colors of each window.
	static constexpr Color windowColors[nWndColors] = {
		{25, 230, 25},	 // Lime
		{230, 25, 25},	 // Red
		{230, 230, 25},  // Yellow
		{25, 25, 230},	 // Blue
		{230, 135, 25},  // Orange
		{135, 25, 230},  // Purple
		{25, 230, 230},  // Cyan
		{230, 25, 230},	 // Magenta
		{100, 50, 0},    // Brown
		{230, 135, 230}, // Pink
		{25, 135, 25},	 // Green
		{25, 135, 135},  // Teal
		{135, 25, 25},   // Maroon
		{105, 105, 105}, // Dark Gray
		{25, 25, 135},   // Navy
		{230, 205, 25}	 // Gold
	};
};