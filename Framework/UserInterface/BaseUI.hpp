#pragma once

#include <iostream>
#include <map>
#include <vector>
#include "../Variables.hpp"



/*   UI 형태

    Lavumi - Magician
    HP : 100/100 ##########
    MP :  10/ 30 ####------
    STR : 10    | AC : 10
    DEX : 5     | EV : 15
    INT : 11    |    
    Gold : 100



    Rule
    1. Single StringData -> PercentData -> Single Data 순서대로 위에서부터 나열된다
    2. SingleData 는 2줄로 나뉘어서 표현해준다.


*/

class BaseUI{
    public :
        BaseUI();
        ~BaseUI();

        bool InitStringData(std::string dataName);
        bool InitPercentData( std::string dataName);
        bool InitValueData( std::string dataName );


        bool SetStringData( std::string dataName, std::string stringData);
        bool SetPercentData( std::string dataName, int curValue, int MaxValue);
        bool SetValueData( std::string dataName, int value);

        std::string GetStringData( std::string dataName);
        Vector2 GetPercentData( std::string dataName);
        int GetValueData( std::string dataName);


        std::vector<std::string> GetstringUIOrder(){
            return stringUIOrder;
        };
        std::vector<std::string> GetpercentUIOrder(){
            return percentUIOrder;
        };
        std::vector<std::string> GetvalueUIOrder(){
            return valueUIOrder;
        };


    private:

        std::map<std::string, std::string > stringUIData;
        std::map<std::string, Vector2> percentUIData;
        std::map<std::string, int > valueUIData;


        std::vector<std::string> stringUIOrder;
        std::vector<std::string> percentUIOrder;
        std::vector<std::string> valueUIOrder;

};