#include "../hpp/Game.hpp"

#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    tlk::Game g;

    g.setup();
    g.play();

    return 0;
}
