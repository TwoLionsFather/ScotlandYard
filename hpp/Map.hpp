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
    static std::vector<int> startingPositions = {103, 112, 34, 155, 94, 117, 132, 53, 174, 198, 50, 91, 26, 29, 141, 13, 138, 197};//{58, 34, 14, 29, 52, 94, 78, 66, 86, 105, 100, 137, 154, 157, 135, 144, 180, 199};
   
    class Map
    {
    public:
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
        
    };
} // namespace tlk

std::ostream& operator<<(std::ostream &out, const tlk::Map& rhs);
