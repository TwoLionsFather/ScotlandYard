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
        Map(const std::string& path) : path(path) { };
        virtual ~Map() { };
        
        /**
         * @brief Uses every node as a start and adds connections leaving it
         * 
         * @return const tlk::Connections list of all directional connections
         */
        const tlk::Connections getAllConnections() const;
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
        void initMap();

    private:
        virtual void addConnection(const Connection& connection) = 0;

        const std::string path;
    };

    class TableMap : public Map
    {
    public:
        TableMap(const std::string& path);
        virtual ~TableMap() { 
            delete distanceMap;
        };

        virtual const tlk::Connections& getOutgoing(const int loc) const;
        virtual const Connections getMovesFor(const Entity* e, const EntityTracker* tracker) const;
        virtual int getDistanceBetween(const int pos, const int target, bool noBoat) const;

        /**
         * @brief Method giving access to the internal structure of the Map
         * 
         * @return const std::array<std::unique_ptr<Connections>, 201>& Array Containing leavong connections for each node
         */
        const std::array<std::unique_ptr<Connections>, 201>& getGameFields() const
        {
            return gameFields;
        }

    protected:
        void buildDistanceTable();
        void printDistanceMap() const;
        void printLostDistances() const;

    private:
        std::array<std::unique_ptr<Connections>, 201> gameFields;
        std::array<int, 20301>* distanceMap;

        int distanceAlgorithm(const int start, const int target);
        void addConnection(const Connection& connection);
        int getDistanceIdx(const int start, const int end) const;
    };

} // namespace tlk

std::ostream& operator<<(std::ostream &out, const tlk::Map& rhs);