//
// Created by tlk on 08.10.24.
//
#include "../hpp/Player_sly.hpp"

const tlk::Connection &tlk::Player_sly::getSelection(const tlk::Connections &options)
{
    return tlk::PlayerInput::consoleSelectMoveFromOptions(options, tickets);
}

tlk::Player_sly::~Player_sly() {

}

tlk::Player_sly::Player_sly() : Entity(Team::SLY) {

}
