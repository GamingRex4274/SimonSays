#include "SelectionMenu.h"

SelectionMenu::Entry::Entry(const RectI& rect, const Font& font, const std::string& text, Size s)
	:
	rect(rect),
	font(font),
	text(text),
	s(s)
{
}

void SelectionMenu::Entry::Draw(Graphics& gfx) const
{
	if (highlighted)
	{
		gfx.DrawRect(rect.GetExpanded(highlightThickness), highlightColor);
	}
	gfx.DrawRect(rect, Colors::Black);
	font.DrawText(text, { rect.left, rect.top }, Colors::White, gfx);
}

SelectionMenu::SelectionMenu(const Vei2& pos, const Font& font)
{
	const int fontWidth = font.GetGlyphWidth();
	const int fontHeight = font.GetGlyphHeight();

	entries.reserve(int(Size::Count));
	Vei2 curPos = pos;
	for (int i = 0; i < int(Size::Count); i++)
	{
		const std::string str = EnumToStr(Size(i));
		entries.emplace_back(RectI(Vei2(curPos.x, curPos.y + (i * fontHeight)), int(str.size()) * fontWidth, fontHeight), font, str, Size(i));
		curPos.y += verticalSpace;
	}
}

void SelectionMenu::Draw(Graphics& gfx) const
{
	for (const Entry& e : entries)
	{
		e.Draw(gfx);
	}
}

std::string SelectionMenu::EnumToStr(Size size)
{
	std::string str;

	switch (size)
	{
	case Size::Small:
		str = "SMALL";
		break;
	case Size::Medium:
		str = "MEDIUM";
		break;
	case Size::Large:
		str = "LARGE";
		break;
	}

	return str;
}
