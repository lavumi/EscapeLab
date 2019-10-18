#include "../Render/Renderer_CLI.hpp"
#include "LogController.hpp"
    
int LogController::current_LogCount = 0;
Renderer* LogController::renderer = nullptr;
std::string LogController::LogContainer[MaxLogContainerSize];


void LogController::Initialize( Renderer* renderer ){
    LogController::renderer = renderer;
    LogController::current_LogCount = 0;
};


int LogController::PrintLog( std::string text ){
   // renderer->RefreshLog(&text, 0);

    LogContainer[current_LogCount] = text;
    renderer->RefreshLog( LogContainer, current_LogCount );
    current_LogCount++;
    if(current_LogCount >= MaxLogContainerSize ){
        current_LogCount = 0;
    }
    return 0;
};
