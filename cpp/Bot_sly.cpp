#include "../hpp/Bot_sly.hpp"

const tlk::Connection& tlk::Bot_sly::getSelectionForMrx(const Connections& options) 
{
    throw std::runtime_error("getSelectionForMrx is not to be called for sly units!");
}

const tlk::Connection& tlk::Bot_sly::getSelectionForSly(const Connections& options) 
{
    auto rng = std::default_random_engine(std::time(0));
    return options[rng() % options.size()];
}

tlk::Ticket tlk::Bot_sly::getTicketForMrx(tlk::ConnectionType usedTransportation)
{
    throw std::runtime_error("getTicketForMrx is not to be called on sly unit!");
}