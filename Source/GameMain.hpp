
class FloorMap;
class Player;
class NonPlayer;
class BaseCharacter;
class Renderer;
class InputController;
class DataController;
class BattleCtrl;
class GameMain{
    public : 
        GameMain();
        ~GameMain();

        bool Initialize();
        bool Update();

    private:

        FloorMap* sampleMap ;

        Renderer* renderer; 
        InputController* inputCtrl;
        DataController* dataCtrl;
        BattleCtrl* btlCtrl;


        BaseCharacter* player;
        BaseCharacter* enemy;
};
