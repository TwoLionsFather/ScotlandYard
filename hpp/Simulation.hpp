#pragma once

#include "Game.hpp"
#include "Consts.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <array>


namespace tlk
{
    class Simulation
    {
    public:
        Simulation() { };
        ~Simulation() { };

        void start();
    };
    
} // namespace tlk
