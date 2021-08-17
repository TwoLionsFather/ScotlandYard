#pragma once

#include "ConstsAndEnums.hpp"
#include <vector>
#include <iostream>

namespace tlk 
{
    //TODO Make const again
    struct Connection
    {
        Connection (const uint target, const ConnectionType type)
            : target(target), type(type) {  };  

        uint target = 0;  
        ConnectionType type = ConnectionType::UNDEFINED;
    };
    typedef std::vector<Connection> Connections; //TODO Make Const
}

std::ostream& operator<<(std::ostream &out, const tlk::Connection& rhs);
std::ostream& operator<<(std::ostream &out, const tlk::Connections& rhs);
std::ostream& operator<<(std::ostream &out, const tlk::ConnectionType& rhs);
