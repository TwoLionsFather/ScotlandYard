#pragma once

#include "Map.hpp"
#include "Connection.hpp"
#include "EntityTracker.hpp"
#include "TicketStack.hpp"

#include <algorithm>
#include <optional>
#include <list>
#include <set>
#include <unordered_set>
#include <bitset>
#include <iostream>

namespace tlk
{
    class VirtualMap
    {
    public:
        VirtualMap(const Map& original, EntityTracker& tracker);
        ~VirtualMap();
        

        bool neighboursContainSLY (const int pos) const;
        bool neighboursContainMRXSighting (const int pos) const;
        
        int getDistanceToMrxReport(const int pos) const;
        int getDistanceToMrxReport(const Entity* e) const;

        int getDistanceToClosestSly() const;
        int getDistanceToClosestSly(const int start) const;
        int getDistanceToClosestSly(const Entity* e) const;

        int getDistanceBetween(const int pos, const int target) const;
        int getDistanceBetween(const Entity* e, const int target) const;

        int countSLYsInRange(const int pos, const int dist) const;

        std::unordered_set<int> getMrxPossibleLocationsAfter (const int roundCount, const bool blockUsed = true) const;
        std::unordered_set<int> getMrxPossibleLocationsAfter (const Entity* ent, const Connection& con) const;
        /**
         * @brief Get the Possible Locations After a certain ammount of rounds has been played
         * When simulating blocked locations, tracker data is used to block moves that would end on positions occupied by sly.
         * This only works up to current round, as future locations of sly units are unknown
         * TODO Fix potential issues related to this
         * 
         * @param start start location search from here
         * @param roundCount how many rounds to calculate, max 200, negative numbers and 0 return only start location 
         * @param futureMode future mode doesn't block locations occupied.
         * @param tickets is optional argument, can be used to simulate entity using specified connection types
         * @return std::unordered_set<int> set conatining all locations reachable within round
         */
        std::unordered_set<int> getPossibleLocationsAfter (const int start, const int roundCount, const bool futureMode = true, const std::optional<std::vector<Ticket>>& tickets = std::nullopt) const;

        double getDistanceToMrx(int i) const;

    private:
        const Map& originalMap;
        EntityTracker& tracker; //TODO Evaluate better option?

        //Per default every Location except MrXs get blocked for first iteration if multiple rounds are calculated
        std::unordered_set<int> reachableOneRound(const int pos, const bool blockUsed = true, const std::optional<Ticket>& ticket = std::nullopt) const;
        std::unordered_set<int> getNewLocations(const std::unordered_set<int>& pos, const bool blockUsed = true, const std::optional<Ticket>& ticket = std::nullopt) const;
    };
    
} // namespace tlk
