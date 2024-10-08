//
// Created by tlk on 08.10.24.
//
#include "../hpp/Main.hpp"

int main(int argc, char const *argv[])
{
    if (tlk::RUN_TESTS)
    {
        const tlk::Map& map = tlk::DistanceMap(tlk::ASSETPATH + "/connections.txt");
        tlk::GameDebug sut(&map);

        bool testcompleted = sut.runTests();

        if (!testcompleted)
            return 1;
    }

    if (tlk::GRAPHICAL_INTERFACE)
    {
        tlk::SLYViewer demo;

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