#pragma once

#include <vector>
#include <iostream>

namespace tlk 
{
    enum ConnectionType
    {
        TAXI,
        BUS,
        UNDERGROUND,
        BOAT,
        UNDEFINED
    };

    struct Connection
    {
        Connection(const unsigned int target, const ConnectionType type): 
            target(target), type(type) {  };  

        const unsigned int    target = 0;  
        const ConnectionType            type = ConnectionType::UNDEFINED;
    };
    typedef std::vector<Connection> Connections;
}

std::ostream& operator<<(std::ostream &out, const tlk::ConnectionType& rhs);
std::ostream& operator<<(std::ostream &out, const tlk::Connection& rhs);
std::ostream& operator<<(std::ostream &out, const tlk::Connections& rhs);
