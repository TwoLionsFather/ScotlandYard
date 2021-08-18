#define OLC_PGE_APPLICATION
#include "../hpp/olcPixelGameEngine.h"

#include "../hpp/Game.hpp"
#include "../hpp/DrawableMap.hpp"
#include "../hpp/ConstsAndEnums.hpp"

class SLY_Viewer : public olc::PixelGameEngine
{
public:
	SLY_Viewer()
	{
		sAppName = "SLY_Viewer";
	}

	~SLY_Viewer()
	{
		delete map;
		delete game;
	}

	bool OnUserCreate() override
	{
		game = new tlk::Game();
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

		FillCircle(drawableMap.getMrxLocation(), 15, olc::BLACK);
		FillCircle(drawableMap.getMrxLocation(), 10, olc::Pixel(200, 100, 0));

		for (const olc::vi2d& pos : drawableMap.getSLYLocations())
		{
			FillCircle(pos, 15, olc::DARK_BLUE);
			FillCircle(pos, 10, olc::WHITE);
		}


		if (GetMouse(olc::Mouse::LEFT).bPressed && state == tlk::PLAYING)
			state = game->playSingleRound();
		

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
	olc::Sprite* map = nullptr;
	tlk::Game* game = nullptr;

	tlk::DrawableMap drawableMap;
	tlk::State state = tlk::PLAYING;

};

int main(int argc, char const *argv[])
{	
	SLY_Viewer demo;

	if (demo.Construct(1444, 1124, 1, 1))
		demo.Start();


	return 0;
}


