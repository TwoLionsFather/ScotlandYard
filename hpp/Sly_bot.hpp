#pragma once

#include "Entity.hpp"

namespace tlk
{
    class Sly_bot : public Entity
    {
    public:
        Sly_bot() : Entity(Team::SLY) { };
        virtual ~Sly_bot() { };

    protected:
        virtual const Connection& getSelectionForMrx(const Connections& options) override;
        virtual const Connection& getSelectionForSly(const Connections& options) override;
        virtual Ticket getTicketForMrx(ConnectionType usedTransportation) override;
    };
} // namespace tlk
