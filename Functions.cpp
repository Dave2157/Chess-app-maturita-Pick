#include "Functions.h"

bool boundsOk(int x, int y)
{
	return x >= 0 && x < 8 && y >= 0 && y < 8;
}

bool isSquareUnderAttack(const Board& board, int x, int y, bool whiteAttacks)
{

	if (whiteAttacks)
	{
		if (boundsOk(x + 1, y + 1) && board.layout[y + 1][x + 1] == 'P')
			return true;
		if (boundsOk(x - 1, y + 1) && board.layout[y + 1][x - 1] == 'P')
			return true;
	}
	else
	{
		if (boundsOk(x + 1, y - 1) && board.layout[y - 1][x + 1] == 'p')
			return true;
		if (boundsOk(x - 1, y - 1) && board.layout[y - 1][x - 1] == 'p')
			return true;
	}

	std::vector<pair<int, int>> rookDirections = { {-1, 0}, {0, -1}, {1, 0}, { 0, 1 } };
	for (pair<int, int> directions : rookDirections)
	{
		for (int i = 1; i < 8; i++)
		{
			int currentX = x + i * directions.first;
			int currentY = y + i * directions.second;


			if (!boundsOk(currentX, currentY))
				break;
			if (board.layout[currentY][currentX] != ' ')
			{
				if (board.layout[currentY][currentX] != (whiteAttacks ? 'R' : 'r') && board.layout[currentY][currentX] != (whiteAttacks ? 'Q' : 'q'))
				{
					break;
				}
				return true;
			}
		}
	}

	std::vector<pair<int, int>> bishopDirections = { {-1, 1}, {1, -1}, {1, 1}, { -1, -1 } };
	for (pair<int, int> directions : bishopDirections)
	{
		for (int i = 1; i < 8; i++)
		{
			int currentX = x + i * directions.first;
			int currentY = y + i * directions.second;

			if (!boundsOk(currentX, currentY))
				break;
			if (board.layout[currentY][currentX] != ' ')
			{
				if (board.layout[currentY][currentX] != (whiteAttacks ? 'B' : 'b') && board.layout[currentY][currentX] != (whiteAttacks ? 'Q' : 'q'))
				{
					break;
				}
				return true;
			}
		}
	}

	std::vector<pair<int, int>> knightSquareOffsets = { {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2} };
	for (pair<int, int> offsets : knightSquareOffsets)
	{
		if (boundsOk(x + offsets.first, y + offsets.second) && board.layout[y + offsets.second][x + offsets.first] == (whiteAttacks ? 'N' : 'n'))
			return true;
	}

	std::vector<pair<int, int>> kingSquareOffsets = { {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1} };
	for (pair<int, int> offsets : kingSquareOffsets)
	{
		if (boundsOk(x + offsets.first, y + offsets.second) && board.layout[y + offsets.second][x + offsets.first] == (whiteAttacks ? 'K' : 'k'))
			return true;
	}

	return false;
}

