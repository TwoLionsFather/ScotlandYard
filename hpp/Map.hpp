#pragma once

#include "Consts.hpp"
#include "Entity.hpp"
#include "Connection.hpp"
#include "TicketStack.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
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
        explicit Map(const std::string& path);
        virtual ~Map();
        
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

    class DistanceMap : public Map
    {
    public:
        DistanceMap(const std::string& path);
        virtual ~DistanceMap() { 
            delete distanceMap;
        };

        virtual const tlk::Connections& getOutgoing(const int loc) const;
        virtual int getDistanceBetween(const int pos, const int target, bool noBoat) const;

        /**
         * @brief Method giving access to the internal structure of the Map
         * 
         * @return const std::array<std::unique_ptr<Connections>, 201>& Array Containing leavong connections for each node
         */
        const std::array<std::unique_ptr<Connections>, 201>& getGameFields() const;

    //TODO these might become private
    protected:
        virtual void saveToFile();
        virtual void initFromFile();

        void buildDistanceTable();
        void printDistanceMap() const;
        void printLostDistances() const;
        inline int getDistance(const int start, const int end) const;
        inline void setDistance(const int start, const int end, const int distance);

    private:
        //TODO add getter and setter for distances
        std::array<std::unique_ptr<Connections>, 201> gameFields;
        std::array<int, 20301>* distanceMap;

        virtual void addConnection(const Connection& connection);
        int distanceAlgorithm(const int start, const int target);
        int getDistanceIdx(const int start, const int end) const;
    };

} // namespace tlk

std::ostream& operator<<(std::ostream &out, const tlk::Map& rhs);