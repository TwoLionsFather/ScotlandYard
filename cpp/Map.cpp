#include "../hpp/Map.hpp"

#include <iostream>


tlk::ConnectionType get_type_from_char(char type)
{
    switch (type)
    {
    case 'T': return tlk::ConnectionType::TAXI;
    case 'B': return tlk::ConnectionType::BUS;
    case 'U': return tlk::ConnectionType::UNDERGROUND;
    case 'H': return tlk::ConnectionType::BOAT;

    default: return tlk::ConnectionType::UNDEFINED;
    }
}

//Read MAp File and create Paths in both directions ordered by node
tlk::Map::Map(std::string path)
{
    std::ifstream file;
    file.open(path, std::ios::in);

    if (!file)
    {
        throw "kein File gefunden!";
    }

    size_t pos;
    std::string token;
    for (std::string line; std::getline(file, line); )
    {
        pos = line.find(";");
        token = line.substr(0, pos);
        int id = stoi(token);
        line.erase(0, pos + 1);

        if (gameFields.find(id) == gameFields.end())
            gameFields[id] = std::make_unique<Connections>();

        while ((pos = line.find(';')) != std::string::npos) 
        {
            token = line.substr(0, pos);
            int targetid = stoi(token);
            char type = token.substr(token.find(' '))[1];

            //add reverseedge
            if (gameFields.find(targetid) == gameFields.end())
                gameFields[targetid] = std::make_unique<Connections>();
        
            gameFields[targetid]->emplace_back(Connection(id, get_type_from_char(type)));
            gameFields[id]->emplace_back(Connection(targetid, get_type_from_char(type)));

            line.erase(0, pos + 1);
        }
    }

    file.close();
}

tlk::Map::~Map()
{
    gameFields.clear();
}

const tlk::Connections tlk::Map::getMovesFor(const Entity& e, const std::vector<unsigned int>& occupiedPos) const
{
    //TODO test if copy or reference is used
    Connections selection = *gameFields.find(e.getPos())->second;

    if (selection.empty())
        throw std::invalid_argument("No options were found for an entity inside of Maps Connectin search function!!");
    
    Connections tmp;
    std::remove_copy_if(selection.begin(), selection.end(), std::back_inserter(tmp),
                        [&](auto connection) {return !e.isAllowedToUse(connection.type);});

    selection.clear();
    std::remove_copy_if(tmp.begin(), tmp.end(), std::back_inserter(selection),
                        [&](auto connection) {  for (unsigned int ui : occupiedPos)
                                                    if (ui == connection.target)
                                                        return true;
                                                        
                                                return false;});

    return selection;
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