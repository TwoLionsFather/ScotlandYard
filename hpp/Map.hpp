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
        virtual ~Map() { };
        
        virtual const tlk::Connections& getOutgoing(const int loc) const = 0;
        virtual const Connections getMovesFor(const Entity* e, const EntityTracker* tracker) const = 0;

    private:
        virtual void addConnection(const Connection& connection) = 0;
    };

    class ColumnMap : public Map
    {
    public:
        ColumnMap(const std::string& path) : Map(path) {
            for (int i = 0; i < 201; ++i)
                    gameFields[i] = std::make_unique<Connections>();
         };
        ~ColumnMap() { };

        const tlk::Connections& getOutgoing(const int loc) const;
        const Connections getMovesFor(const Entity* e, const EntityTracker* tracker) const;


        /**
         * @brief Method giving access to the internal structure of the Map
         * 
         * @return const std::array<std::unique_ptr<Connections>, 201>& Array Containing leavong connections for each node
         */
        const std::array<std::unique_ptr<Connections>, 201>& getGameFields() const
        {
            return gameFields;
        }

    private:
        std::array<std::unique_ptr<Connections>, 201> gameFields;
        void addConnection(const Connection& connection);
    };

} // namespace tlk

std::ostream& operator<<(std::ostream &out, const tlk::ColumnMap& rhs);
