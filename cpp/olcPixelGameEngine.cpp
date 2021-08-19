#define OLC_PGE_APPLICATION
#include "../hpp/olcPixelGameEngine.h"

#include "../hpp/Game.hpp"
#include "../hpp/Simulation.hpp"
#include "../hpp/DrawableMap.hpp"
#include "../hpp/ConstsAndEnums.hpp"

class SLY_Viewer : public olc::PixelGameEngine
{
public:
	SLY_Viewer()
	{
		sAppName = "SLY_Viewer";
		gameMap = new tlk::Map("../assets/connections.txt"); 
	}

	~SLY_Viewer()
	{
		delete gameMap;
		delete map;
		delete game;
	}

	void DrawThickLine(olc::vi2d p1, olc::vi2d p2, olc::Pixel p)
	{
		olc::vi2d top (0, -1);
		olc::vi2d bot (0, 1);
		olc::vi2d left (-1, 0);
		olc::vi2d right (1, 0);

		DrawLine(p1, p2, p);
		DrawLine(p1 + top, p2 + top, p);
		DrawLine(p1 + bot, p2 + bot, p);
		DrawLine(p1 + left, p2 + left, p);
		DrawLine(p1 + right, p2 + right, p);
	}

	bool OnUserCreate() override
	{
		game = new tlk::Game(gameMap);
		map = new olc::Sprite(tlk::ASSETPATH + "slymap.png");

		drawableMap.loadFromFile(tlk::ASSETPATH + "Locations.txt");
		game->setup();
		drawableMap.link(game->getGameLiveInfo());

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);
		DrawSprite(0, 0, map);
		
		// int idxCount = 1;
		// for (const olc::vi2d& pos : drawableMap.getLocations())
		// {
		// 	FillCircle(pos, 15, olc::BLACK);
		// 	DrawString(pos-olc::vi2d(7, 6), std::to_string(idxCount++), olc::WHITE, 1);
		// }


		if (GetMouse(olc::Mouse::LEFT).bPressed && state == tlk::PLAYING)
			state = game->playSingleRound();

		if (GetMouse(olc::Mouse::RIGHT).bPressed)
		{
			delete game;
			game = new tlk::Game(gameMap);
			game->setup();
			drawableMap.link(game->getGameLiveInfo());
			state = tlk::PLAYING;
		}

		for (const tlk::DrawableConneciton& dc : drawableMap.getConnectionHistories())
		{
			DrawThickLine(dc.pos1, dc.pos2, dc.p);
		}

		FillCircle(drawableMap.getMrxLocation(), 15, olc::BLACK);
		FillCircle(drawableMap.getMrxLocation(), 10, olc::Pixel(200, 100, 0));

		for (const olc::vi2d& pos : drawableMap.getSLYLocations())
		{
			FillCircle(pos, 15, olc::DARK_BLUE);
			FillCircle(pos, 10, olc::WHITE);
		}

		switch (state)
		{
		case tlk::WON_SLY:
			DrawString((ScreenWidth()-100)/2, ScreenHeight()/2, "SLY Units WON!", olc::RED, 4);
			break;

		case tlk::WON_MRX:
			DrawString((ScreenWidth()-100)/2, ScreenHeight()/2, "MRX WON!", olc::RED, 4);
			break;

		default:
			break;
		}

		return true;
	}

	
private:
	tlk::Map* gameMap = nullptr;
	olc::Sprite* map = nullptr;
	tlk::Game* game = nullptr;

	tlk::DrawableMap drawableMap;
	tlk::State state = tlk::PLAYING;

};

int main(int argc, char const *argv[])
{	
	if (tlk::GRAPHICAL_INTERFACE)
	{
		SLY_Viewer demo;

		if (demo.Construct(1444, 1124, 1, 1))
			demo.Start();
	}
	else
	{
		tlk::Simulation sim;
		sim.start();
	}

	return 0;
}


