#pragma once

#include "Consts.hpp"
#include "GameDefinitions.hpp"

#include <vector>
#include <iostream>

namespace tlk 
{
    //TODO Make const again
    class Connection
    {

    public:
        /**
         * @brief Construct a new Connection object without defining any porperty
         * 
         */
        Connection () ;

        /**
         * @brief deprecated constructs a Connection only defining a target node. 
         * This could be considered a directional connection, as it doesn't know its source
         * 
         * @param target Target of connection 
         * @param type  Type of connection
         */
        Connection (const int target, const ConnectionType type);

        /**
         * @brief Construct a new Connection object Defines a bidirectional Connection
         * 
         * @param source Source of connection
         * @param target Target of connection
         * @param type Type of connection
         */
        Connection (const int source, const int target, const ConnectionType type);

        //TODO turn into final class?
        int source;
        int target;  
        ConnectionType type;

        Connection getReverse() const;

        static ConnectionType get_type_from_char(char type);

        bool operator==(const Connection c) const {
            return source == c.source && target == c.target && type == c.type;
        }

    };
    typedef std::vector<Connection> Connections; //TODO Make Const

    class ConnectionHashFunction {
    public:

        // We use predefined hash functions of strings
        // and define our hash function as XOR of the
        // hash values.
        size_t operator()(const Connection& p) const
        {
            return (p.source * 1000 + p.target) << 4 | p.type;
        }
    };
}



std::ostream& operator<<(std::ostream &out, const tlk::Connection& rhs);
std::ostream& operator<<(std::ostream &out, const tlk::Connections& rhs);
std::ostream& operator<<(std::ostream &out, const tlk::ConnectionType& rhs);
