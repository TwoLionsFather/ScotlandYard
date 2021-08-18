#pragma once 

#include "olcPixelGameEngine.h"


#include <fstream>
#include <sstream>
#include <string>
#include <array>

namespace tlk
{
    class DrawableMap
    {
    public:
        DrawableMap() { };
        ~DrawableMap() { };

        void loadFromFile(const std::string& pathLocations);

        const std::array<olc::vi2d, 200>& getLocations() const
        {
            return locations;
        }

    private:
        std::array<olc::vi2d, 200> locations;
    };
    
    void DrawableMap::loadFromFile(const std::string& pathLocations)
    {
        std::ifstream file(pathLocations, std::ios::in);

        if (!file)
            throw std::runtime_error("keine Map im File assetss/connections.txt gefunden!");

        int lineNo = 0;
        std::string token;
        for (std::string line; std::getline(file, line); )
        {
            size_t pos = line.find(",");

            token = line.substr(0, pos);
            uint x = stoi(token);
            token = line.substr(pos+1, line.length());
            uint y = stoi(token);

            locations[lineNo++] = olc::vi2d(x, y);
        }
    }
    
} // namespace tlk
