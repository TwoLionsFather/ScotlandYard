#define OLC_PGE_APPLICATION
// #include "../hpp/olcPixelGameEngine.h"
#include "../hpp/Game.hpp"
#include "../hpp/ConstsAndEnums.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <array>

// class Example : public olc::PixelGameEngine
// {
// public:
// 	Example()
// 	{
// 		sAppName = "Example";
// 	}

// public:
// 	bool OnUserCreate() override
// 	{
// 		// Called once at the start, so create things here
// 		return true;
// 	}

// 	bool OnUserUpdate(float fElapsedTime) override
// 	{
// 		// called once per frame
// 		for (int x = 0; x < ScreenWidth(); x++)
// 			for (int y = 0; y < ScreenHeight(); y++)
// 				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));	
// 		return true;
// 	}
// };

int main(int argc, char const *argv[])
{
    // Example demo;
	// if (demo.Construct(256, 240, 4, 4))
	// 	demo.Start();

	// return 0;

    const int gameCount = tlk::GAME_COUNT;
    std::ofstream resultFile("/home/tlk/Documents/Code/VSCode/ScotlandYard/assets/simresults.txt", std::ios::app);

    resultFile << gameCount << " Games calculating!" << std::endl;

    int results[3] = {0, 0, 0};
    std::array<int, 22> length;
    length.fill(0);
    srand(time(NULL));

    auto begin = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < gameCount; i++)
    {
        tlk::Game g;
        g.setup();
        tlk::Statistics stats = g.play();

        length[stats.finalRound-1]++;
        switch (stats.endState)
        {
        case tlk::WON_SLY:
            results[0]++;
            break;

        case tlk::WON_MRX:
            results[1]++;
            break;
        
        default:
            results[2]++;
            break;
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();

    resultFile << "Siege SLY: " << results[0] << " MRX: " << results[1] << " ERRORS: " << results[2] << std::endl; 
    double avg = 0;
    for (int i = 0; i < 22; ++i)
    {
        resultFile << "[" <<  i+1 << " " << length[i] << "] ";
        avg += (double) (length[i] * i);
    }
    resultFile << "Avg " << avg/(double) gameCount << " Rounds" << std::endl;

    resultFile.close();

    std::chrono::duration<double, std::milli> elapsed = finish - begin;
    std::cout << "Calculations took: " << elapsed.count() << "ms" << std::endl;

    return 0;
}
