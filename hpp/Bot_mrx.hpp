#pragma once

#include "Entity.hpp"
#include "VirtualMap.hpp"
#include <random>
#include <chrono>

namespace tlk
{
    class Bot_mrx : public Entity
    {
    public:
        Bot_mrx(const VirtualMap& vMap) 
            : Entity(Team::MRX), vMap(vMap) { };
        virtual ~Bot_mrx() { };

    protected:
        virtual const Connection& getSelectionForMrx(const Connections& options) override;
        virtual const Connection& getSelectionForSly(const Connections& options) override;
        virtual Ticket getTicketForMrx(ConnectionType usedTransportation) override;

    private:
        const VirtualMap& vMap; 

        const tlk::Connection& random(const Connections& options);
        const tlk::Connection& maxDistToSLY(const Connections& options);
        tlk::Ticket randomGetTicketForMrx(tlk::ConnectionType usedTransportation);
    };
} // namespace tlk
