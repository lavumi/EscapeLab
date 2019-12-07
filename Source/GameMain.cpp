#include "../Framework/Map/FloorMap.hpp"


#include "../Framework/Render/Renderer.hpp"
#include "../Framework/Render/Renderer_CLI.hpp"
#include "../Framework/Render/Renderer_ncrs.hpp"
#include "../Framework/Input/InputCtrl.hpp"
#include "../Framework/UserInterface/LogController.hpp"
#include "../Framework/UserInterface/DataController.hpp"

#include "../Framework/Character/Character.hpp"
#include "../Framework/Character/CharacterGenerator.hpp"
#include "../Framework/Character/BattleCtrl.hpp"
#include "GameMain.hpp"


GameMain::GameMain(){
    renderer = new Renderer_ncrs();
    btlCtrl = new BattleCtrl();
    sampleMap = new FloorMap();

    charGenerator = new CharacterGenerator();
    inputCtrl = InputController::getInstance();
    dataCtrl = DataController::getInstance();
    LogController::Initialize( renderer );

}

GameMain::~GameMain(){
    delete (Renderer_ncrs*)renderer;
    delete btlCtrl;
    delete sampleMap;
    delete charGenerator;

    InputController::Delete();
    DataController::Delete();
}

bool GameMain::Initialize(){

    charGenerator->Initialize(btlCtrl);

    BaseCharacter* player = charGenerator->makeCharacter( Status("Lavumi", 100, 80, 12, 6, 9,5,9,523), sampleMap, Vector2( MaxMapWidth / 2, MaxMapHeight / 2), true);
    BaseCharacter* enemy = charGenerator->makeCharacter( Status("TestEnemy", 30, 80, 12, 6, 9,5,9,523), sampleMap, Vector2( 7, 17));

    inputCtrl->SetPlayer( player );
    dataCtrl->setPlayer( player );
    dataCtrl->setCharacter( enemy );
 
    renderer->Initialize();
    renderer->inputMapData(sampleMap);

    return true;
}

bool GameMain::Update(){

    renderer->Render();
    bool result = inputCtrl->WairForInput();
    return result;
}
