#pragma once
#include "BoardAndUtils.h"

bool boundsOk(int x, int y);
bool isSquareUnderAttack(const Board& board, int x, int y, bool whiteAttacks);
std::vector<Move> findLegalMovesForAPiece(const Board& board, char piece, int pieceX, int pieceY);
std::vector<pair<int, int>> findAllPieces(const Board& board, bool white);
void makeMove(Board& board, Move& move);
std::vector<pair<int, int>> findPiecesOfAGivenType(const Board& board, char piece);
bool checkForCheckmate(const Board& board, bool white);
bool checkForStalemate(const Board& board, bool whiteToMove);
string boardIntoString(const Board& board);