std::vector<Move> findLegalMovesForAPiece(const Board& board, char piece, int pieceX, int pieceY)
{
	std::vector<Move> moveListToBeReturned;
	switch (piece)
	{
	case 'p':
		if (boundsOk(pieceX, pieceY + 1) && board.layout[pieceY + 1][pieceX] == ' ')
		{
			if (pieceY + 1 == 7)
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY + 1, false, false, 0, 's' });
			else
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY + 1, false, false, 0 });
		}
		if (pieceY == 1 && board.layout[pieceY + 1][pieceX] == ' ' && board.layout[pieceY + 2][pieceX] == ' ')
		{
			moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY + 2, true, false, 0 });
		}
		if (boundsOk(pieceX + 1, pieceY + 1))
		{
			if (isupper(board.layout[pieceY + 1][pieceX + 1]))
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + 1, pieceY + 1, false, false, 0, (pieceY + 1 == 7 ? 's' : '\0') });
			else if (board.enPassentSquare.first == pieceX + 1 && board.enPassentSquare.second == pieceY + 1)
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + 1, pieceY + 1, false, true, 0 });
		}
		if (boundsOk(pieceX - 1, pieceY + 1))
		{
			if (isupper(board.layout[pieceY + 1][pieceX - 1]))
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - 1, pieceY + 1, false, false, 0, (pieceY + 1 == 7 ? 's' : '\0') });
			else if (board.enPassentSquare.first == pieceX - 1 && board.enPassentSquare.second == pieceY + 1)
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - 1, pieceY + 1, false, true, 0 });
		}
		break;
	case 'P':
		if (boundsOk(pieceX, pieceY - 1) && board.layout[pieceY - 1][pieceX] == ' ')
		{
			if (pieceY - 1 == 0)
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY - 1, false, false, 0, 'w' });
			else
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY - 1, false, false, 0 });
		}
		if (pieceY == 6 && board.layout[pieceY - 1][pieceX] == ' ' && board.layout[pieceY - 2][pieceX] == ' ')
		{
			moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY - 2, true, false, 0 });
		}
		if (boundsOk(pieceX + 1, pieceY - 1))
		{
			if (islower(board.layout[pieceY - 1][pieceX + 1]))
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + 1, pieceY - 1, false, false, 0, (pieceY - 1 == 0 ? 'w' : '\0') });
			else if (board.enPassentSquare.first == pieceX + 1 && board.enPassentSquare.second == pieceY - 1)
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + 1, pieceY - 1, false, true, 0 });
		}
		if (boundsOk(pieceX - 1, pieceY - 1))
		{
			if (islower(board.layout[pieceY - 1][pieceX - 1]))
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - 1, pieceY - 1, false, false, 0, (pieceY - 1 == 0 ? 'w' : '\0') });
			else if (board.enPassentSquare.first == pieceX - 1 && board.enPassentSquare.second == pieceY - 1)
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - 1, pieceY - 1, false, true, 0 });
		}

		break;
	case 'r':																			// zrušení castlingu při pohnutí věží
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX, pieceY + i))
			{
				if (isupper(board.layout[pieceY + i][pieceX]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY + i, false, false, 0 });
					goto A;
				}
				else if (islower(board.layout[pieceY + i][pieceX]))
					goto A;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY + i, false, false, 0 });
			}
			else
				goto A;
		}
	A:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX, pieceY - i))
			{
				if (isupper(board.layout[pieceY - i][pieceX]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY - i, false, false, 0 });
					goto B;
				}
				else if (islower(board.layout[pieceY - i][pieceX]))
					goto B;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY - i, false, false, 0 });
			}
			else
				goto B;
		}
	B:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX + i, pieceY))
			{
				if (isupper(board.layout[pieceY][pieceX + i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY, false, false, 0 });
					goto C;
				}
				else if (islower(board.layout[pieceY][pieceX + i]))
					goto C;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY, false, false, 0 });
			}
			else
				goto C;
		}
	C:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX - i, pieceY))
			{
				if (isupper(board.layout[pieceY][pieceX + -i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY, false, false, 0 });
					goto D;
				}
				else if (islower(board.layout[pieceY][pieceX - i]))
					goto D;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY, false, false, 0 });
			}
			else
				goto D;
		}
	D:
		break;
	case 'R':
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX, pieceY + i))
			{
				if (islower(board.layout[pieceY + i][pieceX]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY + i, false, false, 0 });
					goto E;
				}
				else if (isupper(board.layout[pieceY + i][pieceX]))
					goto E;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY + i, false, false, 0 });
			}
			else
				goto E;
		}
	E:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX, pieceY - i))
			{
				if (islower(board.layout[pieceY - i][pieceX]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY - i, false, false, 0 });
					goto F;
				}
				else if (isupper(board.layout[pieceY - i][pieceX]))
					goto F;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY - i, false, false, 0 });
			}
			else
				goto F;
		}
	F:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX + i, pieceY))
			{
				if (islower(board.layout[pieceY][pieceX + i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY, false, false, 0 });
					goto G;
				}
				else if (isupper(board.layout[pieceY][pieceX + i]))
					goto G;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY, false, false, 0 });
			}
			else
				goto G;
		}
	G:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX - i, pieceY))
			{
				if (islower(board.layout[pieceY][pieceX - i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY, false, false, 0 });
					goto H;
				}
				else if (isupper(board.layout[pieceY][pieceX - i]))
					goto H;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY, false, false, 0 });
			}
			else
				goto H;
		}
	H:
		break;
	case 'n':
	{
		std::vector<pair<int, int>> targetSquares = { {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1} };
		for (pair<int, int> offsets : targetSquares)
		{
			if (boundsOk(pieceX + offsets.first, pieceY + offsets.second) && !islower(board.layout[pieceY + offsets.second][pieceX + offsets.first]))
			{
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + offsets.first, pieceY + offsets.second, false, false, 0 });
			}
		}
		break;
	}
	case 'N':
	{
		std::vector<pair<int, int>> targetSquares = { {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1} };
		for (pair<int, int> offsets : targetSquares)
		{
			if (boundsOk(pieceX + offsets.first, pieceY + offsets.second) && !isupper(board.layout[pieceY + offsets.second][pieceX + offsets.first]))
			{
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + offsets.first, pieceY + offsets.second, false, false, 0 });
			}
		}
		break;
	}
	case 'b':
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX + i, pieceY + i))
			{
				if (isupper(board.layout[pieceY + i][pieceX + i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY + i, false, false, 0 });
					goto I;
				}
				else if (islower(board.layout[pieceY + i][pieceX + i]))
					goto I;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY + i, false, false, 0 });
			}
			else
				goto I;
		}
	I:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX + i, pieceY - i))
			{
				if (isupper(board.layout[pieceY - i][pieceX + i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY - i, false, false, 0 });
					goto J;
				}
				else if (islower(board.layout[pieceY - i][pieceX + i]))
					goto J;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY - i, false, false, 0 });
			}
			else
				goto J;
		}
	J:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX - i, pieceY + i))
			{
				if (isupper(board.layout[pieceY + i][pieceX - i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY + i, false, false, 0 });
					goto K;
				}
				else if (islower(board.layout[pieceY + i][pieceX - i]))
					goto K;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY + i, false, false, 0 });
			}
			else
				goto K;
		}
	K:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX - i, pieceY - i))
			{
				if (isupper(board.layout[pieceY - i][pieceX - i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY - i, false, false, 0 });
					goto L;
				}
				else if (islower(board.layout[pieceY - i][pieceX - i]))
					goto L;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY - i, false, false, 0 });
			}
			else
				goto L;
		}
	L:
		break;
	case 'B':
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX + i, pieceY + i))
			{
				if (islower(board.layout[pieceY + i][pieceX + i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY + i, false, false, 0 });
					goto M;
				}
				else if (isupper(board.layout[pieceY + i][pieceX + i]))
					goto M;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY + i, false, false, 0 });
			}
			else
				goto M;
		}
	M:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX + i, pieceY - i))
			{
				if (islower(board.layout[pieceY - i][pieceX + i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY - i, false, false, 0 });
					goto N;
				}
				else if (isupper(board.layout[pieceY - i][pieceX + i]))
					goto N;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY - i, false, false, 0 });
			}
			else
				goto N;
		}
	N:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX - i, pieceY + i))
			{
				if (islower(board.layout[pieceY + i][pieceX - i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY + i, false, false, 0 });
					goto O;
				}
				else if (isupper(board.layout[pieceY + i][pieceX - i]))
					goto O;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY + i, false, false, 0 });
			}
			else
				goto O;
		}
	O:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX - i, pieceY - i))
			{
				if (islower(board.layout[pieceY - i][pieceX - i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY - i, false, false, 0 });
					goto P;
				}
				else if (isupper(board.layout[pieceY - i][pieceX - i]))
					goto P;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY - i, false, false, 0 });
			}
			else
				goto P;
		}
	P:
		break;
	case 'q':
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX, pieceY + i))
			{
				if (isupper(board.layout[pieceY + i][pieceX]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY + i, false, false, 0 });
					goto Q;
				}
				else if (islower(board.layout[pieceY + i][pieceX]))
					goto Q;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY + i, false, false, 0 });
			}
			else
				goto Q;
		}
	Q:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX, pieceY - i))
			{
				if (isupper(board.layout[pieceY - i][pieceX]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY - i, false, false, 0 });
					goto R;
				}
				else if (islower(board.layout[pieceY - i][pieceX]))
					goto R;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY - i, false, false, 0 });
			}
			else
				goto R;
		}
	R:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX + i, pieceY))
			{
				if (isupper(board.layout[pieceY][pieceX + i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY, false, false, 0 });
					goto S;
				}
				else if (islower(board.layout[pieceY][pieceX + i]))
					goto S;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY, false, false, 0 });
			}
			else
				goto S;
		}
	S:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX - i, pieceY))
			{
				if (isupper(board.layout[pieceY][pieceX + -i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY, false, false, 0 });
					goto T;
				}
				else if (islower(board.layout[pieceY][pieceX - i]))
					goto T;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY, false, false, 0 });
			}
			else
				goto T;
		}
	T:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX + i, pieceY + i))
			{
				if (isupper(board.layout[pieceY + i][pieceX + i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY + i, false, false, 0 });
					goto U;
				}
				else if (islower(board.layout[pieceY + i][pieceX + i]))
					goto U;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY + i, false, false, 0 });
			}
			else
				goto U;
		}
	U:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX + i, pieceY - i))
			{
				if (isupper(board.layout[pieceY - i][pieceX + i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY - i, false, false, 0 });
					goto V;
				}
				else if (islower(board.layout[pieceY - i][pieceX + i]))
					goto V;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY - i, false, false, 0 });
			}
			else
				goto V;
		}
	V:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX - i, pieceY + i))
			{
				if (isupper(board.layout[pieceY + i][pieceX - i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY + i, false, false, 0 });
					goto W;
				}
				else if (islower(board.layout[pieceY + i][pieceX - i]))
					goto W;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY + i, false, false, 0 });
			}
			else
				goto W;
		}
	W:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX - i, pieceY - i))
			{
				if (isupper(board.layout[pieceY - i][pieceX - i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY - i, false, false, 0 });
					goto X;
				}
				else if (islower(board.layout[pieceY - i][pieceX - i]))
					goto X;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY - i, false, false, 0 });
			}
			else
				goto X;
		}
	X:
		break;
	case 'Q':
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX, pieceY + i))
			{
				if (islower(board.layout[pieceY + i][pieceX]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY + i, false, false, 0 });
					goto Y;
				}
				else if (isupper(board.layout[pieceY + i][pieceX]))
					goto Y;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY + i, false, false, 0 });
			}
			else
				goto Y;
		}
	Y:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX, pieceY - i))
			{
				if (islower(board.layout[pieceY - i][pieceX]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY - i, false, false, 0 });
					goto Z;
				}
				else if (isupper(board.layout[pieceY - i][pieceX]))
					goto Z;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX, pieceY - i, false, false, 0 });
			}
			else
				goto Z;
		}
	Z:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX + i, pieceY))
			{
				if (islower(board.layout[pieceY][pieceX + i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY, false, false, 0 });
					goto AA;
				}
				else if (isupper(board.layout[pieceY][pieceX + i]))
					goto AA;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY, false, false, 0 });
			}
			else
				goto AA;
		}
	AA:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX - i, pieceY))
			{
				if (islower(board.layout[pieceY][pieceX + -i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY, false, false, 0 });
					goto AB;
				}
				else if (isupper(board.layout[pieceY][pieceX - i]))
					goto AB;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY, false, false, 0 });
			}
			else
				goto AB;
		}
	AB:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX + i, pieceY + i))
			{
				if (islower(board.layout[pieceY + i][pieceX + i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY + i, false, false, 0 });
					goto AC;
				}
				else if (isupper(board.layout[pieceY + i][pieceX + i]))
					goto AC;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY + i, false, false, 0 });
			}
			else
				goto AC;
		}
	AC:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX + i, pieceY - i))
			{
				if (islower(board.layout[pieceY - i][pieceX + i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY - i, false, false, 0 });
					goto AD;
				}
				else if (isupper(board.layout[pieceY - i][pieceX + i]))
					goto AD;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + i, pieceY - i, false, false, 0 });
			}
			else
				goto AD;
		}
	AD:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX - i, pieceY + i))
			{
				if (islower(board.layout[pieceY + i][pieceX - i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY + i, false, false, 0 });
					goto AE;
				}
				else if (isupper(board.layout[pieceY + i][pieceX - i]))
					goto AE;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY + i, false, false, 0 });
			}
			else
				goto AE;
		}
	AE:
		for (int i = 1; i < 8; i++)
		{
			if (boundsOk(pieceX - i, pieceY - i))
			{
				if (islower(board.layout[pieceY - i][pieceX - i]))
				{
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY - i, false, false, 0 });
					goto AF;
				}
				else if (isupper(board.layout[pieceY - i][pieceX - i]))
					goto AF;
				else
					moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - i, pieceY - i, false, false, 0 });
			}
			else
				goto AF;
		}
	AF:
		break;
	case 'k':
	{
		std::vector<pair<int, int>> targetSquares = { {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0} };
		for (pair<int, int> offsets : targetSquares)
		{
			if (boundsOk(pieceX + offsets.first, pieceY + offsets.second) && !islower(board.layout[pieceY + offsets.second][pieceX + offsets.first]))
			{
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + offsets.first, pieceY + offsets.second, false, false, 0 });
			}
		}

		if (board.castlingRights[2] && board.layout[0][7] == 'r' && board.layout[0][6] == ' ' && board.layout[0][5] == ' ' && !isSquareUnderAttack(board, 6, 0, true) && !isSquareUnderAttack(board, 5, 0, true) && !isSquareUnderAttack(board, pieceX, pieceY, true))
		{
			moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + 2, pieceY, false, false, 'k' });
		}
		if (board.castlingRights[3] && board.layout[0][0] == 'r' && board.layout[0][1] == ' ' && board.layout[0][2] == ' ' && board.layout[0][3] == ' ' && !isSquareUnderAttack(board, 2, 0, true) && !isSquareUnderAttack(board, 3, 0, true) && !isSquareUnderAttack(board, pieceX, pieceY, true))
		{
			moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - 2, pieceY, false, false, 'q' });
		}

		break;
	}
	case 'K':
	{
		std::vector<pair<int, int>> targetSquares = { {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0} };
		for (pair<int, int> offsets : targetSquares)
		{
			if (boundsOk(pieceX + offsets.first, pieceY + offsets.second) && !isupper(board.layout[pieceY + offsets.second][pieceX + offsets.first]))
			{
				moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + offsets.first, pieceY + offsets.second, false, false, 0 });
			}
		}

		if (board.castlingRights[0] && board.layout[7][7] == 'R' && board.layout[7][6] == ' ' && board.layout[7][5] == ' ' && !isSquareUnderAttack(board, 6, 7, false) && !isSquareUnderAttack(board, 5, 7, false) && !isSquareUnderAttack(board, pieceX, pieceY, false))
		{
			moveListToBeReturned.push_back({ pieceX, pieceY, pieceX + 2, pieceY, false, false, 'K' });
		}
		if (board.castlingRights[1] && board.layout[7][0] == 'R' && board.layout[7][1] == ' ' && board.layout[7][2] == ' ' && board.layout[7][3] == ' ' && !isSquareUnderAttack(board, 2, 7, false) && !isSquareUnderAttack(board, 3, 7, false) && !isSquareUnderAttack(board, pieceX, pieceY, false))
		{
			moveListToBeReturned.push_back({ pieceX, pieceY, pieceX - 2, pieceY, false, false, 'Q' });
		}

		break;
	}
	}

	auto garbageStart = std::remove_if(moveListToBeReturned.begin(), moveListToBeReturned.end(),
		[board](Move move)
		{
			Board potentialBoard(board);

			makeMove(potentialBoard, move);
			potentialBoard.whiteToMove = !potentialBoard.whiteToMove;

			int kingX = 0;
			int kingY = 0;
			char kingChar = !potentialBoard.whiteToMove ? 'K' : 'k';


			for (kingX = 0; kingX < 8; kingX++)
				for (kingY = 0; kingY < 8; kingY++)
					if (potentialBoard.layout[kingY][kingX] == kingChar)
						goto AI;
		AI:

			return isSquareUnderAttack(potentialBoard, kingX, kingY, potentialBoard.whiteToMove);

		});

	moveListToBeReturned.erase(garbageStart, moveListToBeReturned.end());

	return moveListToBeReturned;
}

