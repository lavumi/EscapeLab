#pragma once

#include "../../Framework/Character/Character.hpp"
#include "../../Framework/UserInterface/DataController.hpp"


class Player : public BaseCharacter{
    public:
        Player(std::string);
        ~Player();
        bool Initialize();

        virtual bool Move(int x, int y);

        virtual bool goUpstair();
        virtual bool goDownstair();
    private:


};