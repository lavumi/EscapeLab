#include "../Framework/Map/FloorMap.hpp"


#include "../Framework/Render/Renderer.hpp"

#ifdef _WIN32
    #include "../Framework/Render/Renderer_CLI.hpp"
#else
    #include "../Framework/Render/Renderer_ncrs.hpp"
#endif

#include "../Framework/Input/InputCtrl.hpp"
#include "../Framework/UserInterface/LogController.hpp"
#include "../Framework/UserInterface/DataController.hpp"

#include "../Framework/Character/Character.hpp"
#include "../Framework/Character/CharacterGenerator.hpp"
#include "../Source/Character/BattleCtrl.hpp"
#include "GameMain.hpp"


GameMain::GameMain(){

#ifdef _WIN32
    renderer = new Renderer_CLI();
#else
    renderer = new Renderer_ncrs();
#endif

    btlCtrl = new BattleCtrl();
    sampleMap = new FloorMap();

    charGenerator = new CharacterGenerator();
    inputCtrl = InputController::getInstance();
    dataCtrl = DataController::getInstance();
    LogController::Initialize( renderer );

}

GameMain::~GameMain(){ 

#ifdef _WIN32
    delete (Renderer_CLI*)renderer;
#else
    delete (Renderer_ncrs*)renderer;
#endif

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
