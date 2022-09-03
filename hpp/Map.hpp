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
        
        tlk::Connections getAllConnections() const;

        virtual const tlk::Connections& getOutgoing(const int loc) const = 0;
        
        /**
         * @brief Get the Moves For Entity
         * 
         * @param e entity for which to get moves
         * @param tracker knows entity position
         * @return * const Connections connections available
         */
        virtual const Connections getMovesFor(const Entity* e, const EntityTracker* tracker) const = 0;

        virtual int getDistanceBetween(const int pos, const int target, bool noBoat) const = 0;

    protected:
        Connections connectionsFromFile;

    private:
        virtual void addConnection(const Connection& connection) = 0;
    };

    class OutgoingLinksMap : public Map
    {
    public:
        OutgoingLinksMap(const std::string& path);
        ~OutgoingLinksMap() { };

        const tlk::Connections& getOutgoing(const int loc) const;
        const Connections getMovesFor(const Entity* e, const EntityTracker* tracker) const;
        int getDistanceBetween(const int pos, const int target, bool noBoat) const;


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

    class TableMap : public Map
    {
    public:
        TableMap(const std::string& path);
        ~TableMap() { };

        const tlk::Connections& getOutgoing(const int loc) const;
        const Connections getMovesFor(const Entity* e, const EntityTracker* tracker) const;
        int getDistanceBetween(const int pos, const int target, bool noBoat) const;

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
        std::array<std::array<int, 201>, 201> distanceMap;

        void printDistanceTable() const;

        int distanceAlgorithm(const int start, const int target);
        void addConnection(const Connection& connection);
        void buildDistanceTable();
        void setDistance(const int start, const int end, const int dist);
    };

} // namespace tlk

std::ostream& operator<<(std::ostream &out, const tlk::Map& rhs);
std::ostream& operator<<(std::ostream &out, const tlk::OutgoingLinksMap& rhs);
