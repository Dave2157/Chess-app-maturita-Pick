#include "Logs.h"
#include "Minimax.h"
#include "Functions.h"
#include <wchar.h>
#include <codecvt>
using namespace std;

void logAMoveWtihEvaluationsOfBothPositionsIntoAFile(const Board& board, Move& move, string fileName)
{
	wofstream file(fileName, fstream::app);
	file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

	Board newBoard(board);
	makeMove(newBoard, move);

	asciiDrawBoard(file, board);
	
	auto b1blackPawns = findPiecesOfAGivenType(board, 'p');
	auto b1whitePawns = findPiecesOfAGivenType(board, 'P');
	auto b1blackRooks = findPiecesOfAGivenType(board, 'r');
	auto b1whiteRooks = findPiecesOfAGivenType(board, 'R');
	auto b1blackKnights = findPiecesOfAGivenType(board, 'n');
	auto b1whiteKnights = findPiecesOfAGivenType(board, 'N');
	auto b1blackBishops = findPiecesOfAGivenType(board, 'b');
	auto b1whiteBishops = findPiecesOfAGivenType(board, 'B');
	auto b1blackQueens = findPiecesOfAGivenType(board, 'q');
	auto b1whiteQueens = findPiecesOfAGivenType(board, 'Q');
	auto b1blackKing = findPiecesOfAGivenType(board, 'k');
	auto b1whiteKing = findPiecesOfAGivenType(board, 'K');
	
	int blackPawnPoints = 0;
	for (auto piece : b1blackPawns)
		blackPawnPoints += evaluatePawn(board, piece.first, piece.second, false);
	int whitePawnPoints = 0;
	for (auto piece : b1whitePawns)
		whitePawnPoints += evaluatePawn(board, piece.first, piece.second, true);
	int blackRookPoints = 0;
	for (auto piece : b1blackRooks)
		blackRookPoints += evaluateRook(board, piece.first, piece.second, false);
	int whiteRookPoints = 0;
	for (auto piece : b1whiteRooks)
		whiteRookPoints += evaluateRook(board, piece.first, piece.second, true);
	int blackKnightPoints = 0;
	for (auto piece : b1blackKnights)
		blackKnightPoints += evaluateKnight(board, piece.first, piece.second, false);
	int whiteKnightPoints = 0;
	for (auto piece : b1whiteKnights)
		whiteKnightPoints += evaluateKnight(board, piece.first, piece.second, true);
	int blackBishopPoints = 0;
	for (auto piece : b1blackBishops)
		blackBishopPoints += evaluateBishop(board, piece.first, piece.second, false);
	int whiteBishopPoints = 0;
	for (auto piece : b1whiteBishops)
		whiteBishopPoints += evaluateBishop(board, piece.first, piece.second, true);
	int blackQueenPoints = 0;
	for (auto piece : b1blackQueens)
		blackQueenPoints += evaluateQueen(board, piece.first, piece.second, false);
	int whiteQueenPoints = 0;
	for (auto piece : b1whiteQueens)
		whiteQueenPoints += evaluateQueen(board, piece.first, piece.second, true);
	int blackKingPoints = evaluateKing(board, b1blackKing[0].first, b1blackKing[0].second, false);
	int whiteKingPoints = evaluateKing(board, b1whiteKing[0].first, b1whiteKing[0].second, true);

	file << "\nWHITE: " << whiteBishopPoints + whiteKingPoints + whiteKnightPoints + whitePawnPoints + whiteQueenPoints + whiteRookPoints << endl;
	file << "\tPawns: " << whitePawnPoints << endl;
	for (auto piece : b1whitePawns)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluatePawn(board, piece.first, piece.second, true) << endl;
	}
	file << "\tRooks: " << whiteRookPoints << endl;
	for (auto piece : b1whiteRooks)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateRook(board, piece.first, piece.second, true) << endl;
	}
	file << "\tKnights: " << whiteKnightPoints << endl;
	for (auto piece : b1whiteKnights)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateKnight(board, piece.first, piece.second, true) << endl;
	}
	file << "\tBishops: " << whiteBishopPoints << endl;
	for (auto piece : b1whiteBishops)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateBishop(board, piece.first, piece.second, true) << endl;
	}
	file << "\tQueens: " << whiteQueenPoints << endl;
	for (auto piece : b1whiteQueens)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateQueen(board, piece.first, piece.second, true) << endl;
	}
	file << "\tKing: " << whiteKingPoints << endl;

	file << "BLACK: " << blackBishopPoints + blackKingPoints + blackKnightPoints + blackPawnPoints + blackQueenPoints + blackRookPoints << endl;
	file << "\tPawns: " << blackPawnPoints << endl;
	for (auto piece : b1blackPawns)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluatePawn(board, piece.first, piece.second, false) << endl;
	}
	file << "\tRooks: " << blackRookPoints << endl;
	for (auto piece : b1blackRooks)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateRook(board, piece.first, piece.second, false) << endl;
	}
	file << "\tKnights: " << blackKnightPoints << endl;
	for (auto piece : b1blackKnights)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateKnight(board, piece.first, piece.second, false) << endl;
	}
	file << "\tBishops: " << blackBishopPoints << endl;
	for (auto piece : b1blackBishops)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateBishop(board, piece.first, piece.second, false) << endl;
	}
	file << "\tQueens: " << blackQueenPoints << endl;
	for (auto piece : b1blackQueens)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateQueen(board, piece.first, piece.second, false) << endl;
	}
	file << "\tKing: " << blackKingPoints << endl << endl;

	asciiDrawBoard(file, newBoard);

	auto b2blackPawns = findPiecesOfAGivenType(newBoard, 'p');
	auto b2whitePawns = findPiecesOfAGivenType(newBoard, 'P');
	auto b2blackRooks = findPiecesOfAGivenType(newBoard, 'r');
	auto b2whiteRooks = findPiecesOfAGivenType(newBoard, 'R');
	auto b2blackKnights = findPiecesOfAGivenType(newBoard, 'n');
	auto b2whiteKnights = findPiecesOfAGivenType(newBoard, 'N');
	auto b2blackBishops = findPiecesOfAGivenType(newBoard, 'b');
	auto b2whiteBishops = findPiecesOfAGivenType(newBoard, 'B');
	auto b2blackQueens = findPiecesOfAGivenType(newBoard, 'q');
	auto b2whiteQueens = findPiecesOfAGivenType(newBoard, 'Q');
	auto b2blackKing = findPiecesOfAGivenType(newBoard, 'k');
	auto b2whiteKing = findPiecesOfAGivenType(newBoard, 'K');

	blackPawnPoints = 0;
	for (auto piece : b2blackPawns)
		blackPawnPoints += evaluatePawn(newBoard, piece.first, piece.second, false);
	whitePawnPoints = 0;
	for (auto piece : b2whitePawns)
		whitePawnPoints += evaluatePawn(newBoard, piece.first, piece.second, true);
	blackRookPoints = 0;
	for (auto piece : b2blackRooks)
		blackRookPoints += evaluateRook(newBoard, piece.first, piece.second, false);
	whiteRookPoints = 0;
	for (auto piece : b2whiteRooks)
		whiteRookPoints += evaluateRook(newBoard, piece.first, piece.second, true);
	blackKnightPoints = 0;
	for (auto piece : b2blackKnights)
		blackKnightPoints += evaluateKnight(newBoard, piece.first, piece.second, false);
	whiteKnightPoints = 0;
	for (auto piece : b2whiteKnights)
		whiteKnightPoints += evaluateKnight(newBoard, piece.first, piece.second, true);
	blackBishopPoints = 0;
	for (auto piece : b2blackBishops)
		blackBishopPoints += evaluateBishop(newBoard, piece.first, piece.second, false);
	whiteBishopPoints = 0;
	for (auto piece : b2whiteBishops)
		whiteBishopPoints += evaluateBishop(newBoard, piece.first, piece.second, true);
	blackQueenPoints = 0;
	for (auto piece : b2blackQueens)
		blackQueenPoints += evaluateQueen(newBoard, piece.first, piece.second, false);
	whiteQueenPoints = 0;
	for (auto piece : b2whiteQueens)
		whiteQueenPoints += evaluateQueen(newBoard, piece.first, piece.second, true);
	blackKingPoints = evaluateKing(newBoard, b1blackKing[0].first, b1blackKing[0].second, false);
	whiteKingPoints = evaluateKing(newBoard, b1whiteKing[0].first, b1whiteKing[0].second, true);
	
	file << "\nWHITE: " << whiteBishopPoints + whiteKingPoints + whiteKnightPoints + whitePawnPoints + whiteQueenPoints + whiteRookPoints << endl;
	file << "\tPawns: " << whitePawnPoints << endl;
	for (auto piece : b2whitePawns)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluatePawn(board, piece.first, piece.second, true) << endl;
	}
	file << "\tRooks: " << whiteRookPoints << endl;
	for (auto piece : b2whiteRooks)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateRook(board, piece.first, piece.second, true) << endl;
	}
	file << "\tKnights: " << whiteKnightPoints << endl;
	for (auto piece : b2whiteKnights)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateKnight(board, piece.first, piece.second, true) << endl;
	}
	file << "\tBishops: " << whiteBishopPoints << endl;
	for (auto piece : b2whiteBishops)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateBishop(board, piece.first, piece.second, true) << endl;
	}
	file << "\tQueens: " << whiteQueenPoints << endl;
	for (auto piece : b2whiteQueens)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateQueen(board, piece.first, piece.second, true) << endl;
	}
	file << "\tKing: " << whiteKingPoints << endl;

	file << "BLACK: " << blackBishopPoints + blackKingPoints + blackKnightPoints + blackPawnPoints + blackQueenPoints + blackRookPoints << endl;
	file << "\tPawns: " << blackPawnPoints << endl;
	for (auto piece : b2blackPawns)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluatePawn(board, piece.first, piece.second, false) << endl;
	}
	file << "\tRooks: " << blackRookPoints << endl;
	for (auto piece : b2blackRooks)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateRook(board, piece.first, piece.second, false) << endl;
	}
	file << "\tKnights: " << blackKnightPoints << endl;
	for (auto piece : b2blackKnights)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateKnight(board, piece.first, piece.second, false) << endl;
	}
	file << "\tBishops: " << blackBishopPoints << endl;
	for (auto piece : b2blackBishops)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateBishop(board, piece.first, piece.second, false) << endl;
	}
	file << "\tQueens: " << blackQueenPoints << endl;
	for (auto piece : b2blackQueens)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateQueen(board, piece.first, piece.second, false) << endl;
	}
	file << "\tKing: " << blackKingPoints << endl << endl;
	file << "=============================================================================\n\n";


	file.close();
}

