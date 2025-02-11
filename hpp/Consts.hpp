#pragma once
#include <math.h>
#include <string>
#include <map>
#include <array>

namespace tlk
{
    enum DebugLevel {
        NONE = 0
        , LOW = 1
        , NORMAL = 2
        , HIGH = 3
    };

    //TODO Array Out of range... some min method is Virt map might run to far...

    static const DebugLevel LOG_LEVEL = NORMAL;
    static const DebugLevel CHRONO_LOG_LEVEL = NONE;
    static const int PLAYER_COUNT = 5;
    static const bool RUN_TESTS = 0;
    static const bool PLAYER_PLAYING = 0;
    static const bool GRAPHICAL_INTERFACE = 1; //TODO Fix that
    static const int GAME_COUNT = 1; 
    // static const int GAME_COUNT = std::min(10000, (int) std::pow(10, (4-LOG_LEVEL))); 
	static const std::string ASSETPATH = "/home/tlk/Documents/Code/VSCode/ScotlandYard/assets/";

    static const std::array<int, 5> STARTING_TICKETS_MRX = { 4, 3, 3, 2, 3};
    static const std::array<int, 5> STARTING_TICKETS_SLY = {10, 8, 4, 0, 0};

    static const int STARTING_OPTIONS_COUNT = 18;
    static const int STARTING_POSITIONS[] = {13, 26, 29, 34, 50, 53, 91, 94, 103, 112, 117, 132, 138, 141, 155, 174, 197, 198};//{58, 34, 14, 29, 52, 94, 78, 66, 86, 105, 100, 137, 154, 157, 135, 144, 180, 199};
    // static const std::map<int, int> INITIAL_TARGETS { {103, 53}, {112, 138}, {34, 13}, {155, 197}, {94, 78}, {117, 91}, {132, 141}, {53, 103}, {174, 198}
    //                                                 , {198, 174}, {50, 13}, {91, 117}, {26, 29}, {29, 26}, {141, 132}, {13, 34}, {138, 112}, {197, 155}};
} // namespace tlk


