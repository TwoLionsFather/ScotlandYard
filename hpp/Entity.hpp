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

        std::pair<const tlk::Connection*, tlk::Ticket> move(const Connections& options);

        //call this once to select where the entity starts on the map
        void setStartingPos(unsigned int start)
        {
            if (pos != 0)
                throw std::runtime_error("Can't set starting position after Game has started, failed setting startingPos of Entity!");
            
            pos = start;
        }

        //If is Mrx tickets get added
        void addTicket(const tlk::Ticket& type)
        {
            if (isMrx())
                tickets.addTicket(type);
        }

        unsigned int getPos() const
        { 
            return pos;
        }

        bool isMrx() const
        {
            return team == tlk::MRX;
        }

        bool isAllowedToUse(ConnectionType type) const
        {   
            return tickets.isAllowedToUse(type);
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