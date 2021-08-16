#include "../hpp/Bot_mrx.hpp"

const tlk::Connection& tlk::Bot_mrx::getSelectionForMrx(const Connections& options) 
{
    auto rng = std::default_random_engine(std::time(NULL));
    return options[rng() % options.size()];
}

const tlk::Connection& tlk::Bot_mrx::getSelectionForSly(const Connections& options) 
{
    throw std::runtime_error("getSelectionForSly is not to be called for mrx units!");
}

tlk::Ticket tlk::Bot_mrx::getTicketForMrx(tlk::ConnectionType usedTransportation)
{
   Ticket used = TicketStack::getTicketFor(usedTransportation);

    if (!tickets.isAdvancedTicketAvailable())
        return used;
    
    if (tickets.ticketCount(used) == 0 
    && tickets.ticketCount(BLACK_Ti) > 0)
        return BLACK_Ti;
    

    auto rng = std::default_random_engine(std::time(NULL));
    uint rand = rng();

    if (tickets.ticketCount(BLACK_Ti) > 0
    && rand % 100 < 10)
        return BLACK_Ti;
    
    if (tickets.ticketCount(DOUBLE_Ti) > 0
    && rand % 100 < 10)
        return DOUBLE_Ti;
    
    return used;
}