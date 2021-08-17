#pragma once

#include "TicketStack.hpp"
#include "Connection.hpp"
#include "ConstsAndEnums.hpp"

namespace tlk
{
    //Per Default a SLY Entity is described 
    //To set a MRX entity set the Team to MRX
    class Entity
    {
    public:
        Entity(): team(tlk::SLY), tickets(TicketStack(tlk::SLY)) { };
        Entity(Team t): team(t), tickets(TicketStack(t)) { };
        virtual ~Entity() { };

        std::pair<const tlk::Connection*, tlk::Ticket> move(const Connections& options)
        {
            const Connection& selected = (isMrx())? getSelectionForMrx(options) : getSelectionForSly(options);
            Ticket used = (isMrx())? getTicketForMrx(selected.type) : TicketStack::getTicketFor(selected.type);
            
            tickets.useTicket(used);

            return std::make_pair(&selected, used);
        }

        //If is Mrx tickets get added
        void addTicket(const tlk::Ticket& type)
        {
            if (isMrx())
                tickets.addTicket(type);
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
        // int round = 0;
        TicketStack tickets;
    };
}