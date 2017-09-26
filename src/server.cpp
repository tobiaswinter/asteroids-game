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
    Participant gameMaster("Master", Participant::Type::Player);
    state.AddParticipant(gameMaster);

    state.AddParticipant(Participant("TestPlayer", Participant::Type::Player));

    double deltaTime = timer.GetTimeDelta();
    timer.Reset();
    state.Update(deltaTime);

    //std::ofstream os;
    //os.open("test.bin", std::ofstream::out | std::ofstream::binary);
    //state.Serialize(os);
    //os.close();

    //GameState gs2;
    //std::ifstream is;
    //is.open("test.bin", std::istream::in | std::istream::binary);
    //gs2.Deserialize(is);
    //is.close();

    return 0;
}

