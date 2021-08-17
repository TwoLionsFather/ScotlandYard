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
        Bot_mrx(const VirtualMap& virtualMap) 
            : Entity(Team::MRX), virtualMap(virtualMap) { };
        virtual ~Bot_mrx() { };

    protected:
        virtual const Connection& getSelectionForMrx(const Connections& options) override;
        virtual const Connection& getSelectionForSly(const Connections& options) override;
        virtual Ticket getTicketForMrx(ConnectionType usedTransportation) override;

    private:
        const VirtualMap& virtualMap; 

        const tlk::Connection& randomGetSelectionForMrx(const Connections& options);
        tlk::Ticket randomGetTicketForMrx(tlk::ConnectionType usedTransportation);
    };
} // namespace tlk
