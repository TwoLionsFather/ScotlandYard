#pragma once

#include "Connection.hpp"
#include "TicketStack.hpp"

namespace tlk::PlayerInput
{
    static const Ticket consoleSelectTicket(const ConnectionType& type, const TicketStack& tickets);

    static const tlk::Connection& consoleSelectMoveFromOptions(const Connections& options, const TicketStack& tickets);
    
} // namespace tlk::PlayerInput
