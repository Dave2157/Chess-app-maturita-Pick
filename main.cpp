#define OLC_PGE_APPLICATION
#include <iostream>
#include <utility>
#include <vector>
#include <sstream>
#include "olcPixelGameEngine.h"
#include "GameEngine.h"
#include <ctime>
#include "Logs.h"
#include "Minimax.h"
#include <iostream>
#include "Functions.h"
using std::pair;
using std::vector;
using std::stringstream;

using namespace olc;

int main()
{

    GameEngine engine;
    if (engine.Construct(128, 128, 4, 4))
        engine.Start();
    
    //logASinglePositionEvaluationIntoAFile("r6K/1r6/8/8/8/8/8/7k w KQkq - 0 0", "Logs.txt");

    /*Board b;
    b.setBoardFEN("r6K/1r6/r7/8/8/8/8/7k b KQkq - 0 0");
    std::cout << checkForCheckmate(b, true);*/

    //Minimax(b, 0, 1, false);

    /*Board b;
    b.setBoardFEN("rnbqk1nr/pppp1ppp/8/3Pp3/1b6/8/PPP5/RNBQKBNR w KQkq - 0 0");
    std::cout << checkForCheckmate(b, true);*/

}