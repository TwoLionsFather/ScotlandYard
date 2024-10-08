#pragma once

#include "TicketStack.hpp"
#include "Connection.hpp"
#include "Consts.hpp"

namespace tlk
{
    enum Team
    {
        SLY,
        MRX
    };

    //Per Default a SLY Entity is described 
    //To set a MRX entity set the Team to MRX
    class Entity
    {
    protected:
        TicketStack tickets;
        
        virtual double scoreCon(const Connection& c);
        virtual const Connection& getSelection(const Connections& options);

        virtual Ticket getTicket(ConnectionType usedTransportation);

    public:
        Entity();
        explicit Entity(Team t);
        
        Entity(Team t, TicketStack tickets);
        virtual ~Entity();

        const tlk::Move move(const Connections& options);

        //If is Mrx tickets get added
        void addTicket(const tlk::Ticket& type);

        bool isMrx() const;

        bool hasTicketFor(ConnectionType type) const;

    private:
        const Team team = SLY;

        const Connection& getHighestScoring(const Connections& options);

    };


}