//
// Created by tlk on 08.10.24.
//
#include "../hpp/Player_mrx.hpp"

const tlk::Connection &tlk::Player_mrx::getSelection(const tlk::Connections &options)
{
    return tlk::PlayerInput::consoleSelectMoveFromOptions(options, tickets);
}

tlk::Ticket tlk::Player_mrx::getTicket(tlk::ConnectionType usedTransportation)
{
    return tlk::PlayerInput::consoleSelectTicket(usedTransportation, tickets);
}

tlk::Player_mrx::~Player_mrx() {

}

tlk::Player_mrx::Player_mrx() : Entity(Team::MRX) {

}
