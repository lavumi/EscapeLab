#include "../../Framework/Character/Character.hpp"
#include "../../Framework/UserInterface/DataController.hpp"
#include "NonPlayer.hpp"


NonPlayer::NonPlayer(std::string name ) :BaseCharacter(name) {

}

NonPlayer::~NonPlayer(){

}

bool NonPlayer::Initialize(){
    position.x = MaxMapWidth / 2;
    position.y = MaxMapHeight / 2;

    DataController* ui = DataController::getInstance();


    setStringData("Name", name);
    setPercentData( "HP" , 23, 100);
    setPercentData("MP", 40, 80);

    setValueData ("STR", 17);
    setValueData ("EV ", 9);
    setValueData ("DEX", 12);
    setValueData ("DEF", 12);
    setValueData ("INT", 23);
    
    return true;
}

