#include "GameState.h"
#include "network\NetRequest.h"


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
    unsigned int participantSize = participants.size();
    stream.write(reinterpret_cast<const char*>(&participantSize), sizeof(unsigned int));
    for (unsigned int i = 0; i < participantSize; ++i)
    {
        participants[i]->Serialize(stream);
    }
}

void GameState::Deserialize(std::istream & stream)
{
    participants.clear();
    unsigned int participantSize = 0;
    stream.read(reinterpret_cast<char*>(&participantSize), sizeof(unsigned int));
    for (unsigned int i = 0; i < participantSize; ++i)
    {
        Participant* p = new Participant();
        p->Deserialize(stream);
        participants.push_back(p);
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