std::vector<pair<int, int>> findAllPieces(const Board& board, bool white)
{
	auto capsFunction = white ? isupper : islower;
	std::vector<pair<int, int>> toBeReturned;
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
			if (capsFunction(board.layout[y][x]))
				toBeReturned.push_back(std::make_pair(x, y));
	return toBeReturned;
}

void makeMove(Board& board, Move& move)
{
	if (!(board.layout[move.targetY][move.targetX] != ' ' || board.layout[move.startY][move.startX] == 'P' || board.layout[move.startY][move.startX] == 'p'))
		board.fiftyMoveRuleCounter++;
	else
		board.fiftyMoveRuleCounter = 0;

	if (move.pawnTwoTileMove)
	{
		int enPassentRank = board.whiteToMove ? 5 : 2;
		board.enPassentSquare = std::make_pair(move.targetX, enPassentRank);
	}
	else
		board.enPassentSquare = std::make_pair(-1, -1);

	if (move.enPassent)
	{
		board.layout[move.targetY + (board.whiteToMove ? 1 : -1)][move.targetX] = ' ';
	}

	if (move.castle)
	{
		switch (move.castle)
		{
		case 'K':
			board.layout[7][5] = 'R';
			board.layout[7][7] = ' ';
			board.castlingRights[0] = board.castlingRights[1] = false;
			break;
		case 'Q':
			board.layout[7][3] = 'R';
			board.layout[7][0] = ' ';
			board.castlingRights[0] = board.castlingRights[1] = false;
			break;
		case 'k':
			board.layout[0][5] = 'r';
			board.layout[0][7] = ' ';
			board.castlingRights[2] = board.castlingRights[3] = false;
			break;
		case 'q':
			board.layout[0][3] = 'r';
			board.layout[0][0] = ' ';
			board.castlingRights[2] = board.castlingRights[3] = false;
			break;
		}
	}
	else
	{
		if (board.layout[move.startY][move.startX] == 'K')
		{
			board.castlingRights[0] = board.castlingRights[1] = false;
		}
		else if (board.layout[move.startY][move.startX] == 'k')
		{
			board.castlingRights[2] = board.castlingRights[3] = false;
		}
		else if (board.layout[move.startY][move.startX] == 'R')
		{
			if (move.startX == 0 && move.startY == 7)
				board.castlingRights[1] = false;
			else if (move.startX == 7 && move.startY == 7)
				board.castlingRights[0] = false;
		}
		else if (board.layout[move.startY][move.startX] == 'r')
		{
			if (move.startX == 0 && move.startY == 0)
				board.castlingRights[3] = false;
			else if (move.startX == 7 && move.startY == 0)
				board.castlingRights[2] = false;
		}

	}

	

	board.layout[move.targetY][move.targetX] = board.layout[move.startY][move.startX];
	board.layout[move.startY][move.startX] = ' ';

	if (move.promotion && move.promotion != 'w' && move.promotion != 's')
	{
		board.layout[move.targetY][move.targetX] = move.promotion;
		move.promotion = 0;
	}

	board.history.push_back(boardIntoString(board));

}

