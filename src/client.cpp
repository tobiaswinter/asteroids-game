// client.cpp : Defines the entry point for the console application.
//
#include "network\net_shared.h"
#include "network\NetRequest.h"
#include "Participant.h"
#include "GameState.h"
#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
    const char *DestinationName = (argc > 1) ? argv[1] : "localhost";
    const Uint16 DestinationPort = (argc > 2) ? atoi(argv[2]) : 2000;
    const std::string Behaviour = (argc > 3) ? argv[3] : "manual";

    // Initialize SDL_net
    if (SDLNet_Init() < 0)
    {
        std::cerr << "SDLNet_Init: " << SDLNet_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

    IPaddress ServerIP;
    TCPsocket ServerSocket;

    std::cout << "resolving hostname...\n";
    if (SDLNet_ResolveHost(&ServerIP, DestinationName, DestinationPort))
    {
        std::cerr << "failed to resolve " << DestinationName << "\n";
        std::cerr << SDL_GetError();
        exit(3);
    }

    Uint32 ServerIPHost = ServerIP.host;
    std::cout << "Server IP: ";
    std::cout << CNet::TranslateAddr(ServerIP.host);
    std::cout << ", port " << ServerIP.port;
    std::cout << "\n";

    std::cout << "connecting to server ";
    std::cout << CNet::TranslateAddr(ServerIP.host) << ":" << DestinationPort;
    std::cout << " (" << DestinationName << ")";
    std::cout << "...\n";
    ServerSocket = SDLNet_TCP_Open(&ServerIP);
    if (!ServerSocket)
    {
        std::cerr << "failed to connect to server\n";
        std::cerr << SDL_GetError();
        exit(4);
    }

    std::cerr << "sending player name...\n";

    //Insert your Playername here
    const char PlayerName[16] = "BOT";

    if (SDLNet_TCP_Send(ServerSocket, (void *)PlayerName, sizeof(PlayerName)) != sizeof(PlayerName))
    {
        std::cerr << "failed to notify client\n";
        std::cerr << SDL_GetError();
        exit(5);
    }

    char Buffer[BUFFER_SIZE];

    while (true)
    {
        GameState state;
        if (SDLNet_TCP_Recv(ServerSocket, (void *)Buffer, BUFFER_SIZE) != BUFFER_SIZE)
        {
            std::cerr << "failed to receive data from server\n";
            std::cerr << SDL_GetError();
            exit(5);
        }
        std::cout << "Received buffer from Server" << std::endl;

        std::istringstream iss(Buffer);
        state.Deserialize(iss);

        NetRequest* Action = new NetRequest();

        //Do magic here with Action

        std::cin.ignore();

        Action->moving = true;
        Action->shoot = true;

        //Dont touch the following

        int size = SDLNet_TCP_Send(ServerSocket, (void *)Action, sizeof(NetRequest));

        if (size != sizeof(NetRequest))
        {
            std::cerr << "failed to send data to server\n";
            std::cerr << SDL_GetError();
            exit(5);
        }
    }

    return 0;
}

