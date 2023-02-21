#pragma once
#include "BoardAndUtils.h"
#include "GameEngine.h"

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