#ifndef HANSBMPIMAGE_H
#define HANSBMPIMAGE_H

struct Point;
struct Color;

class HansBmpImage {
public:
	HansBmpImage();
	~HansBmpImage();

	void reset();
	bool load(const char *filename);
	bool save(const char *filename);
	void sign();

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	bool setRGB(int x, int y, unsigned char r, unsigned char g, unsigned char b);
	bool lineRGB(int x0, int y0, int x1, int y1, unsigned char r, unsigned char g, unsigned char b);
	bool cirleRGB(int x0, int y0, int radius, unsigned char r, unsigned char g, unsigned char b);

	///////////////////// Obligatoriske oppgaver............ /////////////////////////////////
	bool coordsOK(int x, int y); // oppgave_4_1_coordsOK
	unsigned char getR(int x, int y); // oppgave_4_2_getR
	unsigned char getG(int x, int y);
	unsigned char getB(int x, int y);
	//Color getRGB(...); // oppgave_4_4_getRGB
	//bool setAllRGB(...); // oppgave_4_5_brown
	void convertToGreyScale(); // oppgave_4_7_greyscale
	void flip(); // oppgave_4_8_flip
	//////////////////////////////////////////////////////////////////////////////////////////

	///////////////////// Ikke-obligatoriske oppgaver............ ////////////////////////////
	bool rektangelRGB(int x0, int y0, int x1, int y1, unsigned char r, unsigned char g, unsigned char b, bool fylt = true); // oppgave_5_1
	void mirror(); // oppgave_5_2
	void edge(); // oppgave_5_3
	//////////////////////////////////////////////////////////////////////////////////////////

private:
	int width, height;

	static const int HEADERSIZE = 54;
	unsigned char header[HEADERSIZE];
	unsigned char **rowData;

private:
	//Disse linjer sørger for at objekter ikke kan kopieres med uhell.
	HansBmpImage(const HansBmpImage &); 
	HansBmpImage& operator=(HansBmpImage const&);
};

#endif // HANSBMPIMAGE_H
