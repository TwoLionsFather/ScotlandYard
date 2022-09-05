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
        Bot_sly(const VirtualMap& map, const int* round_ptr_ptr) 
            : Entity(Team::SLY), vMap(map), round_ptr(round_ptr) { };
        virtual ~Bot_sly() { };
        
    protected:
        virtual double scoreCon(const Connection& c) override;

    private:
        const VirtualMap& vMap; 
        const int* round_ptr;
        
        //give slight edge if more tickets are available
        double ticketFactor(ConnectionType type);

        //Connection with highest score is selected!
        double minDist(const Connection& options);
        double minDistStart(const Connection& options);
        double minOptionsCount(const Connection& options);
    };
} // namespace tlk
