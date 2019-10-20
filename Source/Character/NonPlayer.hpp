#pragma once

class BaseCharacter;
class NonPlayer : public BaseCharacter{
    public:
        NonPlayer(std::string);
        ~NonPlayer();
        bool Initialize();
    private:


};