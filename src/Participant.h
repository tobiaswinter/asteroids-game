#pragma once
#include "Serializable.h"
#include <string>

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
    std::string name;
    Type type;
public:
    Participant();
    ~Participant();

    void Serialize(std::ostream& stream) override;
    void Deserialize(std::istream& stream) override;

    Type GetType() { return type; }

};

