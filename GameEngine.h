#pragma once
#include "olcPixelGameEngine.h"
#include "BoardAndUtils.h"

using namespace olc;

class GameEngine : public PixelGameEngine
{
	Board activeBoard;
	bool savedGame;
	int menuState;
	bool playing;
	char p1set;
	char p2set;

	void drawBoard();
	void drawPawn(int x, int y, Pixel colour);
	void drawRook(int x, int y, Pixel colour);
	void drawKnight(int x, int y, Pixel colour);
	void drawBishop(int x, int y, Pixel colour);
	void drawQueen(int x, int y, Pixel colour);
	void drawKing(int x, int y, Pixel colour);

	void drawLetter(char letter, int size, int x, int y, Pixel colour);
	void drawString(string word, int size, int x, int y, Pixel colour);
	bool makeButton(int x, int y, string text, int width, int height, int textSize, Pixel textColour, Pixel textHoverColour, Pixel bgColour, Pixel hoverColour, int menuStateChange);



public:
	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float elapsedTime);
};