std::vector<pair<int, int>> findPiecesOfAGivenType(const Board& board, char piece)
{
	std::vector<pair<int, int>> toBeReturned;
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
			if (board.layout[y][x] == piece)
				toBeReturned.push_back(std::make_pair(x, y));
	return toBeReturned;
}

bool checkForCheckmate(const Board& board, bool white)
{
	int kingX = 0;
	int kingY = 0;
	char kingChar = white ? 'K' : 'k';


	for (kingX = 0; kingX < 8; kingX++)
		for (kingY = 0; kingY < 8; kingY++)
			if (board.layout[kingY][kingX] == kingChar)
				goto checkForCheckmateLabel;
checkForCheckmateLabel:


	if (isSquareUnderAttack(board, kingX, kingY, !white))
	{
		auto allPieces = findAllPieces(board, white);
		std::vector<Move> allLegalMoves;

		for (pair<int, int> piece : allPieces)
		{
			char pieceType = board.layout[piece.second][piece.first];

			Board tempBoard(board);
			tempBoard.whiteToMove = white;

			auto legalMovesForThisPiece = findLegalMovesForAPiece(tempBoard, pieceType, piece.first, piece.second);

			allLegalMoves.insert(allLegalMoves.end(), legalMovesForThisPiece.begin(), legalMovesForThisPiece.end());
		}
		if (!allLegalMoves.size())
			return true;
	}
	return false;
}

