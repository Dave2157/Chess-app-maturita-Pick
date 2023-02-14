#pragma once
#include "olcPixelGameEngine.h"
#include "BoardAndUtils.h"

using namespace olc;

class GameEngine : public PixelGameEngine
{
	Board activeBoard;

	void drawBoard();
	void drawPawn(int x, int y, Pixel colour);
	void drawRook(int x, int y, Pixel colour);
	void drawKnight(int x, int y, Pixel colour);
	void drawBishop(int x, int y, Pixel colour);
	void drawQueen(int x, int y, Pixel colour);
	void drawKing(int x, int y, Pixel colour);



public:
	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float elapsedTime);
};