#include "../hpp/Map.hpp"

//TODO add debug functionalities

//Read Map File and create Paths inside it
void tlk::Map::initMap()
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

            addConnection(Connection {id, targetid, cType});
            
            line.erase(0, pos + 1);
        }
    }
    
    file.close();
}

const tlk::Connections tlk::Map::getAllConnections() const
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

    distanceMap = new std::array<int, 20301>();
    distanceMap->fill(-1);

    //This needs to be called here so that a Map Object is constructed and memory initiated
    initMap(); 

    if (READ_DISTANCES_FROM_FILE)
    {
        initFromFile();
    }
    else 
    {
        buildDistanceTable();
        saveToFile();
    }

    if (tlk::LOG_LEVEL >= tlk::HIGH)
    {
        printDistanceMap();
    }
}

void tlk::TableMap::printLostDistances() const
{
    std::cout << "distanceMap " << std::endl;

    int lost = 0;
    for (int i = 0; i < distanceMap->size(); ++i)
    {
        int val = distanceMap->at(i);
        if (val == -1)
            continue;
        
        ++lost;
        std::cout << i << ". ";
    }

    std::cout << std::endl;
    std::cout << "Lost Location indices: " << lost << std::endl;
}

void tlk::TableMap::printDistanceMap() const
{
    std::cout << "Distances: from:";
    for (int i = 1; i < 201; i = i +10)
    {
        std::cout << i << " ";
        for (int j = 1; j < 201; j = j +10)
        {
            std::cout << j << ":";

            std::cout << distanceMap->at(getDistanceIdx(i, j)) << " ";
        }
        std::cout << std::endl;
    }
}

int tlk::TableMap::getDistanceIdx(const int start, const int end) const
{
    const int total = 200 * 201 /2;

    if (start < end)
    {
        const int sumTillCol = (201 - end) * (202 - end) /2;
        const int diff = end -start;
        return total -sumTillCol +diff;
    } 
    else 
    {
        const int sumTillCol = (201 - start) * (202 - start) /2;
        const int diff = start -end;
        return total -sumTillCol +diff; 
    }
    // if (start == 200)
    // std::cout << " Reverse for " << start << " to " << end << std::endl;

    return getDistanceIdx(end, start);
}

void tlk::TableMap::addConnection(const Connection& connection)
{
    gameFields[connection.target]->push_back(connection.getReverse());
    gameFields[connection.source]->push_back(connection);
    distanceMap->at(getDistanceIdx(connection.source, connection.target)) = 1;
} 

void tlk::TableMap::buildDistanceTable()
{
    for (int start = 1; start < 201; ++start)
    {
        if (tlk::LOG_LEVEL >= tlk::LOW)
            std::cout << "Building distances from: " << start << std::endl;
        

        for (int end = 2; end < 201; ++end)
        {
            if (end == 108) //TODO Fix node 108 related issues
                continue;

            //if node distance is already calculated
            if (getDistanceBetween(start, end, true) != -1)
                continue;

            const int distance = distanceAlgorithm(start, end);
            distanceMap->at(getDistanceIdx(start, end)) = distance;
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
                // TODO this doesn't improve performance, might remove
                // if (getDistanceBetween(i, con.target, true) == -1)
                // {
                    distanceMap->at(getDistanceIdx(i, con.target)) = distance;
                // }
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

const tlk::Connections& tlk::TableMap::getOutgoing(const int loc) const
{
     if (tlk::LOG_LEVEL >= tlk::HIGH)
        std::cout << "get outgoing from " << loc  << std::endl;

    std::cout << "All connections: " << getAllConnections() << std::endl;
    return *gameFields.at(loc);
}

bool isOccupied(int pos, const std::vector<int>& occupied)
{
    return occupied.end() != std::find(occupied.begin(), occupied.end(), pos);
}

int tlk::TableMap::getDistanceBetween(const int s, const int t, bool noBoat) const
{
    if (s == t)
        return 0;

    const int distance = distanceMap->at(getDistanceIdx(s, t));   
    // std::cout << " is " << distance << std::endl; 

    return distance;
}


void tlk::TableMap::saveToFile() 
{
    //TODO make Filepath constant
    std::ofstream resultFile(ASSETPATH + "/distanceMap.txt",  std::ofstream::out);
    
    for (int i = 1; i < 201; ++i)
    {
        for (int j = 1; j < 201; ++j)
        {
            resultFile << distanceMap->at(getDistanceIdx(i, j)) << " ";
        }
        resultFile << std::endl;
    }
    resultFile.close();
}

void tlk::TableMap::initFromFile() 
{
    std::ifstream file(ASSETPATH + "/distanceMap.txt", std::ios::in);

    if (!file)
    {
        std::cerr << "Map::Map Searching Map at: " << ASSETPATH + "/distanceMap.txt" << std::endl;
        throw std::runtime_error("Map::Map no Map was found!");
    }

    int sourceID = 1;
    for (std::string line; std::getline(file, line); ++sourceID)
    {
        int targetID = 1;
        size_t pos = line.find(' ');
        std::string token = line.substr(0, pos);
        
        distanceMap->at(getDistanceIdx(sourceID, targetID++)) = stoi(token);
        line.erase(0, pos + 1);

        while ((pos = line.find(' ')) != std::string::npos) //npos is not found in String
        {
            token = line.substr(0, pos);
            distanceMap->at(getDistanceIdx(sourceID, targetID++)) = stoi(token);
            line.erase(0, pos + 1);
        }
    }

    file.close();
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