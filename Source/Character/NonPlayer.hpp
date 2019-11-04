#pragma once

class BaseCharacter;
class NonPlayer : public BaseCharacter{
    public:
        NonPlayer();
        ~NonPlayer();
        bool Initialize(std::string);
    private:


};