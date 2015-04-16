#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "HansBmpImage.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
// Oppgavene...
//////////////////////////////////////////////////////////////////////////////////////////////

void oppgave_4_1_coordsOK()
{
	HansBmpImage img;
	if (!img.load("img-303x303.bmp")) {
		cout << "oppgave_4_1_coordsOK(): Feil ved åpning av fil" << endl;
		exit(-1);
	}
	bool error = true;

// Fjern // fra neste linjen for å teste om coordsOK() fungerer.
	//error = img.coordsOK(1000, 1000) || img.coordsOK(303, 303) || img.coordsOK(-1, -1) || !img.coordsOK(0, 0);

	if (error) {
		cout << "oppgave_4_1_coordsOK(): Error testing coordsOK()" << endl;
		exit(0);
	}
}


void oppgave_4_2_getR()
{
	HansBmpImage img;
	if (!img.load("img-10x9.bmp")) {
		cout << "oppgave_4_2_setRGB(): Feil ved åpning av fil" << endl;
		exit(-1);
	}

	for (int y = 0; y < img.getHeight(); ++y) {
		for (int x = 0; x < img.getWidth(); ++x) {
			img.setRGB(x, y, x, y, 255-x);
		}
	}

	// Test: This code verifies the whole picture
	for (int y = 0; y < img.getHeight(); ++y) {
		for (int x = 0; x < img.getWidth(); ++x) {
			// Fjern // fra neste linjen for å teste om coordsOK() fungerer. Kopier koden for å teste getG() og getB()!
			//if (img.getR(x, y) != x) 
				{
					cout << "oppgave_4_2_setRGB(): Error testing getR()" << endl;
					exit(0);
				}
		}
	}
}


void oppgave_4_3_structs()
{
	HansBmpImage img;
	if (!img.load("img-345x135.bmp")) {
		cout << "oppgave_4_3_structs(): Feil ved åpning av fil" << endl;
		exit(-1);
	}

	cout << "oppgave_4_3_structs(): setAllRGB() er ikke brukt!" << endl; exit(0); // Erstatt denne linjen med kode som setter piksel vha. strukturene. Sjekk output fila!
	//Point p;
	//p.x = ....
	//Color c;
	//c.r = ....
	//img.setRGB(p, c);

	//img.save("structs.bmp");
}


void oppgave_4_4_getRGB()
{
	HansBmpImage img;
	if (!img.load("img-10x9.bmp")) {
		cout << "oppgave_4_4_getRGB(): Feil ved åpning av fil" << endl;
		exit(-1);
	}

	for (int y = 0; y < img.getHeight(); ++y) {
		for (int x = 0; x < img.getWidth(); ++x) {
			img.setRGB(x, y, x, y, 0);
		}
	}

	// Test: This code verifies the whole picture
	for (int y = 0; y < img.getHeight(); ++y) {
		for (int x = 0; x < img.getWidth(); ++x) {
			// Fjern // fra neste linjen for å teste om coordsOK() fungerer. Kopier koden for å teste getG() og getB()!
			//if (img.getR(x, y) != x) 
				{
					cout << "oppgave_4_3_setRGB(): Error testing getR()" << endl;
					exit(0);
				}
		}
	}
}


void oppgave_4_5_brown()
{
	HansBmpImage img;
	if (!img.load("img-345x135.bmp")) {
		cout << "oppgave_4_5_brown(): Feil ved åpning av fil" << endl;
		exit(-1);
	}

	cout << "oppgave_4_5_brown(): setAllRGB() er ikke brukt!" << endl; exit(0); // Erstatt denne linjen med en linje som endrer hele bildet til brunt.

	img.sign();
	img.save("brown.bmp");
}


void oppgave_4_6_sun()
{
	HansBmpImage img;
	if (!img.load("img-345x135.bmp")) {
		cout << "oppgave_4_6_sun(): Feil ved åpning av fil" << endl;
		exit(-1);
	}

	int centerX = img.getWidth() / 2;
	int centerY = img.getHeight() / 2;

	int maxradius = centerX < centerY ? centerX : centerY;
	double startradius = 0.3 * maxradius;
	double endradius = 0.9 * maxradius;

	cout << "oppgave_4_6_sun(): setAllRGB() er ikke brukt!" << endl; exit(0); // Erstatt denne kodelinjen med en linje som endrer hele bildet til blått.

	int sunradius = int(startradius + 0.5);
	cout << "oppgave_4_6_sun(): Hvor er sola?" << endl; exit(0); // Erstatt denne kodelinjen med en som tegner ei gul sol i senteret av bildet med rett radius.

	double step = 2*M_PI / 32;
	for (double angle = 0.0; angle < 2*M_PI; angle += step) {
		int x0 = centerX + int(0. + startradius * cos(angle));
		//int y0 = ....ikke cos() men....
		//int x1 = centerX + int(0. + endradius .............
		cout << "oppgave_4_6_sun(): Hvor er strålene?" << endl; exit(0); // Erstatt denne kodelinjen med en som tegner en gul linje. Bruk x0, y0, x1 og x2
	}

	img.sign();
	img.save("sun.bmp");
}


void oppgave_4_7_greyscale()
{
	HansBmpImage img;
	if (!img.load("Kimberley.bmp")) {
		cout << "oppgave_4_7_greyscale(): Feil ved åpning av fil" << endl;
		exit(-1);
	}

// Fjern // fra neste linjen
	//img.convertToGreyScale();

	img.sign();
	img.save("Kimberley_greyscale.bmp");
}


void oppgave_4_8_flip()
{
	HansBmpImage img;
	if (!img.load("Kimberley.bmp")) {
		cout << "oppgave_4_8_flip(): Feil ved åpning av fil" << endl;
		exit(-1);
	}

// Fjern // fra neste linjen
	//img.mirror();

	img.sign();
	img.save("Kimberley_flipped.bmp");
}

