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

tlk::Connections tlk::Map::getAllConnections() const
{
    Connections conns;
    for (int i = 0; i < 201; ++i)
    {
        Connections out = getOutgoing(i);
        conns.insert(std::end(conns),std::begin(out), std::end(out));
    }

    return conns;
}

tlk::TableMap::TableMap(const std::string& path) : Map(path) 
{
    for (int i = 0; i < 201; ++i)
        gameFields[i] = std::make_unique<Connections>();

    distanceMap.reserve(201);
    distanceMap.emplace_back(NULL);
    for (int i = 0; i < 201; ++i)
    {
        std::vector<int> distancesTo(201-i, -1);
        //Debug output to display halftable
        //std::cout << "Current Node: " << i << " knows distance to: " << 201-i << std::endl;
        distanceMap.push_back(distancesTo);
    }

    //TODO fix so connections don't need to be stored twice
    for (Connection c : connectionsFromFile)
    {
        addConnection(c);
    }

    connectionsFromFile.clear();

    buildDistanceTable();
}

void tlk::TableMap::addConnection(const Connection& connection)
{
    gameFields[connection.target]->push_back(connection.getReverse());
    gameFields[connection.source]->push_back(connection);

    addDistance(connection.source, connection.source, 0);
    addDistance(connection.target, connection.target, 0);
    addDistance(connection.source, connection.target, 1);
} 

void tlk::TableMap::printDistanceTable() const
{
    // for (int from = 0; from < 201; ++from)
    // {
    //     // std::cout << "From: " << from << std::endl;
    //     for (int to = 0; to < 201; ++to)
    //     {
    //         int dist = tlk::TableMap::getDistanceBetween(from, to, true); 
    //         if (dist != -1)
    //             std::cout << to << ":" << dist << " ";
    //         else 
    //             std::cout << ". ";
    //     }
    //     std::cout << std::endl;
    // }
}

void tlk::TableMap::buildDistanceTable()
{
    for (int start = 1; start < 201; ++start)
    {
        for (int end = 2; end < 201; ++end)
        {
            if (end == 108)
                continue;

            //if node distance is already calculated
            if (distanceMap[start][end-start] != -1)
                continue;

            // if (start == 1)
            // {
            //     std::cout << "buildDistanceTable" << std::endl;
            // }
            int distance = distanceAlgorithm(start, end);
            addDistance(start, end, distance);
        }
        if (start == 108)
            continue;
    }
}

int tlk::TableMap::distanceAlgorithm(const int start, const int target)
{
    if (start == target)
        return 0;

    if (start == 108 || target == 108)
        return -2; //TODO Fix this node is not in the game!
    
    
    int distance = 1;
    bool locationsUsed[201] = { false };
    std::vector<int> locationsQueue, newLocs;

    locationsUsed[start] = true;
    locationsQueue.emplace_back(start);

    do {
        for (int i : locationsQueue)
            for (const Connection& con : getOutgoing(i))
            {
                if (locationsUsed[target])
                    continue;

                //TODO Add Boat support
                else if (con.type == tlk::BOAT)
                    continue;

                newLocs.emplace_back(con.target);
                locationsUsed[con.target] = true;
                if (getDistanceBetween(i, con.target, true) == -1)
                {
                    addDistance(i, con.target, distance);
                }
            }

        locationsQueue.swap(newLocs);
        newLocs.clear();

        if (distance++ == 200)
        {
            std::cerr << "Distance Search between " << start << " and " << target << " failed!"; 
            throw std::runtime_error("OutgoingLinksMap::getDistanceBetween Distance runaway situation!");
        }
    } while (!locationsUsed[target]);

    return distance;
}

void tlk::TableMap::addDistance(const int start, const int end, const int dist)
{
    //TODO Check if keying works correctly
    int distanceFrom = std::min(start, end);
    int distanceTo = std::max(start, end) - distanceFrom;

    distanceMap[distanceFrom].at(distanceTo) = dist;

    // if (distanceFrom == 1)
    // {
    //     std::cout << "TableMap::addDistance between Nodes " << start;
    //     std::cout << " and " << end << " is " << dist << std::endl; 
    // }
}

const tlk::Connections& tlk::TableMap::getOutgoing(const int loc) const
{
    return *gameFields.at(loc);
}

bool isOccupied(int pos, const std::vector<int>& occupied)
{
    return occupied.end() != std::find(occupied.begin(), occupied.end(), pos);
}

const tlk::Connections tlk::TableMap::getMovesFor(const Entity* e, const EntityTracker* tracker) const
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

int tlk::TableMap::getDistanceBetween(const int pos, const int target, bool noBoat) const
{
    int distanceFrom = std::min(pos, target);
    int distanceTo = std::max(pos, target) - distanceFrom;
    // std::cout << "TableMap::getDistanceBetween  " << distanceFrom << " and " << distanceTo;
    
    int distance = distanceMap[distanceFrom][distanceTo];   
    // std::cout << " is " << distance << std::endl; 

    return distance;
}


tlk::OutgoingLinksMap::OutgoingLinksMap(const std::string& path) : Map(path) 
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

void tlk::OutgoingLinksMap::addConnection(const Connection& connection)
{
    gameFields[connection.target]->push_back(connection.getReverse());
    gameFields[connection.source]->push_back(connection);
} 

const tlk::Connections& tlk::OutgoingLinksMap::getOutgoing(const int loc) const
{
    return *gameFields.at(loc);
}

const tlk::Connections tlk::OutgoingLinksMap::getMovesFor(const Entity* e, const EntityTracker* tracker) const
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

int tlk::OutgoingLinksMap::getDistanceBetween(const int pos, const int target, bool noBoat) const
{
    if (pos == target)
        return 0;

    int distance = 1;
    bool locationsUsed[201] = { false };
    std::vector<int> locationsQueue, newLocs;

    locationsUsed[pos] = true;
    locationsQueue.emplace_back(pos);

    do {
        for (int i : locationsQueue)
            for (const Connection& con : getOutgoing(i))
            {
                if (locationsUsed[con.target])
                    continue;

                else if (noBoat && con.type == tlk::BOAT)
                    continue;

                newLocs.emplace_back(con.target);
                locationsUsed[con.target] = true;
            }

        locationsQueue.swap(newLocs);
        newLocs.clear();

        if (distance++ == 200)
            throw std::runtime_error("OutgoingLinksMap::getDistanceBetween Distance runaway situation!");
    } while (!locationsUsed[target]);

    return distance;
}

std::ostream& operator<<(std::ostream &out, const tlk::Map &rhs)  
{
    out << "Map all nodes are:";

    for (tlk::Connection c : rhs.getAllConnections())
    {
        out << c << std::endl;
    }

	return out;
}

std::ostream& operator<<(std::ostream &out, const tlk::OutgoingLinksMap &rhs)  
{
    for (int i = 0; i < 201; ++i)
    {
        out << "node " << i << " with " << rhs.getGameFields()[i]->size() << " connections: " << std::endl;
        out << *rhs.getGameFields()[i];
        
        out << "---------------------\n";
    }

	return out;
}