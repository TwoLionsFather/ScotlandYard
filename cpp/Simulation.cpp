#include "../hpp/Simulation.hpp"


void tlk::Simulation::start()
{
    const tlk::Map& map = tlk::DistanceMap(tlk::ASSETPATH + "/connections.txt");
    std::vector<std::array<int, 5>> startingLog;

    std::cout << tlk::GAME_COUNT << " Games calculating!" << std::endl;

    int results[3] = {0, 0, 0};
    std::array<int, 22> length;
    length.fill(0);
    srand(time(NULL));

    auto begin = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < tlk::GAME_COUNT; i++)
    {
        tlk::Game g(&map);
        setNextStartOrder(startingLog);
        g.setup(startingLocations);
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

    std::ofstream starts(tlk::ASSETPATH + "/starts.txt",  std::ofstream::out);
    for (const std::array<int, 5> locs : startingLog)
    {
        for (const int sl : locs)
            starts << sl << " ";
        starts << std::endl;
    }
    starts.close();
}

/**
 * @brief TODO Make this logic work for comparing if starting set is valid difference or not
 * 
 * @param veca vec a is new starting vector set
 * @param vecb vec b is old starting order
 * @return true if vec a is a different starting order
 * @return false if vec a is essentially the same starting order
 */
bool compareStartingLocations(std::vector<int> veca, std::vector<int> vecb)
{
    std::vector<int> intersection;
    const std::set<int> s1(std::begin(veca) +1, std::begin(veca) +tlk::PLAYER_COUNT);
    const std::set<int> s2(std::begin(vecb) +1, std::begin(vecb) +tlk::PLAYER_COUNT);
    std::set_intersection(std::begin(s1), std::end(s1)
                        , std::begin(s2), std::end(s2)
                        , std::back_inserter(intersection));


    return (intersection.size() != tlk::PLAYER_COUNT -1);
    // if (intersection.size() == tlk::PLAYER_COUNT -1)
    // {
    //     return false;
    // }

    // const int compMrx = veca[0] - vecb[0];
    // if (compMrx < 0)
    //     return true;
    // else if (compMrx > 0)
    //     return false; 
    
    // //compare order of following 
    // auto ita = std::cbegin(veca) +tlk::PLAYER_COUNT;
    // auto itb = std::cbegin(vecb) +tlk::PLAYER_COUNT;
    
    // while (ita != std::cend(veca) && itb != std::cend(vecb))
    // {
    //     const int comp = *ita - *itb;
    //     if (comp < 0)
    //         return true;
    //     else if (comp > 0)
    //         return false; 

    //     ++ita;
    //     ++itb;
    // }

    // return itb != std::cend(vecb);
}


/**
 * @brief Crate a unique starting order that deviates from the last
 * current implementation has one duplicate among 500 games 
 * for 10k games 128 games appear twice
 */
void tlk::Simulation::setNextStartOrder(std::vector<std::array<int, 5>>& log)
{
    // const std::vector<int> old = startingLocations;
    //TODO optional: This can be set to notify when end of permutations is reached
    for (int i = 0; i < 2; ++i)
    {
        const bool others = std::next_permutation(std::begin(startingLocations), std::end(startingLocations));
        if (!others)
            std::cout << "Simulation::setNextStartOrder: Permutations done!! \n";
    }
    std::swap(startingLocations[0], startingLocations[tlk::STARTING_OPTIONS_COUNT -2]);
    std::reverse(std::begin(startingLocations), std::end(startingLocations));

    std::array<int, 5> startingLocs;
    for (int i = 0; i < tlk::PLAYER_COUNT; ++i)
        startingLocs[i] = startingLocations[i];
    log.push_back(startingLocs);
}

tlk::Simulation::Simulation()
{
    startingLocations.insert(std::begin(startingLocations)
            , tlk::STARTING_POSITIONS
            , tlk::STARTING_POSITIONS + tlk::STARTING_OPTIONS_COUNT);
}

tlk::Simulation::~Simulation() {

}
