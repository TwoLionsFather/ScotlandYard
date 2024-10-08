#include "../hpp/TicketStack.hpp"

std::ostream& operator<<(std::ostream& out, const tlk::Ticket& rhs)
{
    switch (rhs)
    {
    case tlk::TAXI_Ti:      out << "Taxi ticket"; break;
    case tlk::BUS_Ti:       out << "Bus ticket"; break;
    case tlk::UNDERGROUND_Ti: out << "Undederground ticket"; break;
    case tlk::DOUBLE_Ti:    out << "Double ticket"; break;
    case tlk::BLACK_Ti:     out << "Black ticket"; break;
    
    default:
        break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const tlk::TicketStack& rhs)
{
    out << "[T, B, U, Double, Black]" << std::endl << "[";
    out << rhs.ticketCount(tlk::TAXI_Ti)        << ", " ; 
    out << rhs.ticketCount(tlk::BUS_Ti)         << ", " ; 
    out << rhs.ticketCount(tlk::UNDERGROUND_Ti) << ", " ; 
    out << rhs.ticketCount(tlk::DOUBLE_Ti)      << "     , " ; 
    out << rhs.ticketCount(tlk::BLACK_Ti)       << "]\n" ; 
    return out;
}

tlk::TicketStack::TicketStack()
        : counts{0, 0, 0, 0, 0} {

}

tlk::TicketStack::TicketStack(const std::array<int, 5> &counts)
        : counts(counts) {

}

tlk::TicketStack::TicketStack(bool isMrxTickets)
        : counts((isMrxTickets)? STARTING_TICKETS_MRX:STARTING_TICKETS_SLY)
{
    // std::cout << "Test if working as intendet" << std::endl;
    // for (int tCount : counts)
    //     std::cout << "[" << tCount << "]" << " ";
    // std::cout << std::endl;
}

void tlk::TicketStack::useTicket(tlk::Ticket typeUsed)
{
    if (typeUsed == tlk::NO_TICKET)
        std::cout << "TicketStack::useTicket Type NO_TICKET can't be used for transport! " << std::endl;

    counts[typeUsed]--;

    if (counts[typeUsed] < 0)
        throw std::runtime_error("TicketStack::useTicket Ticket count is not allowed to be < 0");
}

void tlk::TicketStack::addTicket(tlk::Ticket typeAdded)
{
    counts[typeAdded]++;
}

bool tlk::TicketStack::hasTicketFor(tlk::ConnectionType t) const
{
    // either correct ticket type available or use Black Ticket.
    return (counts[getTicketFor(t)] > 0)
           || (counts[BLACK_Ti] > 0)
           || (counts[DOUBLE_Ti] > 0 && t != BOAT);
}

bool tlk::TicketStack::isAdvancedTicketAvailable() const
{
    return counts[DOUBLE_Ti] || counts[BLACK_Ti];
}

int tlk::TicketStack::ticketCount(tlk::Ticket type) const
{
    return counts[type];
}

bool tlk::TicketStack::validTicketForType(const tlk::Ticket &tick, const tlk::ConnectionType &type)
{
    return ((tick == BLACK_Ti)
            || (tick == DOUBLE_Ti && type != BOAT)
            || (tick == getTicketFor(type)));
}

tlk::Ticket tlk::TicketStack::getTicketFor(const tlk::ConnectionType &t)
{
    switch (t)
    {
        case TAXI:          return TAXI_Ti;
        case BUS:           return BUS_Ti;
        case UNDERGROUND:   return UNDERGROUND_Ti;
        case BOAT:          return BLACK_Ti;

        default:
            throw std::runtime_error("Unknown Connection Type used, can't dereference Ticket!");
    }
}
