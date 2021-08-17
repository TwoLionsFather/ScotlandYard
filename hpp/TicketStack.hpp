#pragma once

#include "Connection.hpp"
#include "ConstsAndEnums.hpp"

namespace tlk
{
    class TicketStack
    {
    public:
        TicketStack() = delete;
        TicketStack(Team t):
            counts{0, 0, 0, 0, 0}
        {
            //TODO make better:
            if (t == tlk::SLY)
            {
                counts[TAXI_Ti] = 10;
                counts[BUS_Ti] = 8;
                counts[UNDERGROUND_Ti] = 4;
            }
            else
            {
                counts[TAXI_Ti] = 4;
                counts[BUS_Ti] = 3;
                counts[UNDERGROUND_Ti] = 3;
                counts[DOUBLE_Ti] = 2;
                counts[BLACK_Ti] = 3;
            }
        };

        void useTicket(tlk::Ticket typeUsed)
        {
            counts[typeUsed]--;
        };
        
        void addTicket(tlk::Ticket typeAdded)
        {
            counts[typeAdded]++;
        };

        bool isAllowedToUse(ConnectionType t) const
        {// either correct ticket type available or use Black Ticket.
            return (counts[getTicketFor(t)] > 0) 
                || (counts[BLACK_Ti] > 0);
        }

        bool isAdvancedTicketAvailable() const
        {
            return counts[DOUBLE_Ti] || counts[BLACK_Ti];
        }
        
        int ticketCount(Ticket type) const
        {
            return counts[type];
        }

        static bool isAllowedConnection(const Ticket& tick, const ConnectionType& type)
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
        int counts[5];
    }; 
}

std::ostream& operator<<(std::ostream& out, const tlk::Ticket& rhs);
std::ostream& operator<<(std::ostream& out, const tlk::TicketStack& rhs);