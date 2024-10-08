#pragma once

#include "PlayerInput.hpp"
#include "Connection.hpp"
#include "Entity.hpp"

#include <iostream>
#include <string>

namespace tlk
{
    class [[maybe_unused]] Player_sly : public Entity
    {
    public:
        Player_sly() ;
        ~Player_sly() override;

    protected:

        virtual const Connection& getSelection(const Connections& options) override;
    };
}