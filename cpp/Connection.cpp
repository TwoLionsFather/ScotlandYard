#include "../hpp/Connection.hpp"

std::ostream& operator<<(std::ostream &out, const tlk::ConnectionType& rhs)
{
    switch (rhs)
    {
    case tlk::TAXI:         out << "TAXI"; break;
    case tlk::BUS:          out << "BUS"; break;
    case tlk::UNDERGROUND:  out << "UNDERGROUND"; break;
    case tlk::BOAT:         out << "BOAT"; break;
    case tlk::UNDEFINED:    out << "UNDEFINED"; break;
    
    default:
        break;
    }
    return out;
}

std::ostream& operator<<(std::ostream &out, const tlk::Connection& rhs)
{
    out << "Connection to: " << rhs.target << " via: " << rhs.type;
    return out;
}

std::ostream& operator<<(std::ostream &out, const tlk::Connections& rhs)
{
    for (auto& itr_c : rhs)
            out << itr_c << "\n";

    return out;
}