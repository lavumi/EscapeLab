#pragma once

#include "../../Framework/Character/Character.hpp"
#include "../../Framework/UserInterface/DataController.hpp"


class Player : public BaseCharacter{
    public:
        Player(std::string);
        ~Player();
        bool Initialize();
    private:


};