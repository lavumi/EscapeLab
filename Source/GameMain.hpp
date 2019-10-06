#include <stdio.h>
#include <conio.h>
#include "../Framework/Map/FloorMap.hpp"
#include "../Framework/Character/Character.hpp"




#include "../Framework/Render/Renderer.hpp"
#include "../Framework/Render/CLI/Renderer_CLI.hpp"
#include "../Framework/Input/InputCtrl.hpp"


class GameMain{
    public : 
        GameMain();
        ~GameMain();

        bool Initialize();
        bool Update();

    private:

        FloorMap* sampleMap ;
        Character* player;
        Renderer* renderer; 
        InputController* inputCtrl;
};