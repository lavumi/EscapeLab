#include <conio.h>


class InputController{

    private : 
    friend class GameMain;
        InputController();
        ~InputController();

        int WairForInput();
};