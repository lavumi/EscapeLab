#pragma once

class BaseCharacter;
class InputController{
    private : 

        static InputController* instance;
        InputController();
        ~InputController();


    public:
        static InputController* getInstance(){
            if( instance == nullptr)
                instance = new InputController();
            return instance;
        }
        static void Delete();


    private:
        enum InputMode {
            NORMAL,
            RANGE_ATTACK
        };
        void changeMode(InputMode mode);
        InputMode currentMode;
        BaseCharacter* player;

        Vector2 cursor;
    public :

        int WairForInput();
        void SetPlayer( BaseCharacter* player );
        Vector2 GetCursorPos();
};