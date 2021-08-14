#include "../hpp/Sly_bot.hpp"

const tlk::Connection& tlk::Sly_bot::getSelectionForMrx(const Connections& options) 
{
    throw std::runtime_error("getSelectionForMrx is not to be called for sly units!");
}

const tlk::Connection& tlk::Sly_bot::getSelectionForSly(const Connections& options) 
{
    return *options.begin();
}

tlk::Ticket tlk::Sly_bot::getTicketForMrx(tlk::ConnectionType usedTransportation)
{
    throw std::runtime_error("getTicketForMrx is not to be called on sly unit!");
}