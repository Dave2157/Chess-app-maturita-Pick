#pragma once
#include <fstream>
#include <string>
#include "BoardAndUtils.h"

void logAMoveWtihEvaluationsOfBothPositionsIntoAFile(const Board& board, Move& move, string fileName);

void asciiDrawBoard(std::wofstream& file, const Board& board1);

void logASinglePositionEvaluationIntoAFile(string FEN, string fileName);