#include "GameEngine.h"
#include "BoardAndUtils.h"
#include "Functions.h"
#include "Minimax.h"
#include "Logs.h"

MinimaxPackage Minimax(const Board& board, int depthInHalfTurns, int numberOfBranches, bool whitesTurn, int alpha, int beta)
{
	std::vector<pair<int, int>> piecesLocations = findAllPieces(board, whitesTurn);

	std::vector<Move> allLegalMoves;

	for (pair<int, int> pieceLoc : piecesLocations)
	{
		char pieceType = board.layout[pieceLoc.second][pieceLoc.first];
		Board newBoard(board);
		newBoard.whiteToMove = whitesTurn;
		auto legalMovesForThisPiece = findLegalMovesForAPiece(newBoard, pieceType, pieceLoc.first, pieceLoc.second);

		for (auto move : legalMovesForThisPiece)
		{
			if (!move.promotion)
				continue;
			if (move.promotion == 'w')
			{
				move.promotion = 'Q';
				allLegalMoves.push_back(move);
				move.promotion = 'R';
				allLegalMoves.push_back(move);
				move.promotion = 'N';
				allLegalMoves.push_back(move);
				move.promotion = 'B';
				allLegalMoves.push_back(move);
			}
			else
			{
				move.promotion = 'q';
				allLegalMoves.push_back(move);
				move.promotion = 'r';
				allLegalMoves.push_back(move);
				move.promotion = 'n';
				allLegalMoves.push_back(move);
				move.promotion = 'b';
				allLegalMoves.push_back(move);
			}
		}

		allLegalMoves.insert(allLegalMoves.end(), legalMovesForThisPiece.begin(), legalMovesForThisPiece.end());

		auto garbageStart = std::remove_if(allLegalMoves.begin(), allLegalMoves.end(),
			[](Move& m)
			{
				return m.promotion == 'w' || m.promotion == 's';
			});
		allLegalMoves.erase(garbageStart, allLegalMoves.end());
	}

	vector<MinimaxPackage> movesWithEvaluations;

	if (!depthInHalfTurns)
	{
		for (Move move : allLegalMoves)
		{
			Board newBoard(board);
			char promotionState = move.promotion;
			makeMove(newBoard, move);

			int score;

			score = evaluatePosition(newBoard);

			move.promotion = promotionState;
			movesWithEvaluations.push_back({ move, score });
			
		}
		std::sort(movesWithEvaluations.begin(), movesWithEvaluations.end(), [&whitesTurn](const MinimaxPackage& a, const MinimaxPackage& b)
			{
				if (whitesTurn)
					return a.score > b.score;
				return a.score < b.score;
			});

		return movesWithEvaluations[0];
	}
	else
	{

		for (Move move : allLegalMoves)
		{
			Board newBoard(board);
			char promotionState = move.promotion;
			makeMove(newBoard, move);

			if (checkForCheckmate(newBoard, !whitesTurn))
				return { move, whitesTurn ? INT_MAX : INT_MIN };

			int score;

			if (checkForStalemate(newBoard, !whitesTurn))
				score = 0;
			else
				score = Minimax(newBoard, 0, numberOfBranches, !whitesTurn, INT_MIN, INT_MAX).score;

			

			

			move.promotion = promotionState;
			movesWithEvaluations.push_back({ move, score });

			
		}
		std::sort(movesWithEvaluations.begin(), movesWithEvaluations.end(), [&whitesTurn](const MinimaxPackage& a, const MinimaxPackage& b)
			{
				int difference = abs(a.score - b.score);
				if (difference <= 10)
					return randomBool();

				if (whitesTurn)
					return a.score > b.score;
				return a.score < b.score;
			});
	}
	

	vector<MinimaxPackage> movesToExamineFurther;
		
	for (int i = 0; i < numberOfBranches && i < movesWithEvaluations.size(); i++)
	{
		if (alpha >= beta)
			break;

		movesToExamineFurther.push_back(movesWithEvaluations[i]);

		Board newBoard(board);
		char promotionState = movesToExamineFurther[i].move.promotion;
		makeMove(newBoard, movesToExamineFurther[i].move);
		movesToExamineFurther[i].move.promotion = promotionState;
		
		if (checkForStalemate(newBoard, !whitesTurn))
		{
			movesToExamineFurther[i].score = 0;
			break;
		}
			


		//logAMoveWtihEvaluationsOfBothPositionsIntoAFile(board, movesToExamineFurther[i].move, "Logs.txt");						//=============================================================================== LOG
		

		if (whitesTurn)
		{
			movesToExamineFurther[i].score = Minimax(newBoard, depthInHalfTurns - 1, numberOfBranches, !whitesTurn, alpha, INT_MAX).score;
			if (movesToExamineFurther[i].score > alpha)
				alpha = movesToExamineFurther[i].score;
		}
		else
		{
			movesToExamineFurther[i].score = Minimax(newBoard, depthInHalfTurns - 1, numberOfBranches, !whitesTurn, INT_MIN, beta).score;
			if (movesToExamineFurther[i].score < beta)
				beta = movesToExamineFurther[i].score;
		}
	}

	std::sort(movesToExamineFurther.begin(), movesToExamineFurther.end(), [&whitesTurn](const MinimaxPackage& a, const MinimaxPackage& b)
		{
			int difference = abs(a.score - b.score);
			if (difference <= 10)
				return randomBool();

			if (whitesTurn)
				return a.score > b.score;
			return a.score < b.score;
		});

	return movesToExamineFurther[0];
}

