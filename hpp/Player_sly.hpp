#pragma once

#include "PlayerInput.hpp"
#include "Connection.hpp"
#include "Entity.hpp"

#include <iostream>
#include <string>

namespace tlk
{
    class Player_sly : public Entity
    {
    public:
        Player_sly() : Entity(Team::SLY) { };
        virtual ~Player_sly() { };

    protected:

        virtual const Connection& getSelection(const Connections& options) override
        {
            return tlk::PlayerInput::consoleSelectMoveFromOptions(options, tickets);
        }
    };
}