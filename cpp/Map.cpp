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
tlk::Map::Map(const std::string& path)
{
    std::ifstream file(path, std::ios::in);

    for (int i = 0; i < 201; ++i)
        gameFields[i] = std::make_unique<Connections>();
    

    if (!file)
        throw std::runtime_error("Map::Map keine Map im File assetss/connections.txt gefunden!");
    
    
    size_t pos;
    std::string token;
    for (std::string line; std::getline(file, line); )
    {
        pos = line.find(";");
        token = line.substr(0, pos);
        int id = stoi(token);
        line.erase(0, pos + 1);


        while ((pos = line.find(';')) != std::string::npos) //npos is not found in String
        {
            token = line.substr(0, pos);
            int targetid = stoi(token);
            char type = token.substr(token.find(' '))[1];

            //add reverseedge

            gameFields[targetid]->emplace_back(id, get_type_from_char(type));
            gameFields[id]->emplace_back(targetid, get_type_from_char(type));

            line.erase(0, pos + 1);
        }
    }

    file.close();
}

tlk::Map::~Map()
{

}

const tlk::Connections& tlk::Map::getOutgoing(const int loc) const
{
    return *gameFields.at(loc);
}

bool isOccupied(int pos, const std::vector<int>& occupied)
{
    return occupied.end() != std::find(occupied.begin(), occupied.end(), pos);
}

const tlk::Connections tlk::Map::getMovesFor(const Entity* e, const EntityTracker* tracker) const
{
    const Connections& options = *gameFields.at(tracker->getLocationOf(e)).get();
    const std::vector<int>& occPos = tracker->getEntityLocations(true);

    if (options.empty())
        throw std::invalid_argument("Map::getMovesFor No options were found for an entity inside of Map::getMovesFor function!!");
    
    Connections possible;
    for (const Connection& c : options)
    {
        if (e->hasTicketFor(c.type) 
        && !isOccupied(c.target, occPos))
            possible.emplace_back(c.target, c.type);
    }

    return possible;
}

std::ostream& operator<<(std::ostream &out, const tlk::Map &rhs)  
{

    for (int i = 0; i < 201; ++i)
    {
        out << "node " << i << " with " << rhs.getGameFields()[i]->size() << " connections: " << std::endl;
        out << *rhs.getGameFields()[i];
        
        out << "---------------------\n";
    }

	return out;
}