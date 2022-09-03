#include "../hpp/Map.hpp"


//Read MAp File and create Paths in both directions ordered by node
tlk::Map::Map(const std::string& path)
{
    std::ifstream file(path, std::ios::in);

    if (!file)
    {
        std::cerr << "Map::Map Searching Map at: " << path << std::endl;
        throw std::runtime_error("Map::Map no Map was found!");
    }
    
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
            const int targetid = stoi(token);
            const char type = token.substr(token.find(' '))[1];
            const tlk::ConnectionType cType = tlk::Connection::get_type_from_char(type);

            connectionsFromFile.emplace_back(id, targetid, cType);
            
            line.erase(0, pos + 1);
        }
    }
    
    file.close();
}

tlk::ColumnMap::ColumnMap(const std::string& path) : Map(path) 
{
    for (int i = 0; i < 201; ++i)
            gameFields[i] = std::make_unique<Connections>();

    //TODO fix so connections don't need to be stored twice
    for (Connection c : connectionsFromFile)
    {
        addConnection(c);
    }

    connectionsFromFile.clear();
};

void tlk::ColumnMap::addConnection(const Connection& connection)
{
    gameFields[connection.target]->push_back(connection);
    gameFields[connection.source]->push_back(connection);
} 

const tlk::Connections& tlk::ColumnMap::getOutgoing(const int loc) const
{
    return *gameFields.at(loc);
}

bool isOccupied(int pos, const std::vector<int>& occupied)
{
    return occupied.end() != std::find(occupied.begin(), occupied.end(), pos);
}

const tlk::Connections tlk::ColumnMap::getMovesFor(const Entity* e, const EntityTracker* tracker) const
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

std::ostream& operator<<(std::ostream &out, const tlk::ColumnMap &rhs)  
{

    for (int i = 0; i < 201; ++i)
    {
        out << "node " << i << " with " << rhs.getGameFields()[i]->size() << " connections: " << std::endl;
        out << *rhs.getGameFields()[i];
        
        out << "---------------------\n";
    }

	return out;
}