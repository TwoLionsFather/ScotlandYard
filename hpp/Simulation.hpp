#pragma once

#include "Game.hpp"
#include "Consts.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
        Simulation();
        ~Simulation();

        /**
         * @brief Starts simulation process
         * 
         */
        void start();

    private:
        std::vector<int> startingLocations;
        void setNextStartOrder(std::vector<std::array<int, 5>>& file);
    };
    
} // namespace tlk
