#include "GameEngine.h"

void GameEngine::drawBoard()
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			FillRect(x * 16, y * 16, 16, 16, (x + y) % 2 == 0 ? Pixel(244, 188, 111) : Pixel(148, 120, 81));   // opt
		}
	}

	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
		{
			switch (activeBoard.layout[x][y])
			{
			case 'P':
				drawPawn(y * 16, x * 16, WHITE);
				break;
			case 'p':
				drawPawn(y * 16, x * 16, BLACK);
				break;
			case 'R':
				drawRook(y * 16, x * 16, WHITE);
				break;
			case 'r':
				drawRook(y * 16, x * 16, BLACK);
				break;
			case 'N':
				drawKnight(y * 16, x * 16, WHITE);
				break;
			case 'n':
				drawKnight(y * 16, x * 16, BLACK);
				break;
			case 'B':
				drawBishop(y * 16, x * 16, WHITE);
				break;
			case 'b':
				drawBishop(y * 16, x * 16, BLACK);
				break;
			case 'Q':
				drawQueen(y * 16, x * 16, WHITE);
				break;
			case 'q':
				drawQueen(y * 16, x * 16, BLACK);
				break;
			case 'K':
				drawKing(y * 16, x * 16, WHITE);
				break;
			case 'k':
				drawKing(y * 16, x * 16, BLACK);
				break;
			}
		}

}
void GameEngine::drawPawn(int x, int y, Pixel colour)
{

	FillRect(x + 7, y + 2, 2, 12, colour);
	FillTriangle(vi2d(x + 6, y + 10), vi2d(x + 6, y + 13), vi2d(x + 3, y + 13), colour);
	FillTriangle(vi2d(x + 9, y + 10), vi2d(x + 9, y + 13), vi2d(x + 12, y + 13), colour);
	FillRect(x + 5, y + 3, 1, 3, colour);
	FillRect(x + 10, y + 3, 1, 3, colour);
	FillRect(x + 6, y + 2, 1, 5, colour);
	FillRect(x + 9, y + 2, 1, 5, colour);


}
void GameEngine::drawRook(int x, int y, Pixel colour)
{
	FillRect(x + 3, y + 12, 10, 2, colour);
	FillRect(x + 4, y + 11, 8, 1, colour);
	FillRect(x + 5, y + 4, 6, 7, colour);
	FillRect(x + 3, y + 2, 2, 3, colour);
	FillRect(x + 11, y + 2, 2, 3, colour);
	FillRect(x + 6, y + 2, 4, 2, colour);
	Draw(x + 4, y + 5, colour);
	Draw(x + 11, y + 5, colour);
}
void GameEngine::drawKnight(int x, int y, Pixel colour)
{
	FillRect(x + 3, y + 13, 10, 1, colour);
	FillTriangle(vi2d(x + 4, y + 12), vi2d(x + 8, y + 12), vi2d(x + 8, y + 8), colour);
	FillTriangle(vi2d(x + 9, y + 12), vi2d(x + 9, y + 9), vi2d(x + 12, y + 9), colour);
	FillRect(x + 8, y + 7, 5, 3, colour);
	FillRect(x + 3, y + 5, 10, 2, colour);
	FillRect(x + 5, y + 3, 8, 1, colour);
	FillRect(x + 9, y + 4, 4, 1, colour);
	FillRect(x + 3, y + 4, 5, 1, colour);
	FillRect(x + 7, y + 2, 5, 1, colour);
	Draw(x + 10, y + 1, colour);
	Draw(x + 10, y + 12, colour);
	Draw(x + 11, y + 12, colour);

}
void GameEngine::drawBishop(int x, int y, Pixel colour)
{
	FillRect(x + 3, y + 13, 10, 1, colour);
	FillRect(x + 4, y + 12, 8, 1, colour);
	FillRect(x + 5, y + 11, 6, 1, colour);
	FillRect(x + 5, y + 4, 2, 5, colour);
	FillRect(x + 9, y + 4, 2, 5, colour);
	FillRect(x + 7, y + 7, 2, 4, colour);
	FillRect(x + 7, y + 2, 2, 4, colour);
	Draw(x + 6, y + 3, colour);
	Draw(x + 9, y + 3, colour);
	Draw(x + 6, y + 9, colour);
	Draw(x + 9, y + 9, colour);

}
void GameEngine::drawQueen(int x, int y, Pixel colour)
{
	FillRect(x + 4, y + 2, 3, 1, colour);
	FillRect(x + 9, y + 2, 3, 1, colour);
	FillRect(x + 5, y + 3, 1, 2, colour);
	FillRect(x + 10, y + 3, 1, 2, colour);
	FillRect(x + 6, y + 4, 1, 4, colour);
	FillRect(x + 9, y + 4, 1, 4, colour);
	FillRect(x + 6, y + 8, 4, 4, colour);
	FillRect(x + 3, y + 5, 1, 4, colour);
	FillRect(x + 4, y + 8, 1, 2, colour);
	FillRect(x + 5, y + 9, 1, 2, colour);
	FillRect(x + 12, y + 5, 1, 4, colour);
	FillRect(x + 11, y + 8, 1, 2, colour);
	FillRect(x + 10, y + 9, 1, 2, colour);
	FillRect(x + 4, y + 12, 8, 1, colour);
	FillRect(x + 3, y + 13, 10, 1, colour);
}
void GameEngine::drawKing(int x, int y, Pixel colour)
{
	FillRect(x + 5, y + 6, 6, 7, colour);
	FillRect(x + 3, y + 7, 1, 4, colour);
	FillRect(x + 4, y + 6, 1, 6, colour);
	FillRect(x + 7, y + 2, 2, 4, colour);
	FillRect(x + 11, y + 6, 1, 6, colour);
	FillRect(x + 12, y + 7, 1, 4, colour);
	FillRect(x + 3, y + 13, 10, 1, colour);
	Draw(x + 6, y + 3, colour);
	Draw(x + 9, y + 3, colour);
}