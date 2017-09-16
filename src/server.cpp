// server.cpp : Defines the entry point for the console application.
//

#include <SDL_net.h>
#include <iostream>
#include <fstream>
#include <thread>

#include "GameState.h"
#include "Timer.h"

int main(int argc, char* argv[])
{
    Timer timer;
    GameState state;
    timer.Start();

    while (true)
    {
        double deltaTime = timer.GetTimeDelta();
        timer.Reset();
        state.Update(deltaTime);
    }
    return 0;
}

