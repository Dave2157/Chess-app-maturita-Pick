#include "GameEngine.h"
#include "Controller.h"
#include "Functions.h"

bool GameEngine::OnUserCreate()
{
	activeBoard.setBoardFEN("7K/1r6/r7/8/8/8/8/7k w KQkq - 0 0");
	activeBoard.currentTurnInformationPackage = { {-1, -1}, {-1, -1, -1, -1} };

	activeBoard.whitePlayer = new Player;
	activeBoard.blackPlayer = new Computer;

	return true;
}
bool GameEngine::OnUserUpdate(float elapsedTime)
{
	if (activeBoard.checkmate)
	{
		
	}
	else
	{
		(activeBoard.whiteToMove ? activeBoard.whitePlayer : activeBoard.blackPlayer)->MakeAMove(activeBoard, activeBoard.currentTurnInformationPackage, this);

		int selectedPieceX = activeBoard.currentTurnInformationPackage.selectedPiece.first;
		int selectedPieceY = activeBoard.currentTurnInformationPackage.selectedPiece.second;

		if (activeBoard.currentTurnInformationPackage.playedMove.targetX != -1)
		{
			makeMove(activeBoard, activeBoard.currentTurnInformationPackage.playedMove);
		}

		drawBoard();

		int bKingX = 0;
		int bKingY = 0;
		int wKingX = 0;
		int wKingY = 0;

		for (bKingX = 0; bKingX < 8; bKingX++)
			for (bKingY = 0; bKingY < 8; bKingY++)
				if (activeBoard.layout[bKingY][bKingX] == 'k')
					goto AG;
	AG:
		for (wKingX = 0; wKingX < 8; wKingX++)
			for (wKingY = 0; wKingY < 8; wKingY++)
				if (activeBoard.layout[wKingY][wKingX] == 'K')
					goto AH;
	AH:



		if (isSquareUnderAttack(activeBoard, bKingX, bKingY, true))
		{
			FillRect(bKingX * 16, bKingY * 16, 16, 1, RED);
			FillRect(bKingX * 16 + 15, bKingY * 16 + 1, 1, 14, RED);
			FillRect(bKingX * 16, bKingY * 16 + 15, 16, 1, RED);
			FillRect(bKingX * 16, bKingY * 16 + 1, 1, 14, RED);

		}
		if (isSquareUnderAttack(activeBoard, wKingX, wKingY, false))
		{
			FillRect(wKingX * 16, wKingY * 16, 16, 1, RED);
			FillRect(wKingX * 16 + 15, wKingY * 16 + 1, 1, 14, RED);
			FillRect(wKingX * 16, wKingY * 16 + 15, 16, 1, RED);
			FillRect(wKingX * 16, wKingY * 16 + 1, 1, 14, RED);
		}


		if (selectedPieceX != -1)
		{
			std::vector<Move> availableMovesForSelectedPiece = findLegalMovesForAPiece(activeBoard, activeBoard.layout[selectedPieceY][selectedPieceX], selectedPieceX, selectedPieceY);

			for (Move& move : availableMovesForSelectedPiece)
			{
				FillRect(move.targetX * 16 + 7, move.targetY * 16 + 7, 2, 2, RED);
			}
		}

		if (activeBoard.currentTurnInformationPackage.playedMove.promotion == 'w' || activeBoard.currentTurnInformationPackage.playedMove.promotion == 's')
		{
			int xInPixels = activeBoard.currentTurnInformationPackage.playedMove.targetX * 16 - 24;
			int yInPixels = activeBoard.currentTurnInformationPackage.playedMove.targetY * 16;
			if (xInPixels < 0)
				xInPixels = 0;
			if (xInPixels > 64)
				xInPixels = 64;
			Pixel colour = activeBoard.currentTurnInformationPackage.playedMove.promotion == 'w' ? WHITE : BLACK;

			FillRect(xInPixels, yInPixels, 64, 16, GREY);
			drawKnight(xInPixels, yInPixels, colour);
			drawBishop(xInPixels + 16, yInPixels, colour);
			drawRook(xInPixels + 32, yInPixels, colour);
			drawQueen(xInPixels + 48, yInPixels, colour);
		}
		else if (activeBoard.currentTurnInformationPackage.playedMove.targetX != -1)
		{
			activeBoard.currentTurnInformationPackage.playedMove = { -1, -1, -1, -1, false, 0, 0, 0 };
			activeBoard.whiteToMove = !activeBoard.whiteToMove;
		}




		std::vector<Move> allLegalMoves;
		std::vector <pair<int, int>> piecesLocations = findAllPieces(activeBoard, activeBoard.whiteToMove);

		for (pair<int, int> pieceLoc : piecesLocations)
		{
			char pieceType = activeBoard.layout[pieceLoc.second][pieceLoc.first];
			auto legalMovesForThisPiece = findLegalMovesForAPiece(activeBoard, pieceType, pieceLoc.first, pieceLoc.second);
			allLegalMoves.insert(allLegalMoves.end(), legalMovesForThisPiece.begin(), legalMovesForThisPiece.end());
		}

		if (!allLegalMoves.size())
		{
			activeBoard.checkmate = activeBoard.whiteToMove ? 'w' : 'b';
		}
	}

	


	return true;
}