int evaluatePosition(const Board& board)
{
	int score = 0;
	const auto& layout = board.layout;

	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
		{
			switch (layout[y][x])
			{
			case ' ':
				continue;
			case 'p':
				score -= evaluatePawn(board, x, y, false);
				break;
			case 'r':
				score -= evaluateRook(board, x, y, false);
				break;
			case 'q':
				score -= evaluateQueen(board, x, y, false);
				break;
			case 'n':
				score -= evaluateKnight(board, x, y, false);
				break;
			case 'b':
				score -= evaluateBishop(board, x, y, false);
				break;
			case 'k':
				score -= evaluateKing(board, x, y, false);
				break;


			case 'P':
				score += evaluatePawn(board, x, y, true);
				break;
			case 'R':
				score += evaluateRook(board, x, y, true);
				break;
			case 'Q':
				score += evaluateQueen(board, x, y, true);
				break;
			case 'N':
				score += evaluateKnight(board, x, y, true);
				break;
			case 'B':
				score += evaluateBishop(board, x, y, true);
				break;
			case 'K':
				score += evaluateKing(board, x, y, true);
				break;
			}
		}

	int pawnStructureScore = 0;
	pawnStructureScore += evaluatePawnStucture(board, true);
	pawnStructureScore -= evaluatePawnStucture(board, false);
	score += pawnStructureScore;

	int oneSideHasAWeakColorScore = 0;
	oneSideHasAWeakColorScore += evaluateWeaknessesOnColoredSquares(board, true);
	oneSideHasAWeakColorScore -= evaluateWeaknessesOnColoredSquares(board, false);
	score += oneSideHasAWeakColorScore;

	return score;
}

