#pragma once


namespace StatusData{
     enum stringData : unsigned int;
     enum vectorData: unsigned int;
     enum intData: unsigned int;
}


class BaseCharacter;
class DataController{
    public :
        static DataController* getInstance(){
            if( instance == nullptr)
                instance = new DataController();
            return instance;
        }
        static void Delete();


        //Player Setting
        bool setPlayer( BaseCharacter* character );

        bool SetUIStringData(std::string dataName);
        bool SetUIPercentData( std::string dataName);
        bool SetUIValueData( std::string dataName );

        std::string GetStringUIData( StatusData::stringData data);
        Vector2 GetPercentUIData( StatusData::vectorData data);
        int GetValueUIData( StatusData::intData data);

        auto GetUIstringOrder();
        auto GetUIpercentOrder();
        auto GetUIvalueOrder();

        Vector2 GetPlayerPos();
        //Player Setting End


        bool setCharacter( BaseCharacter* character);
        bool removeCharacter(BaseCharacter* character );
        int GetEnemyCount();
        Vector2 GetEnemyPos(int index);

    private:
        static DataController* instance;
        DataController();
        ~DataController();

        BaseCharacter* player;

        std::list<BaseCharacter*> characters;

        std::vector<std::string> stringUIOrder;
        std::vector<std::string> percentUIOrder;
        std::vector<std::string> valueUIOrder;

};