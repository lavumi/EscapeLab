#pragma once
#include "../precompiled.hpp"

const int MaxLogContainerSize = 80;
class Renderer;
class LogController{
    public :
        static int PrintLog( std::string text);
        static void Initialize( Renderer* renderer);
        
    private : 
        friend class Renderer;    
        static std::string LogContainer[MaxLogContainerSize];
        static int current_LogCount;

        static Renderer* renderer;

};

