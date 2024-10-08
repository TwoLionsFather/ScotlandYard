#pragma once

#include "Entity.hpp"
#include "Connection.hpp"
#include "PlayerInput.hpp"

#include <iostream>
#include <string>

namespace tlk
{
    class [[maybe_unused]] Player_mrx : public Entity
    {
    public:
        Player_mrx();
        ~Player_mrx() override;

    protected:
        virtual const Connection& getSelection(const Connections& options) override;

        virtual Ticket getTicket(ConnectionType usedTransportation) override;
    };
}