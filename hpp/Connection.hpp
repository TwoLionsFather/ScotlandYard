#pragma once

#include "Consts.hpp"
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

    //TODO Make const again
    struct Connection
    {
        Connection () 
            : target(0), type(UNDEFINED) {  };
        Connection (const int target, const ConnectionType type)
            : target(target), type(type) {  };  

        int target;  
        ConnectionType type;
    };
    typedef std::vector<Connection> Connections; //TODO Make Const
}

std::ostream& operator<<(std::ostream &out, const tlk::Connection& rhs);
std::ostream& operator<<(std::ostream &out, const tlk::Connections& rhs);
std::ostream& operator<<(std::ostream &out, const tlk::ConnectionType& rhs);
