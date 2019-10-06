#include <vector>


//맵들을 관리해주는 클래스
//싱글톤으로 생성해서 쓰자


class FloorMap;
class MapManager {
    public : 
        static MapManager* getInstance(){
            return instance;
        }
        static bool Delete();

        bool Initialize( );
        bool AddMap( FloorMap* map, int floor);
        FloorMap* getMap( int floor );

    private : 
        static MapManager* instance;
        
        MapManager();
        ~MapManager();

        

};