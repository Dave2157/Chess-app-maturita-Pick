#pragma once
#include "BoardAndUtils.h"
struct MinimaxPackage
{
	Move move;
	int score;
};

MinimaxPackage Minimax(const Board& board, int depthInHalfTurns, int numberOfBranches, bool whitesTurn, int alpha, int beta);

int evaluatePosition(const Board& board);

int evaluatePawn(const Board& board, int x, int y, bool isWhite);
int evaluateRook(const Board& board, int x, int y, bool isWhite);
int evaluateKnight(const Board& board, int x, int y, bool isWhite);
int evaluateBishop(const Board& board, int x, int y, bool isWhite);
int evaluateQueen(const Board& board, int x, int y, bool isWhite);
int evaluateKing(const Board& board, int x, int y, bool isWhite);
int evaluatePawnStucture(const Board& board, bool white);
int evaluateWeaknessesOnColoredSquares(const Board& board, bool lightSquares);