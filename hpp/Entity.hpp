#pragma once

#include "TicketStack.hpp"
#include "Connection.hpp"
#include "RandomEnums.hpp"

namespace tlk
{
    //Per Default a SLY Entity is described 
    //To set a MRX entity set the Team to MRX
    class Entity
    {
    public:
        Entity(): team(tlk::SLY), pos(0), tickets(TicketStack(tlk::SLY)) { };
        Entity(Team t): team(t), pos(0), tickets(TicketStack(t)) { };
        virtual ~Entity() { };

        std::pair<Connection, Ticket> move(const Connections& options);

        //call this once to select where the entity starts on the map
        void setStartingPos(unsigned int start)
        {
            if (pos != 0)
                throw std::runtime_error("Can't set starting position after Game has started, failed setting startingPos of Entity!");
            
            pos = start;
        }

        unsigned int getPos() const
        { 
            return pos;
        };

        bool isAllowedToUse(ConnectionType type) const
        {           // either correct ticket type available or use Black Ticket. //TODO Fix so black Ticket must be used in that case
            return tickets.getTicketFor(type) > 0 || tickets.getTicketFor(BOAT) > 0;
        }

    protected:
        virtual const Connection& getSelectionForMrx(const Connections& options) = 0;
        virtual const Connection& getSelectionForSly(const Connections& options) = 0;
        virtual Ticket getTicketForMrx(ConnectionType usedTransportation) = 0;

        const Team team = SLY;
        unsigned int pos = 0;    
        TicketStack tickets;
    };
}