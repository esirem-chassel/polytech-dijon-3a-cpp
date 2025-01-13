#include "bitmap.h"
#include <algorithm>
#include <iostream>


Bitmap::Bitmap()
	: width(0), height(0), lineWidth(0), pixels()
{
}

Bitmap::Bitmap(unsigned int w, unsigned int h)
	: Bitmap()
{
	resize(w, h);
}

void Bitmap::resize(unsigned int w, unsigned int h)
{
	width = w;
	height = h;

	pixels.clear();

	unsigned int padding = (width * 3) % 4;

	if (padding != 0)
		padding = 4 - padding;

	lineWidth = width * 3 + padding;

	pixels.resize(lineWidth * height, 0);
}

void Bitmap::setPixelColor(unsigned int x, unsigned int y, unsigned char red, unsigned char green, unsigned char blue)
{
	const unsigned int iPixel = ((height - y - 1) * lineWidth + (x * 3));

	pixels[iPixel + 2] = red;
	pixels[iPixel + 1] = green;
	pixels[iPixel] = blue;
}

unsigned int Bitmap::getHeaderSize() const
{
	return 14;
}

unsigned int Bitmap::getInfoSize() const
{
	return 40;
}

unsigned int Bitmap::getPixelsSize() const
{
	return width * height * 3;
}

void Bitmap::save(const std::string& fileName) const
{
	std::ofstream file(fileName, std::ios_base::binary);

	if (file.is_open())
	{
		saveHeader(file);
		saveInfo(file);
		savePixels(file);

		file.close();
	}
}

void Bitmap::saveHeader(std::ofstream& file) const
{
	const unsigned int fileSize = getHeaderSize() + getInfoSize() + getPixelsSize();
	const unsigned short reserved = 0;
	const unsigned int offset = getHeaderSize() + getInfoSize();

	file.write("BM", 2);
	file.write((char*)&fileSize, sizeof(fileSize));
	file.write((char*)&reserved, sizeof(reserved));
	file.write((char*)&reserved, sizeof(reserved));
	file.write((char*)&offset, sizeof(offset));
}

void Bitmap::saveInfo(std::ofstream& file) const
{
	const unsigned int infoSize = getInfoSize();
	const unsigned short plans = 1;
	const unsigned short bitPerPixels = 24;
	const unsigned int compression = 0;
	const unsigned int imageSize = getPixelsSize();
	const unsigned int resolution = 200;
	const unsigned int zero = 0;

	file.write((char*)&infoSize, sizeof(infoSize));
	file.write((char*)&width, sizeof(width));
	file.write((char*)&height, sizeof(height));
	file.write((char*)&plans, sizeof(plans));
	file.write((char*)&bitPerPixels, sizeof(bitPerPixels));
	file.write((char*)&compression, sizeof(compression));
	file.write((char*)&imageSize, sizeof(imageSize));
	file.write((char*)&resolution, sizeof(resolution));
	file.write((char*)&resolution, sizeof(resolution));
	file.write((char*)&zero, sizeof(zero));
	file.write((char*)&zero, sizeof(zero));
}

void Bitmap::savePixels(std::ofstream& file) const
{
	file.write((char*)pixels.data(), lineWidth * height);
}
