#pragma once

#include "Vei2.h"

class RectI
{
public:
	RectI() = default;
	RectI(int left, int right, int top, int bottom); // Creates rect with 4 sides.
	RectI(const Vei2& topLeft, const Vei2& bottomRight); // Creates rect with 2 vectors (top-left and bottom-right).
	RectI(const Vei2& topLeft, int width, int height); // Creates rect with a top-left vector and dimensions.
	bool IsOverlappingWith(const RectI& other) const;
	bool IsContainedBy(const RectI& other) const;
	bool Contains(const Vei2& point) const;
	static RectI FromCenter(const Vei2& center, int halfWidth, int halfHeight); // Creates rectangle with center origin.
	RectI GetExpanded(int offset) const; // Gets an expanded version of a rect.
	Vei2 GetCenter() const;
	int GetWidth() const;
	int GetHeight() const;
public:
	int left;
	int right;
	int top;
	int bottom;
};