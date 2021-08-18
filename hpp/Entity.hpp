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
    protected:
        virtual double scoreCon(const Connection& c) { return ((double) random())/rand(); }
        virtual const Connection& getSelection(const Connections& options) { return getBestSelection(options); }

        virtual Ticket getTicket(ConnectionType usedTransportation) { return TicketStack::getTicketFor(usedTransportation); }

    public:
        Entity(): team(tlk::SLY), tickets(TicketStack(tlk::SLY)) { };
        Entity(Team t): team(t), tickets(TicketStack(t)) { };
        virtual ~Entity() { };

        std::pair<const tlk::Connection*, tlk::Ticket> move(const Connections& options)
        {
            const Connection& selected = getSelection(options);
            Ticket used = getTicket(selected.type);
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
        TicketStack tickets;

    private:
        const Team team = SLY;

        const Connection& getBestSelection(const Connections& options)
        {
            const Connection* best = &options[0];
            double bestScore = scoreCon(*best);

            for (const Connection& con : options)
            {
                uint score = scoreCon(con);
                if (bestScore < score)
                {
                    best = &con;
                    bestScore = score;
                }
            }

            return *best;
        }
    };
}