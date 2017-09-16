#include "GameState.h"



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

void GameState::RemoveParticipant(Participant& participant)
{
    for (std::vector<Participant*>::iterator it = participants.begin(); it != participants.end(); ++it)
    {
        if (&participant == *it)
        {
            participants.erase(it);
        }
    }
}

void GameState::Update(double deltaTime)
{
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
