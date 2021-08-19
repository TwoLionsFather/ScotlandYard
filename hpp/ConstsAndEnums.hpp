#pragma once
#include <math.h>
#include <string>

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

    static const Debug LOG_LEVEL = NONE;
    static const int STARTING_OPTIONS = 18;
    static const int PLAYER_COUNT = 5;
    static const bool PLAYER_PLAYING = false;
    static const bool GRAPHICAL_INTERFACE = false;
    static const int GAME_COUNT = std::min(1, (int) std::pow(10, (3-LOG_LEVEL))); 
	static const std::string ASSETPATH = "/home/tlk/Documents/Code/VSCode/ScotlandYard/assets/";
} // namespace tlk


