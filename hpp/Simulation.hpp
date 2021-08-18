#pragma once

#include "../hpp/Game.hpp"
#include "../hpp/ConstsAndEnums.hpp"

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
