
class FloorMap;
class BaseCharacter;
class Renderer;
class InputController;
class DataController;
class BattleCtrl;
class CharacterGenerator;
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
        CharacterGenerator* charGenerator;
};
