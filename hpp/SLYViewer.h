//
// Created by tlk on 08.10.24.
//

#ifndef SCOTLANDYARD_SLYVIEWER_H
#define SCOTLANDYARD_SLYVIEWER_H

#include "olcPixelGameEngine.h"
#include "Map.hpp"
#include "Game.hpp"
#include "DrawableMap.hpp"

namespace tlk {
    class SLYViewer : public olc::PixelGameEngine {
    public:
        SLYViewer();

        ~SLYViewer();

        void DrawThickLine(olc::vi2d p1, olc::vi2d p2, olc::Pixel p);

        bool OnUserCreate() override;

        bool OnUserUpdate(float fElapsedTime) override;


    private:
        const tlk::Map &gameMap;
        olc::Sprite *map = nullptr;
        tlk::Game *game = nullptr;

        tlk::DrawableMap drawableMap;
        tlk::State state = tlk::PLAYING;

        int backgroundLayer = 0;
    };
}
#endif //SCOTLANDYARD_SLYVIEWER_H
