#pragma once

#include "Entity.hpp"
#include "Connection.hpp"
#include "PlayerInput.hpp"
#include <iostream>
#include <string>

namespace tlk
{
    class Player_mrx : public Entity
    {
    public:
        Player_mrx() : Entity(Team::MRX) { };
        virtual ~Player_mrx() { };

    protected:
        virtual const Connection& getSelectionForMrx(const Connections& options)
        {
            return tlk::PlayerInput::consoleSelectMoveFromOptions(options, tickets);
        }

        virtual const Connection& getSelectionForSly(const Connections& options)
        {
            throw std::runtime_error("A Player in MRXs Role shouldn't select moves like a Sly unit! wrong Method called for move selection on Player_mrx");;
        }   

        virtual Ticket getTicketForMrx(ConnectionType usedTransportation)
        {
            return tlk::PlayerInput::consoleSelectTicket(usedTransportation, tickets);
        };
    };
}