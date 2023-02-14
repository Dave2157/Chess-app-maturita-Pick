#define OLC_PGE_APPLICATION
#include <iostream>
#include <utility>
#include <vector>
#include <sstream>
#include "olcPixelGameEngine.h"
#include "GameEngine.h"
#include <ctime>
#include <cstdlib>
#include "Logs.h"

using std::pair;
using std::vector;
using std::stringstream;

using namespace olc;

int main()
{
    std::srand(std::time(0));
    GameEngine engine;
    if (engine.Construct(128, 128, 4, 4))
        engine.Start();

    //logASinglePositionEvaluationIntoAFile("r6K/1r6/8/8/8/8/8/7k w KQkq - 0 0", "Logs.txt");
    
}