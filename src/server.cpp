// server.cpp : Defines the entry point for the console application.
//

#include <SDL_net.h>
#include <iostream>
#include <fstream>
#include <thread>

#include "GameState.h"
#include "Timer.h"
#include "network\net_shared.h"

int main(int argc, char* argv[])
{
    std::cout << "initializing SDL_Net...\n";
    if (SDLNet_Init() < 0)
    {
        std::cerr << "SDLNet_Init: " << SDLNet_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

    TCPsocket ServerSocket;
    IPaddress ServerIP;

    Timer timer;
    GameState state;
    Participant* gameMaster = new Participant("Master", Participant::Type::Gamemaster);
    state.AddParticipant(*gameMaster);

    std::cout << "resolving server ip...\n";
    if (SDLNet_ResolveHost(&ServerIP, 0, SERVER_PORT))
    {
        std::cerr << SDL_GetError() << "\n";
        exit(3); // TODO
    }
    std::cout << "Server IP: ";
    std::cout << CNet::TranslateAddr(ServerIP.host);
    std::cout << ", port: " << ServerIP.port;
    std::cout << "\n";

    std::cout << "opening server socket...\n";
    ServerSocket = SDLNet_TCP_Open(&ServerIP);
    if (!ServerSocket)
    {
        std::cerr << SDL_GetError() << "\n";
        exit(4); // TODO
    }

    std::cout << "listening at port " << SERVER_PORT << "...\n";

    bool startFlag = true;
    do
    {
        std::cout << "Waiting for Participant..." << std::endl;
        
        TCPsocket socket = nullptr;
        while (socket == nullptr)
        {
            socket = SDLNet_TCP_Accept(ServerSocket);
        }
        std::cout << "client connected ";
        IPaddress *ClientIP = SDLNet_TCP_GetPeerAddress(socket);
        if (ClientIP)
        {
            std::cout << "(IP ";
            std::cout << CNet::TranslateAddr(ClientIP->host);
            std::cout << " port " << ClientIP->port << ")" << std::endl;;
        }
        char PlayerName[16];
        if (SDLNet_TCP_Recv(socket, (void *)PlayerName, sizeof(PlayerName)) != sizeof(PlayerName))
        {
            std::cerr << "failed to receive player-name from client\n";
            std::cerr << SDL_GetError();
            exit(5);
        }
        Participant* player = new Participant(PlayerName, Participant::Type::Player);
        player->SetSocket(socket);
        state.AddParticipant(*player);

        std::cout << "Added Participant " << player->GetName() << std::endl;
        std::cout << "Add more? (y/n): ";
        char yn;
        std::cin >> yn;
        if (yn == 'n')
        {
            startFlag = false;
        }
    } while (startFlag);

    std::cout << "dedicated server running.\n";

    std::cout << "allocating buffer...\n";
    char Buffer[BUFFER_SIZE];
    timer.Start();

    std::cout << "Start game" << std::endl;
    while (state.IsAnyPlayerAlive())
    {
        state.HandleRequests();
        double deltaTime = timer.GetTimeDelta();
        timer.Reset();
        state.Update(FIXED_TIME_DELTA);
    }

    std::cout << "All players dead" << std::endl << std::endl;
    state.PrintScores();

    return 0;
}