bool checkForStalemate(const Board& board, bool whiteToMove)
{
	bool stalemate = false;

	bool majorPieceOrAPawnIsPresent = false;
	int blackMinorPiecesCount = 0;
	int whiteMinorPiecesCount = 0;

	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
		{
			char pieceType = board.layout[y][x];
			if (pieceType == 'Q' || pieceType == 'q' || pieceType == 'R' || pieceType == 'r' || pieceType == 'P' || pieceType == 'p')
				majorPieceOrAPawnIsPresent = true;
			if (pieceType == 'B' || pieceType == 'N')
				whiteMinorPiecesCount++;
			if (pieceType == 'b' || pieceType == 'n')
				blackMinorPiecesCount++;
		}


	auto allPieces = findAllPieces(board, whiteToMove);
	std::vector<Move> allLegalMoves;

	for (pair<int, int> piece : allPieces)
	{
		char pieceType = board.layout[piece.second][piece.first];

		Board tempBoard(board);
		tempBoard.whiteToMove = whiteToMove;

		auto legalMovesForThisPiece = findLegalMovesForAPiece(tempBoard, pieceType, piece.first, piece.second);

		allLegalMoves.insert(allLegalMoves.end(), legalMovesForThisPiece.begin(), legalMovesForThisPiece.end());
	}

	stalemate = !allLegalMoves.size();
	
	int howManyTimesDidThisPositionRepeat = 0;
	if (board.history.size() >= 6)
	{
		string lastPosition = board.history.back();
		howManyTimesDidThisPositionRepeat = std::count(board.history.begin(), board.history.end(), lastPosition);
	}

	if (howManyTimesDidThisPositionRepeat >= 3)
		return true;
	if (blackMinorPiecesCount <= 2 && whiteMinorPiecesCount <= 2 && !majorPieceOrAPawnIsPresent)
		return true;
	if (board.fiftyMoveRuleCounter == 100)
		return true;
	if (stalemate)
		return true;

	return false;
}

