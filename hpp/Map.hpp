#pragma once

#include "Consts.hpp"
#include "Entity.hpp"
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
    static const bool READ_DISTANCES_FROM_FILE = 1;

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
        
        virtual int getDistanceBetween(const int pos, const int target, bool noBoat) const = 0;

    protected:
        void initMap();

        //TODO work on default implementation
        virtual void saveToFile() {};
        virtual void initFromFile() {};

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
        virtual void saveToFile();
        virtual void initFromFile();

        void buildDistanceTable();
        void printDistanceMap() const;
        void printLostDistances() const;

    private:
        //TODO add getter and setter for distances
        std::array<std::unique_ptr<Connections>, 201> gameFields;
        std::array<int, 20301>* distanceMap;

        int distanceAlgorithm(const int start, const int target);
        void addConnection(const Connection& connection);
        int getDistanceIdx(const int start, const int end) const;
    };

} // namespace tlk

std::ostream& operator<<(std::ostream &out, const tlk::Map& rhs);