int evaluatePawn(const Board& board, int x, int y, bool isWhite)
{
	int score = 100;

	int centerControlScore = 0;
	if (y == (isWhite ? 4 : 3))
	{
		if (x == 2 || x == 5)
			centerControlScore += 20;
		else if (x == 3 || x == 4)
			centerControlScore += 30;
	}
	score += centerControlScore;

	/*int connectedPawnsScore = 0;
	if (isWhite)
	{
		for (int i = -1; i < 2; i += 2)
			for (int j = -1; j < 1; j += 2)
				if (boundsOk(x + i, y + j) && board.layout[y + j][x + i] == 'P')
					connectedPawnsScore += 10;
	}
	else
	{
		for (int i = -1; i < 2; i += 2)
			for (int j = -1; j < 1; j += 2)
				if (boundsOk(x + i, y + j) && board.layout[y + j][x + i] == 'p')
					connectedPawnsScore += 10;
	}
	score += connectedPawnsScore;*/

	int isolatedPawnScore = 0;
	int passedPawnScore = 0;
	bool friendlyPawnsInAdjacentColumns = false;
	bool enemyPawnsInAdjacentColumns = false;
	if (isWhite)
	{
		for (int i = 1; i < 7; i++)
		{
			if (!boundsOk(x - 1, i))
				break;
			if (board.layout[i][x - 1] == 'P')
			{
				friendlyPawnsInAdjacentColumns = true;
			}
			else if (board.layout[i][x - 1] == 'p')
			{
				enemyPawnsInAdjacentColumns = true;
			}
			if (friendlyPawnsInAdjacentColumns && enemyPawnsInAdjacentColumns)
				goto endOfSearchingForPawnsLoop;

		}
		for (int i = 1; i < 7; i++)
		{
			if (!boundsOk(x + 1, i))
				break;
			if (board.layout[i][x + 1] == 'P')
			{
				friendlyPawnsInAdjacentColumns = true;
			}
			else if (board.layout[i][x + 1] == 'p')
			{
				enemyPawnsInAdjacentColumns = true;
			}
			if (friendlyPawnsInAdjacentColumns && enemyPawnsInAdjacentColumns)
				goto endOfSearchingForPawnsLoop;
		}
	}
	else
	{
		for (int i = 1; i < 7; i++)
		{
			if (!boundsOk(x - 1, i))
				break;
			if (board.layout[i][x - 1] == 'p')
			{
				friendlyPawnsInAdjacentColumns = true;
			}
			else if (board.layout[i][x - 1] == 'P')
			{
				enemyPawnsInAdjacentColumns = true;
			}
			if (friendlyPawnsInAdjacentColumns && enemyPawnsInAdjacentColumns)
				goto endOfSearchingForPawnsLoop;
		}
		for (int i = 1; i < 7; i++)
		{
			if (!boundsOk(x + 1, i))
				break;
			if (board.layout[i][x + 1] == 'p')
			{
				friendlyPawnsInAdjacentColumns = true;
			}
			else if (board.layout[i][x + 1] == 'P')
			{
				enemyPawnsInAdjacentColumns = true;
			}
			if (friendlyPawnsInAdjacentColumns && enemyPawnsInAdjacentColumns)
				goto endOfSearchingForPawnsLoop;
		}
	}
endOfSearchingForPawnsLoop:
	if (!friendlyPawnsInAdjacentColumns)
		isolatedPawnScore -= 80;
	if (!enemyPawnsInAdjacentColumns)
		passedPawnScore += 100;
	score += isolatedPawnScore;
	score += passedPawnScore;


	return score;
}
int evaluateRook(const Board& board, int x, int y, bool isWhite)
{
	int score = 500;

	int squareControlScore = 0;
	std::vector<pair<int, int>> offsets = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0} };
	for (auto offset : offsets)
	{
		for (int i = 1; i < 8; i++)
		{
			if (!boundsOk(i * offset.first + x, i * offset.second + y) || (isWhite ? isupper : islower)(board.layout[i * offset.second + y][i * offset.first + x]))
				break;
			squareControlScore += 5;
			if ((isWhite ? islower : isupper)(board.layout[i * offset.second + y][i * offset.first + x]))
				break;
		}
	}
	score += squareControlScore;
	
	return score;
}
int evaluateKnight(const Board& board, int x, int y, bool isWhite)
{
	int score = 300;

	auto moves = findLegalMovesForAPiece(board, isWhite ? 'N' : 'n', x, y);
	int centeredKnightScore = moves.size() * 10;
	score += centeredKnightScore;

	return score;
}
int evaluateBishop(const Board& board, int x, int y, bool isWhite)
{
	int score = 300;

	int squareControlScore = 0;
	for (int i = -1; i < 2; i += 2)
		for (int j = -1; j < 2; j += 2)
			for (int k = 1; k < 8; k++)
			{
				if (!boundsOk(i * k + x, j * k + y) || (isWhite ? isupper : islower)(board.layout[j * k + y][i * k + x]))
					break;
				squareControlScore += 5;
				if ((isWhite ? islower : isupper)(board.layout[j * k + y][i * k + x]))
					break;
			}
	score += squareControlScore;


	return score;
}
int evaluateQueen(const Board& board, int x, int y, bool isWhite)
{
	int score = 900;

	int squareControlScore = 0;
	std::vector<pair<int, int>> offsets = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }, { 1, 1 }, { 1, -1 }, { 1, 1 }, { -1, -1 } };
	for (auto offset : offsets)
	{
		for (int i = 1; i < 8; i++)
		{
			if (!boundsOk(i * offset.first + x, i * offset.second + y) || (isWhite ? isupper : islower)(board.layout[i * offset.second + y][i * offset.first + x]))
				break;
			squareControlScore += 3;
			if ((isWhite ? islower : isupper)(board.layout[i * offset.second + y][i * offset.first + x]))
				break;
		}
	}
	score += squareControlScore;

	/*int escapeSquareScore = 0;
	bool escapeSquares = false;
	auto queenMoves = findLegalMovesForAPiece(board, (isWhite ? 'Q' : 'q'), x, y);
	for (auto& move : queenMoves)
	{
		if (!isSquareUnderAttack(board, move.targetX, move.targetY, !isWhite))
		{
			escapeSquares = true;
			break;
		}
	}
	if (!escapeSquares)
		escapeSquareScore -= 200;
	score += escapeSquareScore;*/

	return score;
}
int evaluateKing(const Board& board, int x, int y, bool isWhite)
{
	int score = 0;
	int numberOfEnemyMajorPieces = 0;
	if (isWhite)
	{
		numberOfEnemyMajorPieces += findPiecesOfAGivenType(board, 'q').size();
		numberOfEnemyMajorPieces += findPiecesOfAGivenType(board, 'n').size();
		numberOfEnemyMajorPieces += findPiecesOfAGivenType(board, 'b').size();
		numberOfEnemyMajorPieces += findPiecesOfAGivenType(board, 'r').size();

	}
	else
	{
		numberOfEnemyMajorPieces += findPiecesOfAGivenType(board, 'Q').size();
		numberOfEnemyMajorPieces += findPiecesOfAGivenType(board, 'N').size();
		numberOfEnemyMajorPieces += findPiecesOfAGivenType(board, 'B').size();
		numberOfEnemyMajorPieces += findPiecesOfAGivenType(board, 'R').size();
	}
	
	if (numberOfEnemyMajorPieces > 3)
	{
		int closedKingScore = 0;
		std::vector<pair<int, int>> offsets = !isWhite ? std::vector<pair<int, int>>({ { 0, 1 }, { -1, 1 }, { 1, 1 } }) : std::vector<pair<int, int>>({ {-1, -1}, { 0, -1 }, { 1, -1 } });
		auto caseFunction = isWhite ? isupper : islower;
		for (auto offset : offsets)
		{
			if (boundsOk(x + offset.first, y + offset.second) && caseFunction(board.layout[y + offset.second][x + offset.first]))
				closedKingScore += 10;
		}
		score += closedKingScore;
	}

	if (isSquareUnderAttack(board, x, y, !isWhite))
	{
		auto allPieces = findAllPieces(board, isWhite);
		std::vector<Move> allLegalMoves;
		Board tempBoard(board);
		tempBoard.whiteToMove = !tempBoard.whiteToMove;

		for (pair<int, int> piece : allPieces)
		{
			char pieceType = board.layout[piece.second][piece.first];
			
			auto legalMovesForThisPiece = findLegalMovesForAPiece(tempBoard, pieceType, piece.first, piece.second);

			allLegalMoves.insert(allLegalMoves.end(), legalMovesForThisPiece.begin(), legalMovesForThisPiece.end());
		}
		if (!allLegalMoves.size())
			score -= 1000000;
	}


	return score;
}

