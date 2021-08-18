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
        Bot_sly(const VirtualMap& map) : Entity(Team::SLY)
                                        , vMap(map) { };
        virtual ~Bot_sly() { };
        
    protected:
        virtual double scoreCon(const Connection& c) 
        {
            return -vMap.getDistanceToMrxReport(c.target);
        };

    private:
        const VirtualMap& vMap; 
        
        const Connection& minDist(const Connections& options);
        const Connection& random(const Connections& options);
    };
} // namespace tlk
