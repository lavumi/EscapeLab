#include "../Framework/Map/FloorMap.hpp"


#include "../Framework/Render/Renderer.hpp"
#include "../Framework/Render/Renderer_CLI.hpp"
#include "../Framework/Render/Renderer_ncrs.hpp"
#include "../Framework/Input/InputCtrl.hpp"
#include "../Framework/UserInterface/LogController.hpp"
#include "../Framework/UserInterface/DataController.hpp"

#include "../Framework/Character/Character.hpp"
#include "../Source/Character/Player.hpp"
#include "../Source/Character/NonPlayer.hpp"
#include "../Source/Character/BattleCtrl.hpp"
#include "GameMain.hpp"


GameMain::GameMain(){

}

GameMain::~GameMain(){
    delete (Renderer_ncrs*)renderer;
    delete btlCtrl;
    delete sampleMap;


    delete (Player*)player;
    delete (NonPlayer*)enemy;



    InputController::Delete();
    DataController::Delete();
}

bool GameMain::Initialize(){
    renderer = new Renderer_ncrs();
    btlCtrl = new BattleCtrl();
    sampleMap = new FloorMap();
    player = new Player();
    enemy = new NonPlayer();
    inputCtrl = InputController::getInstance();
    dataCtrl = DataController::getInstance();

    LogController::Initialize( renderer );




    inputCtrl->SetPlayer( player );
    dataCtrl->setPlayer( player );
    dataCtrl->setCharacter( enemy );


    renderer->Initialize();
    renderer->inputMapData(sampleMap);



    ((Player*)player)->Initialize("Lavumi", btlCtrl);
    player->goDownstair( sampleMap );
    ((NonPlayer*)enemy)->Initialize("TESTENEMY");
    enemy->goDownstair( sampleMap );
    enemy->Move(40,40);
    return true;
}

bool GameMain::Update(){

    renderer->Render();
    bool result = inputCtrl->WairForInput();
    return result;
}
