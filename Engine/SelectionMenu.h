#pragma once

#include "RectI.h"
#include "Font.h"
#include <vector>

class SelectionMenu
{
public:
	enum class Size
	{
		Small,
		Medium,
		Large,
		Count,
		Invalid
	};
private:
	class Entry
	{
	public:
		Entry(const RectI& rect, const Font& font, const std::string& text, Size s);
		void Draw(Graphics& gfx) const;
	private:
		Size s;
		RectI rect;
		Font font;
		std::string text;
		static constexpr Color highlightColor = Colors::Yellow;
		static constexpr int highlightThickness = 5;
		bool highlighted = true;
	};
public:
	SelectionMenu(const Vei2& pos, const Font& font);
	void Draw(Graphics& gfx) const;
private:
	std::string EnumToStr(Size size);
private:
	std::vector<Entry> entries;
	static constexpr int verticalSpace = 20;
};