#include "GameEngine.h"
#include "Controller.h"
#include "BoardAndUtils.h"
#include "Functions.h"
#include "Minimax.h"


void Player::MakeAMove(const Board& board, ControllerTurnInformationPackage& receivedPackage, GameEngine* ge)
{
	if (ge->GetMouse(0).bPressed)
	{
		int rank, file;
		file = ge->GetMouseX() / 16;
		rank = ge->GetMouseY() / 16;

		bool pieceHadBeenSelected = receivedPackage.selectedPiece.first != -1;

		if (receivedPackage.playedMove.promotion == 'w' || receivedPackage.playedMove.promotion == 's')
		{
			if (receivedPackage.playedMove.promotion == 'w')
			{
				if (rank != 0)
					return;

				float beginningOfMenuArea = receivedPackage.playedMove.targetX * 16 - 24;
				if (beginningOfMenuArea < 0)
					beginningOfMenuArea = 0;
				if (beginningOfMenuArea > 64)
					beginningOfMenuArea = 64;

				float whatPartOfMenuAreaHasBeenClickedOn = (ge->GetMouseX() - beginningOfMenuArea) / 64;

				if (whatPartOfMenuAreaHasBeenClickedOn < 0)
					return;
				if (whatPartOfMenuAreaHasBeenClickedOn < 0.25f)
					receivedPackage.playedMove.promotion = 'N';
				else if (whatPartOfMenuAreaHasBeenClickedOn < 0.5f)
					receivedPackage.playedMove.promotion = 'B';
				else if (whatPartOfMenuAreaHasBeenClickedOn < 0.75f)
					receivedPackage.playedMove.promotion = 'R';
				else if (whatPartOfMenuAreaHasBeenClickedOn > 1)
					return;
				else
					receivedPackage.playedMove.promotion = 'Q';
			}
			else if (rank == 7)
			{
				float beginningOfMenuArea = receivedPackage.playedMove.targetX * 16 - 24;
				if (beginningOfMenuArea < 0)
					beginningOfMenuArea = 0;
				if (beginningOfMenuArea > 64)
					beginningOfMenuArea = 64;

				float whatPartOfMenuAreaHasBeenClickedOn = (ge->GetMouseX() - beginningOfMenuArea) / 64;
				if (whatPartOfMenuAreaHasBeenClickedOn < 0)
					return;
				if (whatPartOfMenuAreaHasBeenClickedOn < 0.25f)
					receivedPackage.playedMove.promotion = 'n';
				else if (whatPartOfMenuAreaHasBeenClickedOn < 0.5f)
					receivedPackage.playedMove.promotion = 'b';
				else if (whatPartOfMenuAreaHasBeenClickedOn < 0.75f)
					receivedPackage.playedMove.promotion = 'r';
				else if (whatPartOfMenuAreaHasBeenClickedOn > 1)
					return;
				else
					receivedPackage.playedMove.promotion = 'q';
			}
		}
		else if (pieceHadBeenSelected)
		{
			int selectedPieceX = receivedPackage.selectedPiece.first;
			int selectedPieceY = receivedPackage.selectedPiece.second;


			std::vector<Move> availableMovesForSelectedPiece = findLegalMovesForAPiece(board, board.layout[selectedPieceY][selectedPieceX], selectedPieceX, selectedPieceY);

			bool possibleMoveFound = false;
			for (Move& move : availableMovesForSelectedPiece)
			{
				if (move.targetX == file && move.targetY == rank)
				{
					possibleMoveFound = true;
					receivedPackage.playedMove = { receivedPackage.selectedPiece.first, receivedPackage.selectedPiece.second, move.targetX, move.targetY, move.pawnTwoTileMove, move.enPassent, move.castle, move.promotion };
					receivedPackage.selectedPiece.first = receivedPackage.selectedPiece.second = -1;
					break;
				}
			}
			if (!possibleMoveFound)
			{
				receivedPackage.selectedPiece.first = receivedPackage.selectedPiece.second = -1;
			}
		}
		else
		{
			char piece = board.layout[rank][file];
			if ((board.whiteToMove ? isupper : islower)(piece))
			{
				receivedPackage.selectedPiece.first = file;
				receivedPackage.selectedPiece.second = rank;
				pieceHadBeenSelected = true;
			}
		}
	}

	return;
}

Computer::Computer(int md, int nob) : Controller()
{
	minimaxDepth = md;
	numberOfBranches = nob;
}

void Computer::MakeAMove(const Board& board, ControllerTurnInformationPackage& receivedPackage, GameEngine* ge)
{
	Move moveToBePlayed = Minimax(board, minimaxDepth, numberOfBranches, board.whiteToMove, INT_MIN, INT_MAX).move;

	receivedPackage.selectedPiece = std::make_pair(moveToBePlayed.startX, moveToBePlayed.startY);
	receivedPackage.playedMove = moveToBePlayed;
	if (receivedPackage.playedMove.promotion == 'w' || receivedPackage.playedMove.promotion == 's')
		receivedPackage.playedMove.promotion = 'q';
}