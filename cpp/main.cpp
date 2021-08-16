#define OLC_PGE_APPLICATION
#include "../hpp/olcPixelGameEngine.h"
#include "../hpp/Game.hpp"

#include <iostream>
#include <string>

class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));	
		return true;
	}
};

int main(int argc, char const *argv[])
{
    // Example demo;
	// if (demo.Construct(256, 240, 4, 4))
	// 	demo.Start();

	// return 0;

    tlk::Game g;

    g.setup();
    g.play();

    return 0;
}