int evaluatePawnStucture(const Board& board, bool white)
{
	int score = 0;
	if (white)
	{
		auto pawns = findPiecesOfAGivenType(board, 'P');
		for (auto pawn : pawns)
		{
			int numberOfProtectingPawns = 0;
			if (boundsOk(pawn.first + 1, pawn.second + 1) && board.layout[pawn.second + 1][pawn.first + 1] == 'P')
				numberOfProtectingPawns++;
			if (boundsOk(pawn.first - 1, pawn.second + 1) && board.layout[pawn.second + 1][pawn.first - 1] == 'P')
				numberOfProtectingPawns++;
			score += 5 * numberOfProtectingPawns;

			if (!numberOfProtectingPawns && isSquareUnderAttack(board, pawn.first, pawn.second, true))
				score += 10;
		}
	}
	else
	{
		auto pawns = findPiecesOfAGivenType(board, 'p');
		for (auto pawn : pawns)
		{
			int numberOfProtectingPawns = 0;
			if (boundsOk(pawn.first + 1, pawn.second - 1) && board.layout[pawn.second - 1][pawn.first + 1] == 'p')
				numberOfProtectingPawns++;
			if (boundsOk(pawn.first - 1, pawn.second - 1) && board.layout[pawn.second - 1][pawn.first - 1] == 'p')
				numberOfProtectingPawns++;
			score -= 5 * numberOfProtectingPawns;

			if (!numberOfProtectingPawns && isSquareUnderAttack(board, pawn.first, pawn.second, false))
				score -= 10;
		}
	}
	return score;
}

