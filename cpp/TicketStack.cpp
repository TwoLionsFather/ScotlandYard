#include "../hpp/TicketStack.hpp"

std::ostream& operator<<(std::ostream& out, const tlk::Ticket& ticket)
{
    switch (ticket)
    {
    case tlk::TAXI_Ti: out << "Taxi ticket"; break;
    case tlk::BUS_Ti: out << "Bus ticket"; break;
    case tlk::UNDERGROUND_Ti: out << "Undederground ticket"; break;
    case tlk::DOUBLE_Ti: out << "Double ticket"; break;
    case tlk::BLACK_Ti: out << "Black ticket"; break;
    
    default:
        break;
    }
    return out;
}