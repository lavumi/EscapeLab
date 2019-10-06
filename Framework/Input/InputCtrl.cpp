#include "InputCtrl.hpp"

InputController::InputController(){

}

InputController::~InputController(){

}

int InputController::WairForInput(){
    return getch();
}