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
    Participant* gameMaster = new Participant("Master", Participant::Type::Gamemaster);
    state.AddParticipant(*gameMaster);
    std::cout << "Waiting for Player..." << std::endl;

    bool startFlag = true;
    while (startFlag)
    {
        //Sync add here
        Participant* player = new Participant("Player", Participant::Type::Player);
        state.AddParticipant(*player);
        std::cout << "Added player " << player->GetName() << std::endl;
        std::cout << "Add more? (y/n): ";
        char yn;
        std::cin >> yn;
        if (yn == 'n')
        {
            startFlag = false;
        }
    }
    timer.Start();

    while (state.IsAnyPlayerAlive())
    {
        double deltaTime = timer.GetTimeDelta();
        timer.Reset();
        state.Update(deltaTime);
    }

    std::cout << "All players dead" << std::endl << std::endl;
    state.PrintScores();
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

