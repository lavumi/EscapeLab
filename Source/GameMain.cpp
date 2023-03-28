#include "../Framework/Map/FloorMap.hpp"


#include "../Framework/Render/Renderer.hpp"
#include "../Framework/Render/Renderer_CLI.hpp"
#include "../Framework/Render/Renderer_nCursor.hpp"
#include "../Framework/Input/InputCtrl.hpp"
#include "../Framework/UserInterface/LogController.hpp"
#include "../Framework/UserInterface/DataController.hpp"

#include "../Framework/Character/Character.hpp"
#include "../Framework/Character/CharacterGenerator.hpp"
#include "../Framework/Character/BattleCtrl.hpp"
#include "GameMain.hpp"


GameMain::GameMain(){
    renderer = new Renderer_nCursor();
    btlCtrl = new BattleCtrl();
    sampleMap = new FloorMap();

    charGenerator = new CharacterGenerator();
    inputCtrl = InputController::getInstance();
    dataCtrl = DataController::getInstance();
    LogController::Initialize( renderer );

}

GameMain::~GameMain(){
    delete (Renderer_nCursor*)renderer;
    delete btlCtrl;
    delete sampleMap;
    delete charGenerator;

    InputController::Delete();
    DataController::Delete();
}

bool GameMain::Initialize(){

    charGenerator->Initialize(btlCtrl);

    BaseCharacter* player = charGenerator->makeCharacter(
            Status("Lavumi", 100, 80, 12, 6, 9,5,9,523),
            sampleMap,
            sampleMap->getStartPos(),
            true);
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
    int processTurn = inputCtrl->WairForInput();

    switch (processTurn)
    {
    case 0:
        return false;
        break;
    case 1:
        dataCtrl->Update();
        return true;
        break;
    case 2:
        return true;
        break;
    default:
        break;
    }
    return true;
}
