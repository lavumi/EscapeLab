
#include <stdio.h>
//#include <conio.h>
#include "../Framework/Map/FloorMap.hpp"


#include "../Framework/Render/Renderer.hpp"
#include "../Framework/Render/CLI/Renderer_CLI.hpp"
#include "../Framework/Input/InputCtrl.hpp"


#include "../Source/Character/Player.hpp"


class GameMain{
    public : 
        GameMain();
        ~GameMain();

        bool Initialize();
        bool Update();

    private:

        FloorMap* sampleMap ;
        BaseCharacter* player;
        Renderer* renderer; 
        InputController* inputCtrl;
};
