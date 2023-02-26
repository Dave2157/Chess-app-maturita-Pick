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


void GameEngine::drawLetter(char letter, int size, int x, int y, Pixel colour)
{
	switch (letter)
	{
	case 'C':
	{
		FillRect(x, y, size / 2, size / 8, colour);
		FillRect(x, y + size / 8, size / 8, 3 * size / 4, colour);
		FillRect(x, y + 7 * size / 8, size / 2, size / 8, colour);
		break;
	}

	case 'H':
	{
		FillRect(x, y, size / 8, size, colour);
		FillRect(x + 3 * size / 8, y, size / 8, size, colour);
		FillRect(x + size / 8, y + size / 2, size / 4, size / 8, colour);
		break;
	}
	case 'E':
	{
		FillRect(x, y, size / 8, size, colour);
		FillRect(x, y, size / 2, size / 8, colour);
		FillRect(x, y + size / 2, 3 * size / 8, size / 8, colour);
		FillRect(x, y + 7 * size / 8, size / 2, size / 8, colour);

		break;
	}
	case 'S':
	{
		FillRect(x, y, size / 2, size / 8, colour);
		FillRect(x, y + size / 2, size / 2, size / 8, colour);
		FillRect(x, y + 7 * size / 8, size / 2, size / 8, colour);
		FillRect(x, y + size / 8, size / 8, 3 * size / 8, colour);
		FillRect(x + 3 * size / 8, y + 5 * size / 8, size / 8, 3 * size / 8, colour);

		break;
	}
	case 'P':
	{
		FillRect(x, y, size / 8, size, colour);
		FillRect(x + size / 8, y, 3 * size / 8, size / 8, colour);
		FillRect(x + size / 8, y + 3 * size / 8, 3 * size / 8, size / 8, colour);
		FillRect(x + 3 * size / 8, y + size / 8, size / 8, size / 4, colour);

		break;
	}
	case 'L':
	{
		FillRect(x, y, size / 8, size, colour);
		FillRect(x + size / 8, y + 7 * size / 8, 3 * size / 8, size / 8, colour);
		break;
	}
	case 'A':
	{
		FillRect(x, y, size / 8, size, colour);
		FillRect(x + 3 * size / 8, y, size / 8, size, colour);
		FillRect(x + size / 8, y, size / 4, size / 8, colour);
		FillRect(x + size / 8, y + 3 * size / 8, size / 4, size / 8, colour);
		break;
	}
	case 'Y':
	{
		DrawLine(x + size / 2 - 1, y, x, y + size - 1, colour);
		DrawLine(x, y, x + size / 4, y + size / 2, colour);
		break;
	}
	case 'Q':
	{
		drawLetter('O', size, x, y, colour);
		DrawLine(x + size / 4, y + size / 2, x + size / 2 - 1, y + size - 1, colour);
		break;
	}
	case 'U':
	{
		drawLetter('L', size, x, y, colour);
		FillRect(x + 3 * size / 8, y, size / 8, 7 * size / 8, colour);
		break;
	}
	case 'I':
	{
		FillRect(x + size / 4, y, size / 8, size, colour);
		break;
	}
	case 'T':
	{
		FillRect(x, y, size / 2, size / 8, colour);
		FillRect(x + size / 4, y + size / 8, size / 8, 7 * size / 8, colour);
		break;
	}
	case 'O':
	{
		drawLetter('U', size, x, y, colour);
		FillRect(x + size / 8, y, size / 4, size / 8, colour);
		break;
	}
	case 'N':
	{
		FillRect(x, y, size / 8, size, colour);
		FillRect(x + 3 * size / 8, y, size / 8, 7 * size / 8, colour);
		DrawLine(x, y, x + size / 2 - 1, y + size - 1, colour);
		break;
	}
	case 'R':
	{
		drawLetter('P', size, x, y, colour);
		DrawLine(x + size / 4, y + size / 2, x + size / 2 - 1, y + size - 1, colour);
		break;
	}
	case 'M':
	{
		FillRect(x, y, size / 8, size, colour);
		FillRect(x + 3 * size / 8, y, size / 8, size, colour);
		DrawLine(x + 1, y + 1, x + size / 4 - 1, y + size / 2 - 1, colour);
		DrawLine(x + size / 4 - 1, y + size / 2 - 1, x + size / 2 - 1, y, colour);
		break;
	}
	case 'W':
	{
		FillRect(x, y, size / 8, size, colour);
		FillRect(x + 3 * size / 8, y, size / 8, size, colour);
		DrawLine(x + 1, y + size - 2, x + size / 4 - 1, y + size / 2 - 1, colour);
		DrawLine(x + size / 4 - 1, y + size / 2 - 1, x + size / 2 - 1, y + size - 2, colour);
		break;
	}
	case 'B':
	{
		FillRect(x, y, size / 8, size, colour);
		FillRect(x + size / 8, y, size / 4, size / 8, colour);
		FillRect(x + size / 8, y + 3 * size / 8, size / 4, size / 8, colour);
		FillRect(x + size / 4, y + size / 8, size / 8, size / 4, colour);
		FillRect(x + size / 8, y + 7 * size / 8, 3 * size / 8, size / 8, colour);
		FillRect(x + 3 * size / 8, y + 3 * size / 8, size / 8, size / 2, colour);
		break;
	}
	case 'K':
	{
		FillRect(x, y, size / 8, size, colour);
		DrawLine(x, y + size / 2, x + size / 2 - 1, y, colour);
		DrawLine(x, y + size / 2, x + size / 2 - 1, y + size - 1, colour);

	}
	}
}
void GameEngine::drawString(string word, int size, int x, int y, Pixel colour)
{
	for (int i = 0; i < word.size(); i++)
	{
		drawLetter(word[i], size, x + i * 5 * size / 8, y, colour);
	}
}

bool GameEngine::makeButton(int x, int y, string text, int width, int height, int textSize, Pixel textColour, Pixel textHoverColour, Pixel bgColour, Pixel hoverColour, int menuStateChange)
{
	

	bool hover = (GetMouseX() >= x && GetMouseX() < x + width && GetMouseY() >= y && GetMouseY() < y + height);
	FillRect(x, y, width, height, hover ? hoverColour : bgColour);


	int textWidthInPixels = text.size() * textSize / 2 + (textSize - 1) * textSize / 8;
	int startingX = (width - textWidthInPixels) / 2 + x;
	int startingY = (height - textSize) / 2 + y;

	drawString(text, textSize, startingX, startingY, hover ? textHoverColour : textColour);


	if (GetMouse(0).bPressed && hover)
	{
		menuState = menuStateChange;
		return true;
	}
	return false;
		
}
