#pragma once

#include "Consts.hpp"
#include "GameDefinitions.hpp"

#include <vector>
#include <iostream>

namespace tlk 
{
    //TODO Make const again
    struct Connection
    {
        /**
         * @brief Construct a new Connection object without defining any porperty
         * 
         */
        Connection () 
            : source(0), target(0), type(UNDEFINED) {  };

        /**
         * @brief deprecated constructs a Connection only defining a target node. 
         * This could be considered a directional connection, as it doesn't know its source
         * 
         * @param target Target of connection 
         * @param type  Type of connection
         */
        Connection (const int target, const ConnectionType type)
            : source(0), target(target), type(type) {  };  

        /**
         * @brief Construct a new Connection object Defines a bidirectional Connection
         * 
         * @param source Source of connection
         * @param target Target of connection
         * @param type Type of connection
         */
        Connection (const int source, const int target, const ConnectionType type)
            : source(source), target(target), type(type) {  };  

        //TODO turn into final class?
        int source;
        int target;  
        ConnectionType type;

        Connection getReverse() const
        {
            return Connection(target, source, type);
        };

        static ConnectionType get_type_from_char(char type);
    };
    typedef std::vector<Connection> Connections; //TODO Make Const
}

std::ostream& operator<<(std::ostream &out, const tlk::Connection& rhs);
std::ostream& operator<<(std::ostream &out, const tlk::Connections& rhs);
std::ostream& operator<<(std::ostream &out, const tlk::ConnectionType& rhs);
