#include "GameState.h"
#include "network\NetRequest.h"
#include <sstream>


GameState::GameState()
{
}


GameState::~GameState()
{
}

void GameState::AddParticipant(Participant& participant)
{
    participants.push_back(&participant);
}

std::vector<Participant*>::iterator GameState::RemoveParticipant(std::vector<Participant*>::iterator& it)
{
    return participants.erase(it);
}

void GameState::RemoveParticipant(Participant& participant)
{
    for (std::vector<Participant*>::iterator it = participants.begin(); it != participants.end();)
    {
        if (&participant == *it)
        {
            it = participants.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void GameState::Update(double deltaTime)
{
    Rigidbody::UpdatePhysics(deltaTime);
    for (std::vector<Participant*>::iterator it = participants.begin(); it != participants.end(); ++it)
    {
        (*it)->Update(deltaTime);
    }
}

void GameState::Serialize(std::ostream & stream)
{
    stream << participants.size();
    for (size_t i = 0; i < participants.size(); i++)
    {
        stream << "Test";
    }
}

void GameState::Deserialize(std::istream & stream)
{
    int ps = 0;
    stream >> ps;
    for (size_t i = 0; i < ps; i++)
    {
        std::string str;
        stream >> str;
        std::cout << str;
    }
}

bool GameState::IsAnyPlayerAlive()
{
    for each (Participant* p in participants)
    {
        if (p->IsAlive() && p->GetType() == Participant::Type::Player)
        {
            return true;
        }
    }
    return false;
}

void GameState::PrintScores()
{
    std::cout << "Scores:" << std::endl;
    for each(Participant* p in participants)
    {
        if (p->GetType() == Participant::Type::Player)
        {
            std::cout << p->GetName() << ": " << p->GetScore() << std::endl;
        }
    }
}

void GameState::HandleRequests()
{
    for each (Participant* p in participants)
    {
        if (p->GetType() == Participant::Type::Player)
        {
            NetRequest* request = new NetRequest;
            int size = SDLNet_TCP_Recv(p->GetSocket(), (void *)request, sizeof(NetRequest));
            std::cout << size << std::endl;
            if (size != sizeof(NetRequest))
            {
                std::cerr << "failed to receive Request\n";
                std::cerr << SDL_GetError();
                exit(5);
            }

        }
    }
}

void GameState::DistributeToCLients()
{
    char buffer[BUFFER_SIZE];
    std::stringstream ss;

    ss << 1;

    Serialize(ss);

    strcpy_s(buffer, ss.str().c_str());
    for each (Participant* p in participants)
    {
        if (p->GetType() == Participant::Type::Player)
        {
            if (SDLNet_TCP_Send(p->GetSocket(), (void *)buffer, BUFFER_SIZE) < BUFFER_SIZE)
            {
                std::cout << "failed to send data to client " << p->GetName() << "\n";
            }
        }
    }
}
