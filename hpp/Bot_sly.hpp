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
        virtual const Connection& getSelectionForMrx(const Connections& options) override;
        virtual const Connection& getSelectionForSly(const Connections& options) override;
        virtual Ticket getTicketForMrx(ConnectionType usedTransportation) override;

    private:
        const VirtualMap& vMap; 
        
        const Connection& minDist(const Connections& options);
        const Connection& random(const Connections& options);
    };
} // namespace tlk
