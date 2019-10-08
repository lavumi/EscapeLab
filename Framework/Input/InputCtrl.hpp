#include <conio.h>
#include "../Character/Character.hpp"

class InputController{
    public:
        static InputController* getInstance(){
            if( instance == nullptr)
                instance = new InputController();
            return instance;
        }
        static void Delete();
        void WairForInput();
        void SetPlayer( BaseCharacter* player );
    private : 

        static InputController* instance;
        InputController();
        ~InputController();
        BaseCharacter* player;

};