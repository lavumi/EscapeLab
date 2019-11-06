#include "../Render/Renderer_CLI.hpp"
#include "LogController.hpp"
    
int LogController::current_LogCount = 0;
Renderer* LogController::renderer = nullptr;
std::string LogController::LogContainer[MaxLogContainerSize];


void LogController::Initialize( Renderer* renderer ){
    LogController::renderer = renderer;
    LogController::current_LogCount = MaxLogContainerSize;
    renderer->SetLogContainer( LogContainer, &current_LogCount);
};


int LogController::PrintLog( std::string text ){
   // renderer->RefreshLog(&text, 0);
    std::string inputText = text;
    while(inputText.length() < 35){
        inputText += " ";
    }

    current_LogCount++;
    if(current_LogCount >= MaxLogContainerSize ){
        current_LogCount = 0;
    }
    LogContainer[current_LogCount] = inputText;
    //renderer->RefreshLog( LogContainer, current_LogCount );

    return 0;
};
