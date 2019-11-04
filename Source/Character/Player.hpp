#pragma once



class Player : public BaseCharacter{
    public:
        Player();
        ~Player();
        bool Initialize(std::string, BaseBattleCtrl* btlCtrl);
    private:


};