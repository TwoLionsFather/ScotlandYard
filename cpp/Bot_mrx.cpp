#include "../hpp/Bot_mrx.hpp"

const tlk::Connection& tlk::Bot_mrx::getSelectionForMrx(const Connections& options) 
{
    return *options.begin();
}

const tlk::Connection& tlk::Bot_mrx::getSelectionForSly(const Connections& options) 
{
    throw std::runtime_error("getSelectionForSly is not to be called for mrx units!");
}

tlk::Ticket tlk::Bot_mrx::getTicketForMrx(tlk::ConnectionType usedTransportation)
{
    return TicketStack::getTicketFor(usedTransportation);
}