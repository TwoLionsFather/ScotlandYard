#include "../hpp/Entity.hpp"

std::pair<const tlk::Connection*, tlk::Ticket> tlk::Entity::move(const Connections& options)
{
    const Connection& selected = (isMrx())? getSelectionForMrx(options) : getSelectionForSly(options);
    Ticket used = (isMrx())? getTicketForMrx(selected.type) : TicketStack::getTicketFor(selected.type);
    
    pos = selected.target;
    tickets.useTicket(used);

    return std::make_pair(&selected, used);
}