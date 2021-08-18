#define OLC_PGE_APPLICATION
#include "../hpp/olcPixelGameEngine.h"

#include "../hpp/Simulation.hpp"
#include "../hpp/DrawableMap.hpp"

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
	}

	bool OnUserCreate() override
	{
		std::string assetPath = "/home/tlk/Documents/Code/VSCode/ScotlandYard/assets/";
		map = new olc::Sprite(assetPath + "slymap.png");
		mapLocations.loadFromFile(assetPath + "Locations.txt");

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);
		DrawSprite(0, 0, map);
		
		for (const olc::vi2d& vector : mapLocations.getLocations())
			FillCircle(vector, 15, olc::BLACK);
		

		return true;
	}

private:
	olc::Sprite* map = nullptr;
	
	tlk::DrawableMap mapLocations;

};

int main(int argc, char const *argv[])
{	
	SLY_Viewer demo;

	if (demo.Construct(1444, 1124, 1, 1))
		demo.Start();


	return 0;
}


