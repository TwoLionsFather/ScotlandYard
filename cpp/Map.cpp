#include "../hpp/Map.hpp"

#include <iostream>


tlk::ConnectionType get_type_from_char(char type)
{
    switch (type)
    {
    case 'T': return tlk::TAXI;
    case 'B': return tlk::BUS;
    case 'U': return tlk::UNDERGROUND;
    case 'H': return tlk::BOAT;

    default: return tlk::UNDEFINED;
    }
}

//Read MAp File and create Paths in both directions ordered by node
tlk::Map::Map(std::string path)
{
    std::ifstream file(path, std::ios::in);

    if (!file)
        throw std::runtime_error("keine Map im File assetss/connections.txt gefunden!");
    

    size_t pos;
    std::string token;
    for (std::string line; std::getline(file, line); )
    {
        pos = line.find(";");
        token = line.substr(0, pos);
        uint id = stoi(token);
        line.erase(0, pos + 1);

        if (gameFields.find(id) == gameFields.end())
            gameFields[id] = std::make_unique<Connections>();

        while ((pos = line.find(';')) != std::string::npos) //npos is not found in String
        {
            token = line.substr(0, pos);
            int targetid = stoi(token);
            char type = token.substr(token.find(' '))[1];

            //add reverseedge
            if (gameFields.find(targetid) == gameFields.end())
                gameFields[targetid] = std::make_unique<Connections>();
        
            gameFields[targetid]->emplace_back(id, get_type_from_char(type));
            gameFields[id]->emplace_back(targetid, get_type_from_char(type));

            line.erase(0, pos + 1);
        }
    }

    file.close();
}

tlk::Map::~Map()
{
    gameFields.clear();
}

const tlk::Connections tlk::Map::getMovesFor(const Entity* e, const EntityTracker* posTrack) const
{
    const Connections& options = *gameFields.at(posTrack->getLocationOf(e)).get();
    const std::list<uint>& occPos = posTrack->getEntityLocations(true);

    if (options.empty())
        throw std::invalid_argument("No options were found for an entity inside of Map::getMovesFor function!!");
    

    Connections possible;
    auto hasTicket = [&e](auto con) {return !e->isAllowedToUse(con.type);};
    std::remove_copy_if(options.begin(), options.end(), std::back_inserter(possible), hasTicket);

    auto isOccupied = [&occPos] (const auto con) {return occPos.end() != std::find(occPos.begin(), occPos.end(), con.target);};
    const auto possEnd = std::remove_if(possible.begin(), possible.end(), isOccupied);
    possible.erase(possEnd, possible.end());

    return possible;
}

std::ostream& operator<<(std::ostream &out, const tlk::Map &rhs)  
{
    for (auto& itr : rhs.getGameFields())
    {
        out << "node " << itr.first << " with " << itr.second->size() << " connections: " << std::endl;
        out << *(itr.second.get());
        
        out << "---------------------\n";
    }

	return out;
}