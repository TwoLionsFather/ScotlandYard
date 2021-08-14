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
            return (counts[TicketStack::getTicketFor(t)] > 0) 
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
        // int convertTypeToIDX(Ticket t) const
        // {
        //     switch (t)
        //     {
        //     case TAXI_Ti:           return 0;
        //     case BUS_Ti:            return 1;
        //     case UNDERGROUND_Ti:    return 2;
        //     case BLACK_Ti:          return 3;
        //     case DOUBLE_Ti:         return 4;    
            
        //     default:
        //         throw std::runtime_error("Unknown Connection Type used, can't dereference Ticket!");
        //     }  
        // }
        int counts[5];
    }; 
}

std::ostream& operator<<(std::ostream& out, const tlk::Ticket& ticket);