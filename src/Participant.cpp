#include "Participant.h"


Participant::Participant() :name("Participant")
{
}


Participant::~Participant()
{
}

void Participant::Serialize(std::ostream& stream) 
{
    unsigned int nameLength = name.length();
    stream.write(reinterpret_cast<const char*>(&nameLength), sizeof(unsigned int));
    stream.write(name.c_str(), sizeof(const char) * nameLength);
}

void Participant::Deserialize(std::istream& stream) 
{
    unsigned int nameLength = 0;
    stream.read(reinterpret_cast<char*>(&nameLength), sizeof(unsigned int));
    char* name = new char[nameLength];
    stream.read(name, sizeof(char) * nameLength);
}

