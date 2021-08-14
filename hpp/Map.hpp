#pragma once

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
    class Map
    {
    public:
        Map(std::string path);
        ~Map();
        
        const Connections getMovesFor(const Entity* e, const std::vector<unsigned int>& occupiedPos) const;

        const std::map<int, std::unique_ptr<Connections>>& getGameFields() const
        {
            return gameFields;
        }

    private:
        std::map<int, std::unique_ptr<Connections>> gameFields;
    };
} // namespace tlk


std::ostream& operator<<(std::ostream &out, const tlk::Map& rhs);
