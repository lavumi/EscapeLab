#include "Player.hpp"



Player::Player(std::string name ) :BaseCharacter(name) {

}

Player::~Player(){

}

bool Player::Initialize(){
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

    setValueData ("GLD", 993);



    ui->SetUIStringData("Name");
    ui->SetUIPercentData( "HP" );
    ui->SetUIPercentData("MP");


    ui->SetUIValueData ("STR");
    ui->SetUIValueData ("EV ");
    ui->SetUIValueData ("DEX");
    ui->SetUIValueData ("DEF");
    ui->SetUIValueData ("INT");
    ui->SetUIValueData ("GLD");
}


