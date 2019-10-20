
class FloorMap;
class BaseCharacter;
class Renderer;
class InputController;
class DataController;
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
        DataController* dataCtrl;


        BaseCharacter* enemy;
};
