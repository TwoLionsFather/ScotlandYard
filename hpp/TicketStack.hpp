#pragma once

#include "Connection.hpp"
#include "RandomEnums.hpp"

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
                counts[0] = 10;
                counts[1] = 8;
                counts[2] = 4;
            }
            else
            {
                counts[0] = 4;
                counts[1] = 3;
                counts[2] = 3;
                counts[3] = 2;
                counts[4] = 3;
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

        bool isAdvancedTicketAvailable()
        {
            return counts[3] || counts[4];
        }
        
        int ticketCount(Ticket type)
        {
            return counts[type];
        }

        static Ticket getTicketFor(ConnectionType t)
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

std::ostream& operator<<(std::ostream& out, const tlk::Ticket& ticket);