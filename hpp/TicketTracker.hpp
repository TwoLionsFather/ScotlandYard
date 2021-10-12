#pragma once

#include "Entity.hpp"
#include "TicketStack.hpp"

#include <map>

//TODO give easy access to ticketStack to create Debug functionality

namespace tlk
{
    class TicketTracker
    {
    public:
        TicketTracker();
        ~TicketTracker();

        void createEntry(Entity* e);
        void setEntry(Entity* e, const TicketStack& ts);

        const TicketStack& getEntry(Entity* e);

    private:
        std::map<Entity*, TicketStack> ticketMap;
    };
} // namespace ttlk


