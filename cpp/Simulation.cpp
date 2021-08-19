#include "../hpp/Simulation.hpp"


void tlk::Simulation::start()
{
    tlk::Map map = tlk::Map("../assets/connections.txt");


    std::ofstream resultFile("/home/tlk/Documents/Code/VSCode/ScotlandYard/assets/simresults.txt", std::ios::app);

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

    std::cout << "Siege SLY: " << results[0] << " MRX: " << results[1] << " ERRORS: " << results[2] << std::endl; 
    double avg = 0;
    for (int i = 0; i < 22; ++i)
    {
        std::cout << "[" <<  i+1 << " " << length[i] << "] ";
        avg += (double) (length[i] * i);
    }
    std::cout << "Avg " << avg/(double) tlk::GAME_COUNT << " Rounds" << std::endl;

    resultFile.close();

    std::chrono::duration<double, std::milli> elapsed = finish - begin;
    std::cout << "Calculations took: " << elapsed.count() << "ms" << std::endl;

}