string boardIntoString(const Board& board)
{
	string ret(64, '\0');
	for (int y = 0; y < 8; y++)
		for (int x = 0; x < 8; x++)
			ret[y * 8 + x] = board.layout[y][x];
	return ret;
}

string boardIntoFEN(const Board& board)
{
	//rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

	std::stringstream FEN;

	int blankSpacesInARow = 0;

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (board.layout[y][x] != ' ')
			{
				if (blankSpacesInARow)
				{
					FEN << blankSpacesInARow;
					blankSpacesInARow = 0;
				}
				FEN << board.layout[y][x];
			}
			else
				blankSpacesInARow++;
				
		}
		if (blankSpacesInARow)
		{
			FEN << blankSpacesInARow;
			blankSpacesInARow = 0;
		}
		if (y == 7)
			break;
		FEN << '/';
	}
	FEN << ' ';

	FEN << (board.whiteToMove ? 'w' : 'b');

	FEN << ' ';

	if (!(board.castlingRights[0] || board.castlingRights[1] || board.castlingRights[2] || board.castlingRights[3]))
		FEN << '-';
	if (board.castlingRights[0])
		FEN << 'K';
	if (board.castlingRights[1])
		FEN << 'Q';
	if (board.castlingRights[2])
		FEN << 'k';
	if (board.castlingRights[3])
		FEN << 'q';

	FEN << ' ';

	if (board.enPassentSquare.first != -1)
	{
		FEN << char(board.enPassentSquare.first + 97);
		FEN << 8 - board.enPassentSquare.second;
	}
	else
		FEN << '-';

	FEN << ' ';

	FEN << board.fiftyMoveRuleCounter << ' ' << board.fullMoves;

	return FEN.str();
}

void saveGameIntoFile(const Board& board, string fileName)
{
	std::ofstream file(fileName);
	file << boardIntoFEN(board) << std::endl;

	if (dynamic_cast<Player*>(board.whitePlayer))
		file << 'p';
	else
		file << 'c';
	if (dynamic_cast<Player*>(board.blackPlayer))
		file << 'p';
	else
		file << 'c';

	file << std::endl;

	for (const string& position : board.history)
	{
		file << position << '/';
	}
}

bool randomBool()
{
	std::time_t integer = time(nullptr);
	return integer & 1;
}