void asciiDrawBoard(wofstream& file, const Board& board)
{
	file << L'\u250f';
	for (int i = 1; i < 16; i++)
		file << ((i % 2 == 0) ? L'\u2533' : L'\u2501');
	file << L'\u2513' << endl;

	for (int i = 0; i < 15; i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < 17; j++)
				file << ((j % 2 == 0) ? (L'\u2503') : wchar_t(board.layout[i / 2][j / 2]));
		}
		else
		{
			file << L'\u2523';
			for (int j = 1; j < 16; j++)
				file << ((j % 2 == 0) ? L'\u254b' : L'\u2501');
			file << L'\u252b';
		}
		file << '\n';
	}

	file << L'\u2517';
	for (int i = 1; i < 16; i++)
		file << ((i % 2 == 0) ? L'\u253b' : L'\u2501');
	file << L'\u251b' << '\n';

}

void logASinglePositionEvaluationIntoAFile(string FEN, string fileName)
{
	Board board;
	board.setBoardFEN(FEN);

	wofstream file(fileName, fstream::app);
	file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

	Board newBoard(board);

	asciiDrawBoard(file, board);

	auto b1blackPawns = findPiecesOfAGivenType(board, 'p');
	auto b1whitePawns = findPiecesOfAGivenType(board, 'P');
	auto b1blackRooks = findPiecesOfAGivenType(board, 'r');
	auto b1whiteRooks = findPiecesOfAGivenType(board, 'R');
	auto b1blackKnights = findPiecesOfAGivenType(board, 'n');
	auto b1whiteKnights = findPiecesOfAGivenType(board, 'N');
	auto b1blackBishops = findPiecesOfAGivenType(board, 'b');
	auto b1whiteBishops = findPiecesOfAGivenType(board, 'B');
	auto b1blackQueens = findPiecesOfAGivenType(board, 'q');
	auto b1whiteQueens = findPiecesOfAGivenType(board, 'Q');
	auto b1blackKing = findPiecesOfAGivenType(board, 'k');
	auto b1whiteKing = findPiecesOfAGivenType(board, 'K');

	int blackPawnPoints = 0;
	for (auto piece : b1blackPawns)
		blackPawnPoints += evaluatePawn(board, piece.first, piece.second, false);
	int whitePawnPoints = 0;
	for (auto piece : b1whitePawns)
		whitePawnPoints += evaluatePawn(board, piece.first, piece.second, true);
	int blackRookPoints = 0;
	for (auto piece : b1blackRooks)
		blackRookPoints += evaluateRook(board, piece.first, piece.second, false);
	int whiteRookPoints = 0;
	for (auto piece : b1whiteRooks)
		whiteRookPoints += evaluateRook(board, piece.first, piece.second, true);
	int blackKnightPoints = 0;
	for (auto piece : b1blackKnights)
		blackKnightPoints += evaluateKnight(board, piece.first, piece.second, false);
	int whiteKnightPoints = 0;
	for (auto piece : b1whiteKnights)
		whiteKnightPoints += evaluateKnight(board, piece.first, piece.second, true);
	int blackBishopPoints = 0;
	for (auto piece : b1blackBishops)
		blackBishopPoints += evaluateBishop(board, piece.first, piece.second, false);
	int whiteBishopPoints = 0;
	for (auto piece : b1whiteBishops)
		whiteBishopPoints += evaluateBishop(board, piece.first, piece.second, true);
	int blackQueenPoints = 0;
	for (auto piece : b1blackQueens)
		blackQueenPoints += evaluateQueen(board, piece.first, piece.second, false);
	int whiteQueenPoints = 0;
	for (auto piece : b1whiteQueens)
		whiteQueenPoints += evaluateQueen(board, piece.first, piece.second, true);
	int blackKingPoints = evaluateKing(board, b1blackKing[0].first, b1blackKing[0].second, false);
	int whiteKingPoints = evaluateKing(board, b1whiteKing[0].first, b1whiteKing[0].second, true);

	file << "\nWHITE: " << whiteBishopPoints + whiteKingPoints + whiteKnightPoints + whitePawnPoints + whiteQueenPoints + whiteRookPoints << endl;
	file << "\tPawns: " << whitePawnPoints << endl;
	for (auto piece : b1whitePawns)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluatePawn(board, piece.first, piece.second, true) << endl;
	}
	file << "\tRooks: " << whiteRookPoints << endl;
	for (auto piece : b1whiteRooks)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateRook(board, piece.first, piece.second, true) << endl;
	}
	file << "\tKnights: " << whiteKnightPoints << endl;
	for (auto piece : b1whiteKnights)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateKnight(board, piece.first, piece.second, true) << endl;
	}
	file << "\tBishops: " << whiteBishopPoints << endl;
	for (auto piece : b1whiteBishops)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateBishop(board, piece.first, piece.second, true) << endl;
	}
	file << "\tQueens: " << whiteQueenPoints << endl;
	for (auto piece : b1whiteQueens)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateQueen(board, piece.first, piece.second, true) << endl;
	}
	file << "\tKing: " << whiteKingPoints << endl;

	file << "BLACK: " << blackBishopPoints + blackKingPoints + blackKnightPoints + blackPawnPoints + blackQueenPoints + blackRookPoints << endl;
	file << "\tPawns: " << blackPawnPoints << endl;
	for (auto piece : b1blackPawns)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluatePawn(board, piece.first, piece.second, false) << endl;
	}
	file << "\tRooks: " << blackRookPoints << endl;
	for (auto piece : b1blackRooks)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateRook(board, piece.first, piece.second, false) << endl;
	}
	file << "\tKnights: " << blackKnightPoints << endl;
	for (auto piece : b1blackKnights)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateKnight(board, piece.first, piece.second, false) << endl;
	}
	file << "\tBishops: " << blackBishopPoints << endl;
	for (auto piece : b1blackBishops)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateBishop(board, piece.first, piece.second, false) << endl;
	}
	file << "\tQueens: " << blackQueenPoints << endl;
	for (auto piece : b1blackQueens)
	{
		file << "\t\t[" << char(piece.first + 65) << "; " << 8 - piece.second << "]: " << evaluateQueen(board, piece.first, piece.second, false) << endl;
	}
	file << "\tKing: " << blackKingPoints << endl << endl;
}