int evaluateWeaknessesOnColoredSquares(const Board& board, bool lightSquares)
{
	int score;

	int numberOfColoredSquaresControlledByWhite = 0;
	int numberOfColoredSquaresControlledByBlack = 0;


	int remainder = lightSquares ? 0 : 1;
	
	auto whitePawns = findPiecesOfAGivenType(board, 'P');
	auto blackPawns = findPiecesOfAGivenType(board, 'p');

	for (auto wPawn : whitePawns)
	{
		if ((wPawn.first + wPawn.second) % 2 == remainder)
		{
			numberOfColoredSquaresControlledByWhite += (wPawn.first == 0 || wPawn.first == 7) ? 1 : 2;
		}
	}

	for (auto bPawn : blackPawns)
	{
		if ((bPawn.first + bPawn.second) % 2 == remainder)
		{
			numberOfColoredSquaresControlledByBlack += (bPawn.first == 0 || bPawn.first == 7) ? 1 : 2;
		}
	}

	auto whiteBishops = findPiecesOfAGivenType(board, 'B');
	auto blackBishops = findPiecesOfAGivenType(board, 'b');

	for (auto wBishop : whiteBishops)
	{
		if ((wBishop.first + wBishop.second) % 2 == remainder)
			for (int i = -1; i < 2; i += 2)
				for (int j = -1; j < 2; j += 2)
					for (int k = 0; k < 8; k++)
					{
						if (!boundsOk(i * k + wBishop.first, j * k + wBishop.second))
							break;
						numberOfColoredSquaresControlledByWhite += 5;
						if (board.layout[j * k + wBishop.second][i * k + wBishop.first])
							break;
					}
	}

	for (auto bBishop : blackBishops)
	{
		if ((bBishop.first + bBishop.second) % 2 == remainder)
			for (int i = -1; i < 2; i += 2)
				for (int j = -1; j < 2; j += 2)
					for (int k = 0; k < 8; k++)
					{
						if (!boundsOk(i * k + bBishop.first, j * k + bBishop.second))
							break;
						numberOfColoredSquaresControlledByBlack += 5;
						if (board.layout[j * k + bBishop.second][i * k + bBishop.first])
							break;
					}
	}

	int difference = numberOfColoredSquaresControlledByWhite - numberOfColoredSquaresControlledByBlack;
	if (difference > 8)
		score = 200;
	else if (difference > 4)
		score = 100;
	else if (difference < 8)
		score = -200;
	else if (difference < 4)
		score = -100;

	return score;
}