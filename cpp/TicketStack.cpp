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
    for (int ticketID = tlk::TAXI_Ti; ticketID != tlk::BLACK_Ti; ++ticketID)
    {
        tlk::Ticket tmp = static_cast<tlk::Ticket>(ticketID);
        out << rhs.ticketCount(tmp) << " " << tmp << "s available." << std::endl; 
    }
    out << rhs.ticketCount(tlk::BLACK_Ti) << " " << tlk::BLACK_Ti << "s available." << std::endl; 
    return out;
}