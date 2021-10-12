#include "../hpp/Simulation.hpp"


void tlk::Simulation::start()
{
    tlk::Map map = tlk::Map(tlk::ASSETPATH + "/connections.txt");

    std::cout << tlk::GAME_COUNT << " Games calculating!" << std::endl;

    int results[3] = {0, 0, 0};
    std::array<int, 22> length;
    length.fill(0);
    srand(time(NULL));

    auto begin = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < tlk::GAME_COUNT; i++)
    {
        tlk::Game g(&map);
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

    std::ofstream resultFile(tlk::ASSETPATH + "/simresults.txt",  std::ofstream::out | std::ios::app);

    resultFile << tlk::GAME_COUNT << " Games calculated!" << std::endl;
    resultFile << "Siege SLY: " << results[0] << " MRX: " << results[1] << " ERRORS: " << results[2] << std::endl; 

    double avg = 0;
    for (int i = 0; i < 22; ++i)
    {
        resultFile << "[" <<  i+1 << " " << length[i] << "] ";
        avg += (double) (length[i] * i);
    }
    resultFile << "Avg " << avg/(double) tlk::GAME_COUNT << " Rounds" << std::endl;

    std::chrono::duration<double, std::milli> elapsed = finish - begin;
    resultFile << "Calculations took: " << elapsed.count() << "ms" << std::endl << std::endl;

    resultFile.close();
}
