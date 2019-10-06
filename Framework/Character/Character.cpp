#include "Character.hpp"



Character::Character(){
    position.x = MaxMapWidth / 2;
    position.y = MaxMapHeight / 2;
}

Character::~Character(){

}

bool Character::Move(int x, int y){
    position.x += x;
    position.y += y;
    return true;
}

Vector2 Character::GetPos(){
    return position;
}
