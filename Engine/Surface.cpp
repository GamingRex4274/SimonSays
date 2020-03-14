#include "Surface.h"
#include <cassert>
#include <fstream>
#include "ChiliWin.h"

Surface::Surface(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	assert(file);

	BITMAPFILEHEADER bmpFileHeader;
	file.read(reinterpret_cast<char*>(&bmpFileHeader), sizeof(bmpFileHeader)); // Read bitmap file header into object.

	BITMAPINFOHEADER bmpInfoHeader;
	file.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(bmpInfoHeader)); // Read bitmap info header into object.

	// File must have 24-bit or 32-bit depth.
	assert(bmpInfoHeader.biBitCount == 24 || bmpInfoHeader.biBitCount == 32);
	// File must have no compression.
	assert(bmpInfoHeader.biCompression == BI_RGB);

	const bool is32Bit = bmpInfoHeader.biBitCount == 32;

	width = bmpInfoHeader.biWidth;

	// Calculate height and Y based on row order.
	int yStart;
	int yEnd;
	int dy;

	if (bmpInfoHeader.biHeight < 0)
	{
		height = -bmpInfoHeader.biHeight;
		yStart = 0;
		yEnd = height;
		dy = 1;
	}
	else
	{
		height = bmpInfoHeader.biHeight;
		yStart = height - 1;
		yEnd = -1;
		dy = -1;
	}

	pPixels = new Color[width * height];

	file.seekg(bmpFileHeader.bfOffBits);
	// Calculate padding for 24-bit depth only.
	const int padding = (4 - (width * 3) % 4) % 4;

	for (int y = yStart; y != yEnd; y += dy) // Loop Y based on previous calculation.
	{
		for (int x = 0; x < width; x++)
		{
			PutPixel(x, y, Color(file.get(), file.get(), file.get()));
			if (is32Bit)
			{
				file.seekg(1, std::ios::cur);
			}
		}
		if (!is32Bit)
		{
			file.seekg(padding, std::ios::cur);
		}
	}
}

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	pPixels(new Color[width * height])
{
}

Surface::Surface(const Surface& rhs)
	:
	Surface(rhs.width, rhs.height)
{
	const int nPixels = width * height;
	for (int i = 0; i < nPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
}

Surface::~Surface()
{
	delete[] pPixels;
	pPixels = nullptr;
}

Surface& Surface::operator=(const Surface& rhs)
{
	width = rhs.width;
	height = rhs.height;

	delete[] pPixels;
	pPixels = new Color[width * height];

	const int nPixels = width * height;
	for (int i = 0; i < nPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}

	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pPixels[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return pPixels[y * width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

RectI Surface::GetRect() const
{
	return { 0, width, 0, height };
}