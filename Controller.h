#pragma once
#include "BoardAndUtils.h"
#include "GameEngine.h"

const int MINIMAX_DEPTH = 4;
const int MINIMAX_BRANCHES = 5;

class Controller
{
public:
	virtual void MakeAMove(const Board&, ControllerTurnInformationPackage&, GameEngine*) = 0;
};

class Player : public Controller
{
	virtual void MakeAMove(const Board& board, ControllerTurnInformationPackage& receivedPackage, GameEngine* ge);
};

class Computer : public Controller
{
	int minimaxDepth;
	int numberOfBranches;

public:
	Computer(int md, int nob);
	virtual void MakeAMove(const Board& board, ControllerTurnInformationPackage& receivedPackage, GameEngine* ge);
};