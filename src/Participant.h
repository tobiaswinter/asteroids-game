#pragma once
#include "Serializable.h"
#include "Rigidbody.h"
#include <string>
#include <vector>

class Participant :
    public Serializable
{
public:
    enum Type {
        Gamemaster = 0,
        Player = 1,
        Observer = 2
    };
private:
    char* name;
    Type type;
    std::vector<Rigidbody> rigidbodies;
    Spacecraft* spacecraft;
public:
    Participant(char* name = "Participant", Type type = Type::Observer);
    ~Participant();

    void Serialize(std::ostream& stream) override;
    void Deserialize(std::istream& stream) override;

    Type GetType() { return type; }

    bool IsAlive();
};

