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
    static const int PLAYER_COUNT = 3;
    static const bool PLAYER_PLAYING = false;
    static const int GAME_COUNT = 100;//std::pow(10, (3-LOG_LEVEL));static const 
	static const std::string ASSETPATH = "/home/tlk/Documents/Code/VSCode/ScotlandYard/assets/";
} // namespace tlk


