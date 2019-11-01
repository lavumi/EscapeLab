#include "../Framework/Map/FloorMap.hpp"


#include "../Framework/Render/Renderer.hpp"
#include "../Framework/Render/Renderer_CLI.hpp"
#include "../Framework/Render/Renderer_ncrs.hpp"
#include "../Framework/Input/InputCtrl.hpp"
#include "../Framework/UserInterface/LogController.hpp"

#include "../Source/Character/Player.hpp"
#include "../Source/Character/NonPlayer.hpp"
#include "../Source/Character/BattleCtrl.hpp"
#include "GameMain.hpp"


GameMain::GameMain(){

}

GameMain::~GameMain(){
    delete (Renderer_ncrs*)renderer;
    delete sampleMap;
    delete (Player*)player;

    InputController::Delete();
    DataController::Delete();
}

bool GameMain::Initialize(){
    renderer = new Renderer_ncrs();
    sampleMap = new FloorMap();
    player = new Player("Lavumi");
    enemy = new NonPlayer("TESTENEMY");
    inputCtrl = InputController::getInstance();
    dataCtrl = DataController::getInstance();

    LogController::Initialize( renderer );

    BattleCtrl* btlCtrl = new BattleCtrl();


    inputCtrl->SetPlayer( player );
    dataCtrl->setPlayer(player);
    dataCtrl->setCharacter(enemy);

    player->Initialize();
    renderer->Initialize();
    renderer->inputMapData(sampleMap);
    player->goDownstair( sampleMap );


    enemy->Initialize();
    enemy->goDownstair( sampleMap );
    enemy->Move(40,40);
    return true;
}

bool GameMain::Update(){

    renderer->Render();
    bool result = inputCtrl->WairForInput();
    return result;
}
