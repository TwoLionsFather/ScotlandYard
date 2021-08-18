#pragma once

#include "Entity.hpp"
#include "VirtualMap.hpp"
#include <random>
#include <chrono>

namespace tlk
{
    class Bot_sly : public Entity
    {
    public:
        Bot_sly(const VirtualMap& map, const int* round, std::vector<int>* startingOptions) 
            : Entity(Team::SLY), vMap(map), round(round), startingOptions(startingOptions) { };
        virtual ~Bot_sly() { };
        
    protected:
        virtual double scoreCon(const Connection& c) 
        {
            if (*round < 3)
                return minDistStart(c);
            return minDist(c);
        }

    private:
        const VirtualMap& vMap; 
        const int* round = 0;
        std::vector<int>* startingOptions;
        
        double minDistStart(const Connection& options);
        double minDist(const Connection& options);
        double minOptions(const Connection& options);
    };
} // namespace tlk
