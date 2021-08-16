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