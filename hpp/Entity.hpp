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
        
        virtual double scoreCon(const Connection& c) 
        { 
            std::cout << "Entity::scoreCon: scoring " << c << " with random score" << std::endl;
            return ((double) random())/rand(); 
        }
        virtual const Connection& getSelection(const Connections& options) { return getHighestScoring(options); }

        virtual Ticket getTicket(ConnectionType usedTransportation) { return TicketStack::getTicketFor(usedTransportation); }

    public:
        Entity(): team(tlk::SLY), tickets(TicketStack(false)) { };
        Entity(Team t): team(t), tickets(TicketStack(t == tlk::MRX)) { };
        
        Entity(Team t, TicketStack tickets): team(t), tickets(tickets) { };
        virtual ~Entity() { };

        const tlk::Move move(const Connections& options)
        {
            tlk::Move pair(getSelection(options), tlk::NO_TICKET);

            pair.second = getTicket(pair.first.type);
            tickets.useTicket(pair.second);
            return pair;
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

        bool hasTicketFor(ConnectionType type) const
        {   
            return tickets.hasTicketFor(type);
        }

    private:
        const Team team = SLY;

        const Connection& getHighestScoring(const Connections& options)
        {
            const Connection* best = &options[0];
            double highScore = scoreCon(*best);

            for (const Connection& con : options)
            {
                double score = scoreCon(con);
                if (highScore < score)
                {
                    best = &con;
                    highScore = score;
                }
            }

            return *best;
        }
    };
}