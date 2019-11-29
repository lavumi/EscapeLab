#pragma once
#include "../precompiled.hpp"

typedef struct _status
{
    std::string* StringData;
    Vector2* VectorData;
    int* intData;

    _status(){
        StringData = new std::string[StatusData::stringDataLength];
        VectorData = new Vector2[StatusData::vectorDataLength];
        intData = new int[StatusData::intDataLength];

        StringData[0] = "NoName";
        VectorData[0] = Vector2(1, 1);
        VectorData[1] = Vector2(0, 0);
        intData[0] = 0; 
        intData[1] = 0; 
        intData[2] = 0;  
        intData[3] = 0;  
        intData[4] = 0;  
        intData[5] = 0;
    }

    _status(std::string name, int HP, int MP, int STR, int EV, int DEX, int DEF, int INT, int GLD)
    {
        StringData = new std::string[StatusData::stringDataLength];
        VectorData = new Vector2[StatusData::vectorDataLength];
        intData = new int[StatusData::intDataLength];
        StringData[0] = name;
        VectorData[0] = Vector2(HP, HP);
        VectorData[1] = Vector2(MP, MP);
        intData[0] = STR; 
        intData[1] = EV; 
        intData[2] = DEX;  
        intData[3] = DEF;  
        intData[4] = INT;  
        intData[5] = GLD;
    }

    ~_status(){
      //  delete[] StringData;
      //  delete[] VectorData;
      //  delete[] intData;
    }

    _status operator=(_status &p)
    {

        StringData[0] = p.StringData[0];

        VectorData[0]   = p.VectorData[0];
        VectorData[1]   = p.VectorData[1];
        intData[0]      = p.intData[0]   ;
        intData[1]      = p.intData[1]   ;
        intData[2]      = p.intData[2]   ;
        intData[3]      = p.intData[3]   ;
        intData[4]      = p.intData[4]   ;
        intData[5]      = p.intData[5]   ;

        return *this;
    }

} Status;




class FloorMap;
class FieldOfView;
class BaseBattleCtrl;
class BaseCharacter
{
public:
    BaseCharacter();
    ~BaseCharacter();

    bool Initialize(BaseBattleCtrl *battleCtrl, Status stats, Vector2 position, bool isPlayer);

    bool Move(int x, int y);
    bool goUpstair(FloorMap *targetMap);
    bool goDownstair(FloorMap *targetMap);

    std::string getStatusData(StatusData::stringData);
    Vector2 getStatusData(StatusData::vectorData);
    int getStatusData(StatusData::intData);

    Vector2 GetPos()
    {
        return position;
    }

    FloorMap *GetCurrentMap() { return currentMap; };

    bool MeleeAttack(BaseCharacter *target);

    void TakeDamage(int atk);

    bool isDead()
    {
        return _isDead;
    }
    bool __setPosition(Vector2 pos );

protected:
    bool isPlayerCharacter;

    std::string name;
    Vector2 position;
    FloorMap *currentMap;
    Status *stats;

    FieldOfView *fov;

    int sightSize;

    BaseBattleCtrl *btlCtrl;

    void die();
    bool _isDead;
};