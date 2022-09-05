#pragma once

#include <vector>

namespace tlk
{
    enum Ticket
    {
        TAXI_Ti = 0,
        BUS_Ti = 1,
        UNDERGROUND_Ti = 2,
        DOUBLE_Ti = 3,
        BLACK_Ti = 4,
        NO_TICKET = 5
    };

    enum ConnectionType
    {
        TAXI,
        BUS,
        UNDERGROUND,
        BOAT,
        UNDEFINED
    }; 

    class Connection;
    typedef std::pair<const tlk::Connection, tlk::Ticket> Move;
    typedef std::vector<Move> Moves;

} // namespace tlk


