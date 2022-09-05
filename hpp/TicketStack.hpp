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
        TicketStack()
            : counts{0, 0, 0, 0, 0} { };

        TicketStack(const std::array<int, 5>& counts)
            : counts(counts) { };

        TicketStack(bool isMrxTickets)
            : counts((isMrxTickets)? STARTING_TICKETS_MRX:STARTING_TICKETS_SLY) 
            { 
                // std::cout << "Test if working as intendet" << std::endl;
                // for (int tCount : counts)
                //     std::cout << "[" << tCount << "]" << " ";
                // std::cout << std::endl;
            };

        void useTicket(Ticket typeUsed)
        {
            if (typeUsed == tlk::NO_TICKET)
                std::cout << "TicketStack::useTicket Type NO_TICKET can't be used for transport! " << std::endl;

            counts[typeUsed]--;

            if (counts[typeUsed] < 0)
                throw std::runtime_error("TicketStack::useTicket Ticket count is not allowed to be < 0");
        };
        
        void addTicket(Ticket typeAdded)
        {
            counts[typeAdded]++;
        };

        bool hasTicketFor(ConnectionType t) const
        {// either correct ticket type available or use Black Ticket.
            return (counts[getTicketFor(t)] > 0) 
                || (counts[BLACK_Ti] > 0)
                || (counts[DOUBLE_Ti] > 0 && t != BOAT);
        }

        bool isAdvancedTicketAvailable() const
        {
            return counts[DOUBLE_Ti] || counts[BLACK_Ti];
        }
        
        int ticketCount(Ticket type) const
        {
            return counts[type];
        }

        static bool validTicketForType(const Ticket& tick, const ConnectionType& type)
        {
            return ((tick == BLACK_Ti)
                || (tick == DOUBLE_Ti && type != BOAT)
                || (tick == getTicketFor(type)));
        }

        static Ticket getTicketFor(const ConnectionType& t)
        {
            switch (t)
            {
            case TAXI:          return TAXI_Ti;
            case BUS:           return BUS_Ti;
            case UNDERGROUND:   return UNDERGROUND_Ti;
            case BOAT:          return BLACK_Ti;    
            
            default:
                throw std::runtime_error("Unknown Connection Type used, can't dereference Ticket!");
            }
        };

    private:
        std::array<int, 5> counts;
    }; 
}

std::ostream& operator<<(std::ostream& out, const tlk::Ticket& rhs);
std::ostream& operator<<(std::ostream& out, const tlk::TicketStack& rhs);