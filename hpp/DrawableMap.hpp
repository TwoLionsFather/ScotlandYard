#pragma once 

#include "olcPixelGameEngine.h"
#include "Connection.hpp"
#include "Game.hpp"

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

        const std::array<olc::vi2d, 200>& getLocations() const;

        const std::vector<DrawableConneciton> getConnectionHistories();

        const std::array<olc::vi2d, tlk::PLAYER_COUNT> getSLYLocations() const;

        olc::vi2d getMrxLocation() const;

    private:
        GameLiveInfo gameInfo;
        std::array<olc::vi2d, 200> locations;

        static olc::Pixel getColorFor(ConnectionType type);
    };
    
} // namespace tlk
