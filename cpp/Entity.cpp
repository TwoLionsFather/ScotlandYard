#include "../hpp/Entity.hpp"

std::pair<tlk::Connection, tlk::Ticket> tlk::Entity::move(const Connections& options)
{
    const Connection& selected = (team == tlk::SLY)? getSelectionForSly(options) : getSelectionForMrx(options);
    const Ticket used = (team == tlk::SLY)? TicketStack::getTicketFor(selected.type) : getTicketForMrx(selected.type);
    
    pos = selected.target;
    tickets.useTicket(used);

    return std::make_pair(selected, used);
}