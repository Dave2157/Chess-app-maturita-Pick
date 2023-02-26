#include "BoardAndUtils.h"
#include <sstream>
using namespace std;

Board::Board()
{
	layout.resize(8);
	for (int i = 0; i < 8; i++)
		layout[i].resize(8);
	/*layout = new char* [8];
	for (int i = 0; i < 8; i++)
	{
		layout[i] = new char[8];
	}*/
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			layout[i][j] = ' ';

	whiteToMove = true;
	castlingRights = new bool[4];
	for (int i = 0; i < 4; i++)
		castlingRights[i] = true;
	enPassentSquare = { -1, -1 };
	fiftyMoveRuleCounter = 0;
	fullMoves = 0;
	checkmate = 0;

	whitePlayer = 0;
	blackPlayer = 0;
}
Board::Board(const Board& cboard)
{
	layout = cboard.layout;
	/*layout = new char* [8];
	for (int i = 0; i < 8; i++)
	{
		layout[i] = new char[8];
	}*/
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			layout[i][j] = cboard.layout[i][j];

	whiteToMove = cboard.whiteToMove;
	castlingRights = new bool[4];
	for (int i = 0; i < 4; i++)
		castlingRights[i] = cboard.castlingRights[i];

	enPassentSquare = cboard.enPassentSquare;
	fiftyMoveRuleCounter = cboard.fiftyMoveRuleCounter;
	fullMoves = cboard.fiftyMoveRuleCounter;
	checkmate = cboard.checkmate;

	whitePlayer = cboard.whitePlayer;
	blackPlayer = cboard.blackPlayer;
}
Board::~Board()
{
	/*for (int i = 0; i < 8; i++)
	{
		delete[] layout[i];
	}
	delete[] layout;*/
	delete[] castlingRights;
}
void Board::setBoardFEN(string FEN)				//		rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
{											//		boardLayout toMove castlingRights enPassentSquare halfMove fullMove
	stringstream ssFEN(FEN);

	string boardLayout;
	getline(ssFEN, boardLayout, ' ');

	for (int i = 0; i < boardLayout.length(); i++)
	{
		if (std::isdigit(boardLayout[i]))
		{
			int numberOfSpaces = boardLayout[i] - 48;
			for (int j = 0; j < numberOfSpaces; j++)
				boardLayout.insert(i + 1, " ");
			boardLayout.erase(i, 1);
		}
	}

	stringstream ssBoardLayout(boardLayout);
	string ranks[8];

	for (int i = 0; i < 8; i++)
	{
		string& thisRank = ranks[i];

		getline(ssBoardLayout, thisRank, '/');
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			layout[i][j] = ranks[i][j];
		}
	}

	string toMove;
	getline(ssFEN, toMove, ' ');

	whiteToMove = toMove[0] == 'w';


	string castlingRightsString;
	getline(ssFEN, castlingRightsString, ' ');
	if (castlingRightsString.find("K"))
		castlingRights[0] = true;
	if (castlingRightsString.find("Q"))
		castlingRights[1] = true;
	if (castlingRightsString.find("k"))
		castlingRights[2] = true;
	if (castlingRightsString.find("q"))
		castlingRights[3] = true;

	string enPassentSquareString;
	getline(ssFEN, enPassentSquareString, ' ');
	enPassentSquare.first = enPassentSquareString[0] - 97;
	enPassentSquare.second = enPassentSquareString[1] - 49;


	string moveCounter;
	getline(ssFEN, moveCounter, ' ');
	fiftyMoveRuleCounter = std::stoi(moveCounter);

	getline(ssFEN, moveCounter, ' ');
	fullMoves = std::stoi(moveCounter);


}
