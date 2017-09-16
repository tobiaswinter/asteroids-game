#pragma once
#include "Serializable.h"
#include "Participant.h"
#include "Rigitbody.h"
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

    void Update(double deltaTime);

    void Serialize(std::ostream& stream) override;
    void Deserialize(std::istream& stream) override;
};

