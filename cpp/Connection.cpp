#include "../hpp/Connection.hpp"

tlk::ConnectionType tlk::Connection::get_type_from_char(char type)
{
    switch (type)
    {
    case 'T': return tlk::TAXI;
    case 'B': return tlk::BUS;
    case 'U': return tlk::UNDERGROUND;
    case 'H': return tlk::BOAT;

    default: return tlk::UNDEFINED;
    }
}

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