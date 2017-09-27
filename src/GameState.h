#pragma once
#include "Serializable.h"
#include "Participant.h"
#include "Rigidbody.h"
#include <vector>

class GameState :
    public Serializable
{
private:
    std::vector<Participant*> participants;
public:
    GameState();
    ~GameState();

    void AddParticipant(Participant& participant);
    void RemoveParticipant(Participant& participant);
    std::vector<Participant*>::iterator RemoveParticipant(std::vector<Participant*>::iterator& it);

    void Update(double deltaTime);

    void Serialize(std::ostream& stream) override;
    void Deserialize(std::istream& stream) override;

    bool IsAnyPlayerAlive();

    void PrintScores();
};

