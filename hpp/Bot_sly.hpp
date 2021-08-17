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
                                        , virtualMap(map) { };
        virtual ~Bot_sly() { };
        
    protected:
        virtual const Connection& getSelectionForMrx(const Connections& options) override;
        virtual const Connection& getSelectionForSly(const Connections& options) override;
        virtual Ticket getTicketForMrx(ConnectionType usedTransportation) override;

    private:
        const VirtualMap& virtualMap; 
        
        const Connection& getMinDistanceToMrxCon(const Connections& options);
        const Connection& randomGetSelectionForSly(const Connections& options);
    };
} // namespace tlk
