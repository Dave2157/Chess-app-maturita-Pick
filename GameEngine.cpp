#include "GameEngine.h"
#include "Controller.h"
#include "Functions.h"
#include <fstream>

bool GameEngine::OnUserCreate()
{
	//activeBoard.setBoardFEN("7K/1r6/r7/8/8/8/8/7k w KQkq - 0 0");
	activeBoard.setBoardFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
	//activeBoard.setBoardFEN("7k/8/1P6/6q1/8/8/PPP5/1KR5 w KQkq - 0 0");
	//activeBoard.setBoardFEN("k8/8/2Q5/8/8/8/8/K7 b KQkq - 0 0");
	//activeBoard.setBoardFEN("P7/p3P2p/1p3k2/2p5/8/P3R3/3q1PB1/4R1K1 w KQkq - 0 0");
	//activeBoard.setBoardFEN("rnb1kbnr/pppp1ppp/5q2/6B1/4P3/2N2NP1/PPP2P1P/R2QKB1R b KQkq - 0 0");

	activeBoard.currentTurnInformationPackage = { {-1, -1}, {-1, -1, -1, -1} };

	activeBoard.whitePlayer = new Player;
	activeBoard.blackPlayer = new Computer(4, 5);


	savedGame = true;
	playing = false;
	menuState = 0;
	p1set = 0;
	p2set = 0;


	return true;
}
bool GameEngine::OnUserUpdate(float elapsedTime)
{

	if (playing)
	{
		if (activeBoard.checkmate)
		{
			std::cout << activeBoard.checkmate;
		}
		else
		{
			if (checkForStalemate(activeBoard, activeBoard.whiteToMove))
			{
				activeBoard.checkmate = 's';
				return true;
			}
				

			(activeBoard.whiteToMove ? activeBoard.whitePlayer : activeBoard.blackPlayer)->MakeAMove(activeBoard, activeBoard.currentTurnInformationPackage, this);

			int selectedPieceX = activeBoard.currentTurnInformationPackage.selectedPiece.first;
			int selectedPieceY = activeBoard.currentTurnInformationPackage.selectedPiece.second;

			Move playedMove = activeBoard.currentTurnInformationPackage.playedMove;

			if (playedMove.targetX != -1 && !(playedMove.promotion == 'w' || playedMove.promotion == 's'))
			{
				if (!(activeBoard.layout[playedMove.targetY][playedMove.targetX] != ' ' || activeBoard.layout[playedMove.startY][playedMove.startX] == 'P' || activeBoard.layout[playedMove.startY][playedMove.startX] == 'p'))
					activeBoard.fiftyMoveRuleCounter++;
				else
					activeBoard.fiftyMoveRuleCounter = 0;

				makeMove(activeBoard, playedMove);
				activeBoard.history.push_back(boardIntoString(activeBoard));
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

				if (!activeBoard.whiteToMove)
					activeBoard.fullMoves++;

				activeBoard.whiteToMove = !activeBoard.whiteToMove;
			}




			if (checkForCheckmate(activeBoard, true))
				activeBoard.checkmate = 'w';
			else if (checkForCheckmate(activeBoard, false))
				activeBoard.checkmate = 'b';
		}

	}
	else
	{
		Clear(Pixel(91, 56, 7));
		switch (menuState)
		{
		case 0:
		{
			drawString("CHESS", 16, ScreenWidth() / 2 - 20, ScreenHeight() / 4, WHITE);
			makeButton(10, ScreenHeight() / 2, "PLAY", 32, 16, 8, BLACK, WHITE, GREY, VERY_DARK_GREY, 1);
			makeButton(10, ScreenHeight() / 2 + 40, "QUIT", 32, 16, 8, BLACK, WHITE, GREY, VERY_DARK_GREY, 2);
			if (savedGame)
				makeButton(50, ScreenHeight() / 2, "CONTINUE", 64, 16, 8, BLACK, WHITE, GREY, VERY_DARK_GREY, 3);
			break;
		}
		case 1:
		{

			if (p1set == 'p')
			{

				if (makeButton(5, ScreenHeight() / 8, "PLAYER", 48, 16, 8, WHITE, WHITE, VERY_DARK_GREY, VERY_DARK_GREY, 1))
				{
					if (!activeBoard.whitePlayer)
						delete activeBoard.whitePlayer;
					activeBoard.whitePlayer = new Player;

					p1set = 'p';
				}
				
			}
			else
			{
				if (makeButton(5, ScreenHeight() / 8, "PLAYER", 48, 16, 8, BLACK, WHITE, GREY, VERY_DARK_GREY, 1))
				{
					if (!activeBoard.whitePlayer)
						delete activeBoard.whitePlayer;
					activeBoard.whitePlayer = new Player;

					p1set = 'p';
				}
			}


			if (p1set == 'c')
			{
				if (makeButton(5, ScreenHeight() / 4, "COMPUTER", 48, 16, 8, WHITE, WHITE, VERY_DARK_GREY, VERY_DARK_GREY, 1))
				{
					if (!activeBoard.whitePlayer)
						delete activeBoard.whitePlayer;
					activeBoard.whitePlayer = new Computer(4, 5);

					p1set = 'c';
				}
			}
			else
			{
				if (makeButton(5, ScreenHeight() / 4, "COMPUTER", 48, 16, 8, BLACK, WHITE, GREY, VERY_DARK_GREY, 1))
				{
					if (!activeBoard.whitePlayer)
						delete activeBoard.whitePlayer;
					activeBoard.whitePlayer = new Computer(4, 5);

					p1set = 'c';
				}
			}
			drawString("WHITE", 16, 5, ScreenHeight() / 2, WHITE);

			if (p2set == 'p')
			{
				if (makeButton(ScreenWidth() - 53, ScreenHeight() / 8, "PLAYER", 48, 16, 8, WHITE, WHITE, VERY_DARK_GREY, VERY_DARK_GREY, 1))
				{
					if (!activeBoard.blackPlayer)
						delete activeBoard.blackPlayer;
					activeBoard.blackPlayer = new Player;

					p2set = 'p';
				}
			}
			else
			{
				if (makeButton(ScreenWidth() - 53, ScreenHeight() / 8, "PLAYER", 48, 16, 8, BLACK, WHITE, GREY, VERY_DARK_GREY, 1))
				{
					if (!activeBoard.blackPlayer)
						delete activeBoard.blackPlayer;
					activeBoard.blackPlayer = new Player;

					p2set = 'p';
				}
			}
			
			if (p2set == 'c')
			{
				if (makeButton(ScreenWidth() - 53, ScreenHeight() / 4, "COMPUTER", 48, 16, 8, WHITE, WHITE, VERY_DARK_GREY, VERY_DARK_GREY, 1))
				{
					if (!activeBoard.blackPlayer)
						delete activeBoard.blackPlayer;
					activeBoard.blackPlayer = new Computer(4, 5);

					p2set = 'c';
				}
			}
			else
			{
				if (makeButton(ScreenWidth() - 53, ScreenHeight() / 4, "COMPUTER", 48, 16, 8, BLACK, WHITE, GREY, VERY_DARK_GREY, 1))
				{
					if (!activeBoard.blackPlayer)
						delete activeBoard.blackPlayer;
					activeBoard.blackPlayer = new Computer(4, 5);

					p2set = 'c';
				}
			}
			
			drawString("BLACK", 16, ScreenWidth() - 53, ScreenHeight() / 2, WHITE);

			if (makeButton(ScreenWidth() / 2 - 24, 3 * ScreenHeight() / 4, "PLAY", 48, 16, 8, BLACK, WHITE, GREY, VERY_DARK_GREY, 1) && p1set && p2set)
			{
				activeBoard.setBoardFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
				drawBoard();
				playing = true;
			}

			break;
		}
		case 2:
		{
			return false;
		}
		}
	}
	return true;
}