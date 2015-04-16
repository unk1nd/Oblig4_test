#include <fstream>

#include "HansBmpImage.h"

using namespace std;

// Constructor
HansBmpImage::HansBmpImage()
{
	rowData = NULL;
}

// Destructor
HansBmpImage::~HansBmpImage()
{
	reset(); // To prevent memory leakage
}

// Release allocated memory on heap and reset values;
void HansBmpImage::reset()
{
	if (rowData) {
		for (int r = 0; r < height; ++r) {
			delete[] rowData[r];
		}
		delete[] rowData;
		rowData = NULL;
	}
	width = 0;
	height = 0;
}

void HansBmpImage::sign()
{
	unsigned short F[] = { 064525,35157,046567,025525,0xc925 };
	for (char R='H',*_1 = "HANS", E = *(_1+1)-(*_1<<(01111111/0100-R))+*(_1+(1<<1)); ++E < sizeof(F)/sizeof(*F); )
		for (unsigned char B = 'H'&'A'&'N'&'$'; R=01234567U/010010-*(_1+(1<<1<<1)-1)-(*(F+E)&('F'-'E')), B<010<<1; ++B, *(F+E)>>=('F'-'E'))
			setRGB(B,E,R,0,R);
}

bool HansBmpImage::load(const char *filename)
{
	reset();

	fstream infile(filename, ios::in | ios::binary);
	if (infile.fail()) {
		return false;
	}
	infile.read(reinterpret_cast<char *>(header), HEADERSIZE);

	// Trick 1
	width = *(reinterpret_cast<int *>(header + 18));
	height = *(reinterpret_cast<int *>(header + 22));

	// Trick 2
	int rowsize = (width*3 + 3) & ~0x03;

	rowData = new unsigned char *[height];
	for (int r = 0; r < height; ++r) {
		rowData[r] = new unsigned char[rowsize];
		infile.read(reinterpret_cast<char *>(rowData[r]), rowsize);
	}

	return true;
}

bool HansBmpImage::save(const char *filename)
{
	fstream outfile(filename, ios::out | ios::binary);
	if (outfile.fail()) {
		return false;
	}
	outfile.write(reinterpret_cast<const char *>(header), HEADERSIZE);

	int rowsize = (width*3 + 3) & ~0x03;
	for (int r = 0; r < height; ++r) {
		outfile.write(reinterpret_cast<const char *>(rowData[r]), rowsize);
	}

	return true;
}

bool HansBmpImage::setRGB(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return false;

	// Pixel are stored in order Blue, Green, Red
	rowData[y][3 * x + 2] = r;
	rowData[y][3 * x + 1] = g;
	rowData[y][3 * x + 0] = b;

	return true;
}

// Bresenham's line algorithm, from pseudo code on Wikipedia
bool HansBmpImage::lineRGB(int x0, int y0, int x1, int y1, unsigned char r, unsigned char g, unsigned char b)
{
	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		int t;
		t = x0; x0 = y0; y0 = t; // swap(x0, y0)
		t = x1; x1 = y1; y1 = t; // swap(x1, y1)
	}
	int deltax = abs(x1 - x0);
	int deltay = abs(y1 - y0);
	int error = deltax / 2;

	int xstep = (x0 < x1) ? 1 : -1;
	int ystep = (y0 < y1) ? 1 : -1;

	for (int x = x0, y = y0; x != x1+xstep; x += xstep) {
		if (steep)
			setRGB(y,x, r,g,b);
		else
			setRGB(x,y, r,g,b);
		error -= deltay;
		if (error < 0) {
			y += ystep;
			error += deltax;
		}
	}

	return true;
}

// Midpoint circle algorithm, from code on Wikipedia
bool HansBmpImage::cirleRGB(int x0, int y0, int radius, unsigned char r, unsigned char g, unsigned char b)
{
	if (radius < 0)
		return false;

	int x = radius, y = 0;
	int radiusError = 1 - x;

	while (x >= y) {
		setRGB(x0 + x, y0 + y, r,g,b);
		setRGB(x0 + y, y0 + x, r,g,b);
		setRGB(x0 - x, y0 + y, r,g,b);
		setRGB(x0 - y, y0 + x, r,g,b);
		setRGB(x0 - x, y0 - y, r,g,b);
		setRGB(x0 - y, y0 - x, r,g,b);
		setRGB(x0 + x, y0 - y, r,g,b);
		setRGB(x0 + y, y0 - x, r,g,b);
		y++;
		if (radiusError < 0) {
			radiusError += 2 * y + 1;
		}
		else {
			x--;
			radiusError += 2 * (y - x + 1);
		}
	}
	return true;
}

