#pragma once

#include "Entity.hpp"
#include "EntityTracker.hpp"
#include "Connection.hpp"
#include "TicketStack.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

namespace tlk
{
    /**
     * @brief Representation of a Map for the scotland yard game. 
     * 
     */
    class Map
    {
    public:
        /**
         * @brief Construct a new Map object using a file with all the connections that ar part of the map
         * 
         * @param path path to a file conatining map connections
         */
        Map(const std::string& path);
        ~Map();
        
        const tlk::Connections& getOutgoing(const int loc) const;
        const Connections getMovesFor(const Entity* e, const EntityTracker* tracker) const;

        const std::array<std::unique_ptr<Connections>, 201>& getGameFields() const
        {
            return gameFields;
        }

    private:
        std::array<std::unique_ptr<Connections>, 201> gameFields;
        void addConnection(Connection);
        
    };

    class ColumnMap
    {
    public:
        ColumnMap();
    };

} // namespace tlk

std::ostream& operator<<(std::ostream &out, const tlk::Map& rhs);
