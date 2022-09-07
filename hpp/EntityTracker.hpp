#pragma once

#include "Map.hpp"
#include "Entity.hpp"

#include <algorithm>
#include <vector>
#include <list>
#include <map>

namespace tlk
{

    /**
     * @brief This class knows the current locations of entities and is used to manipulate them
     * 
     */
    class EntityTracker
    {
    public:
        EntityTracker(const Map& map)
            : map(map), mrxLastSeenLocation(0) {  };
        ~EntityTracker() 
        {
            mrx_ticketHistory.clear();
            entityHistory.clear();
            positions.clear();
        };

        void track(const Entity& e);

        /**
         * @brief Set Starting Position for entity
         * TODO add Method to initialize Game 
         * 
         * @param e  Entity to use
         * @param startingPos Location where Entity starts
         */
        void setStartingPos(const Entity& e, int startingPos);

        /**
         * @brief Set Position of entity
         * TODO should not be required
         * 
         * @param e Entity to use
         * @param newPos new Position
         */
        void simulatePosition(const Entity& e, int newPos); //TODO make reverting an option also
        
        /**
         * @brief Update Entity with connection, validating connection used
         * TODO This method should only provide valid options so checking becomes irrelevant
         * 
         * @param e Entity to use
         * @param moved connection used by entity
         * @param used Ticket used for connection, relevant for Mrx Moves
         */
        void updatePosition(const Entity& e, const Move used);

        const Connections getMovesFor(const Entity& e) const;

        int getLocationOfMrx() const;
        int getLocationOf(const Entity& e) const;

        /**
         * @brief Return current location of all entities
         * TODO make vector constant length and hide mrx if neccecary
         * 
         * @param hideMrX if mrx is hidden, his location won't be added
         * @return const std::vector<int>  locations of entities in current round. 
         *          If mrx location is not hidden, it is the first location in the vector
         */
        const std::vector<int> getEntityLocations(bool hideMrX) const;

        const std::vector<int> getSlyLocations() const;

        /**
         * @brief Set the Mrx Location publicly 
         * TODO replace by call to update mrx location. This class knows where he currently is
         * 
         * @param loc location of mrx
         */
        void setMrxLocation(int loc)
        {
            mrxLastSeenLocation = loc;
            if (!mrx_ticketHistory.empty())
                mrx_ticketHistory.erase(mrx_ticketHistory.cbegin(), --mrx_ticketHistory.cend());
        }

        int getMrxLastSeenLocation() const
        {
            return mrxLastSeenLocation;
        }

        const std::vector<Ticket>& getMrxHistory() const
        {
            return mrx_ticketHistory;
        }

        /**
         * @brief Get history of moves by an entity
         * 
         * @param e Entity to use
         * @return a vector containing all moves by entity
         */
        // const Moves getEntityHistory(const Entity& e)
        // {
        //     return entityHistory.at(e);
        // }

        /**
         * @brief Get history of Connections used by an entity
         * 
         * @param e Entity to use
         * @return a vector containing all moves by entity
         */
        const Connections getEntityMovesHistory(const Entity& e) const
        {
            Connections conns;
            for (auto move : entityHistory.at(&e))
            {
                conns.push_back(move.first);
            }

            return conns;
        }

        /**
         * @brief get The locations where sly units were located at the begining of round
         * TODO This class has no round information, so this could return different results when called after first sly unit moved...
         * 
         * @param roundOffset round offset can be used to look at round - x. min is 0 as this can't predict location of sly
         * @return const std::vector<int> locations of sly units.
         */
        const std::vector<int> getSlyLocations(const int roundOffset) const;

    private:
        int mrxLastSeenLocation;
        std::vector<tlk::Ticket> mrx_ticketHistory;

        //TODO double information is stored here
        std::map<const Entity*, int> positions; 
        std::map<const Entity*, Moves> entityHistory;

        const Map& map;
    };
    
} // namespace tlk
