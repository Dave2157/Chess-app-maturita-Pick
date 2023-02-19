#pragma once

#include <string>
#include <vector>
#include <utility>

class Controller;

using std::vector;
using std::pair;
using std::string;

struct Move
{
	int startX, startY;
	int targetX, targetY;
	bool pawnTwoTileMove;
	bool enPassent;
	char castle;
	char promotion;
};

struct ControllerTurnInformationPackage
{
	pair<int, int> selectedPiece;
	Move playedMove;
};

struct Board
{
	//char** layout;
	std::vector<vector<char>> layout;
	bool whiteToMove;
	bool* castlingRights;
	pair<int, int> enPassentSquare;
	int fiftyMoveRuleCounter;
	int fullMoves;
	char checkmate;


	Controller* whitePlayer;
	Controller* blackPlayer;

	ControllerTurnInformationPackage currentTurnInformationPackage;

public:
	Board();
	Board(const Board& cboard);
	~Board();

	void setBoardFEN(string FEN);

};



