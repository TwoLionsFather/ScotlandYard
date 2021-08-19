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
