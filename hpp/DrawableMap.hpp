#pragma once 

#include "olcPixelGameEngine.h"

#include <fstream>
#include <sstream>
#include <string>
#include <array>

namespace tlk
{
    struct DrawableConneciton
    {
        olc::vi2d pos1;
        olc::vi2d pos2;
        olc::Pixel p;
    };

    class DrawableMap
    {
    public:
        DrawableMap() { };
        ~DrawableMap() { };

        void loadFromFile(const std::string& pathLocations);
        void link(GameLiveInfo liveInfo);

        const std::array<olc::vi2d, 200>& getLocations() const
        {
            return locations;
        }

        const std::vector<DrawableConneciton> getConnectionHistories()
        {
            std::vector<DrawableConneciton> outCons;

            const Connections mrxHist = gameInfo.tracker->getEntityMovesHistory(*gameInfo.mrx);
            for (int i = 1; i < mrxHist.size(); ++i)
            {
                DrawableConneciton dc;
                dc.pos1 = locations[mrxHist[i].source - 1];
                dc.pos2 = locations[mrxHist[i].target - 1];
                dc.p = getColorFor(mrxHist[i].type);
                outCons.push_back(dc);
            }

            for (const Entity* e : *gameInfo.sly)
            {
                const Connections mrxHist = gameInfo.tracker->getEntityMovesHistory(*e);
                
                for (int i = 1; i < mrxHist.size(); ++i)
                {
                    DrawableConneciton dc;
                    dc.pos1 = locations[mrxHist[i].source - 1];
                    dc.pos2 = locations[mrxHist[i].target - 1];
                    dc.p = getColorFor(mrxHist[i].type);
                    outCons.push_back(dc);
                }
            }

            return outCons;
        }

        const std::array<olc::vi2d, tlk::PLAYER_COUNT> getSLYLocations() const
        {
            std::array<olc::vi2d, tlk::PLAYER_COUNT> locs;
            auto locsItr = locs.begin();
            for (int ui : gameInfo.tracker->getSlyLocations())
                *locsItr++ = locations[ui-1];
            
            return locs;
        }

        olc::vi2d getMrxLocation() const
        {
            return locations[gameInfo.tracker->getLocationOf(*gameInfo.mrx)-1];
        }

    private:
        GameLiveInfo gameInfo;
        std::array<olc::vi2d, 200> locations;

        static olc::Pixel getColorFor(ConnectionType type)
        {
            switch (type)
            {
            case tlk::TAXI:
                return olc::YELLOW;

            case tlk::BUS:
                return olc::DARK_GREEN;

            case tlk::UNDERGROUND:
                return olc::DARK_RED;
                
            case tlk::BOAT:
                return olc::DARK_BLUE;
            
            default:
                return olc::MAGENTA;
            }
        }
    };

    void DrawableMap::link(GameLiveInfo liveInfo)
    {
        gameInfo = liveInfo;
    }
    
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
            int x = stoi(token);
            token = line.substr(pos+1, line.length());
            int y = stoi(token);

            locations[lineNo++] = olc::vi2d(x, y);
        }
    }
    
} // namespace tlk
