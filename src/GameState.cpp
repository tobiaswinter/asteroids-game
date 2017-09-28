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
    stream << participants.size() << ",";
    for (size_t i = 0; i < participants.size(); i++)
    {
        participants[i]->Serialize(stream);
        stream << ",";
    }
}

void GameState::Deserialize(std::istream & stream)
{
    int ps = 0;
    char sep = ',';
    stream >> ps;
    stream >> sep;
    participants.clear();
    for (size_t i = 0; i < ps; i++)
    {
        Participant* p = new Participant();
        p->Deserialize(stream);
        participants.push_back(p);
        stream >> sep;
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
    for (std::vector<Participant*>::iterator it = participants.begin(); it != participants.end(); ++it)
    {
        Participant* p = (*it);
        if (p->GetType() == Participant::Type::Player)
        {
            NetRequest* request = new NetRequest;
            int size = SDLNet_TCP_Recv(p->GetSocket(), (void *)request, sizeof(NetRequest));
            std::cout << size << std::endl;
            if (size != sizeof(NetRequest))
            {
                std::cerr << "failed to receive Request from " << p->GetName() << std::endl;
                std::cerr << "Remove Player from Participants" << std::endl;
                participants.erase(it);
                return;
            }
            p->spacecraft->SetForwardVector(request->forwardVector);
            if (request->moving)
            {
                p->spacecraft->SetVelocity(request->forwardVector * (float)SPACECRAFT_SPEED);
            }
            if (request->shoot)
            {
                Projectile* proj = p->spacecraft->Shoot(p);
                if (proj != nullptr)
                {
                    p->AddRigidbody(proj);
                }
            }
        }
    }
}

void GameState::DistributeToCLients()
{
    char buffer[BUFFER_SIZE];
    std::stringstream ss;

    Serialize(ss);

    strcpy_s(buffer, ss.str().c_str());

    std::cout << buffer;
    for (std::vector<Participant*>::iterator it = participants.begin(); it != participants.end(); ++it)
    {
        Participant* p = (*it);
        if (p->GetType() != Participant::Type::Gamemaster)
        {
            if (SDLNet_TCP_Send(p->GetSocket(), (void *)buffer, BUFFER_SIZE) < BUFFER_SIZE)
            {
                std::cout << "failed to send data to client " << p->GetName() << std::endl;
                std::cerr << "Remove Player from Participants" << std::endl;
                participants.erase(it);
                return;
            }
        }
    }
}
