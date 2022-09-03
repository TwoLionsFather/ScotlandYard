#pragma once

#include "Game.hpp"
#include "Consts.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <array>


namespace tlk
{
    /**
     * @brief Simulation of games only using ai and console. Gui will not be displayed
     * 
     */
    class Simulation
    {
    public:
        Simulation() { };
        ~Simulation() { };

        /**
         * @brief Starts simulation process
         * 
         */
        void start();
    };
    
} // namespace tlk
