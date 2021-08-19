#pragma once
#include <math.h>
#include <string>
#include <map>

namespace tlk
{
    enum ConnectionType
    {
        TAXI,
        BUS,
        UNDERGROUND,
        BOAT,
        UNDEFINED
    }; 

    enum Ticket
    {
        TAXI_Ti,
        BUS_Ti,
        UNDERGROUND_Ti,
        DOUBLE_Ti,
        BLACK_Ti
    };

    enum State {
        WON_MRX
        , WON_SLY
        , PLAYING
        , ERROR
    };

    enum Debug {
        NONE
        , LOW
        , NORMAL
        , HIGH
    };

    enum Team
    {
        SLY,
        MRX
    };

    static const Debug LOG_LEVEL = LOW;
    static const Debug CHRONO_LOG_LEVEL = HIGH;
    static const int STARTING_OPTIONS = 18;
    static const int PLAYER_COUNT = 5;
    static const bool PLAYER_PLAYING = false;
    static const bool GRAPHICAL_INTERFACE = false;
    static const int GAME_COUNT = std::min(1000, (int) std::pow(10, (3-LOG_LEVEL))); 
	static const std::string ASSETPATH = "/home/tlk/Documents/Code/VSCode/ScotlandYard/assets/";
    static const std::map<int, int> INITIAL_TARGETS { {103, 53}, {112, 138}, {34, 13}, {155, 197}, {94, 78}, {117, 91}, {132, 141}, {53, 103}, {174, 198}
                                                    , {198, 174}, {50, 13}, {91, 117}, {26, 29}, {29, 26}, {141, 132}, {13, 34}, {138, 112}, {197, 155}};
} // namespace tlk


