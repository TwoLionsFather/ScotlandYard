#pragma once

#include "Connection.hpp"
#include "Consts.hpp"

#include <iostream>
#include <array>

namespace tlk
{
    class TicketStack
    {
    public:
        TicketStack();

        explicit TicketStack(const std::array<int, 5>& counts);

        explicit TicketStack(bool isMrxTickets);

        void useTicket(Ticket typeUsed);
        
        void addTicket(Ticket typeAdded);

        bool hasTicketFor(ConnectionType t) const;

        bool isAdvancedTicketAvailable() const;
        
        int ticketCount(Ticket type) const;

        static bool validTicketForType(const Ticket& tick, const ConnectionType& type);

        static Ticket getTicketFor(const ConnectionType& t);

    private:
        std::array<int, 5> counts;
    }; 
}

std::ostream& operator<<(std::ostream& out, const tlk::Ticket& rhs);
std::ostream& operator<<(std::ostream& out, const tlk::TicketStack& rhs);