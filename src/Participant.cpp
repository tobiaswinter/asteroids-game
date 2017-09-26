#include "Participant.h"


Participant::Participant(char* name, Type type) :name(name), type(type)
{
    if (type == Player)
    {
        spacecraft = new Spacecraft();
    }
}


Participant::~Participant()
{
}

void Participant::Serialize(std::ostream& stream) 
{
    unsigned int nameLength = strlen(name);
    stream.write(reinterpret_cast<const char*>(&nameLength), sizeof(unsigned int));
    stream.write(reinterpret_cast<const char*>(&name), nameLength);
    stream.write(reinterpret_cast<const char*>(&type), sizeof(int));
}

void Participant::Deserialize(std::istream& stream) 
{
    unsigned int nameLength = 0;
    stream.read(reinterpret_cast<char*>(&nameLength), sizeof(unsigned int));
    stream.read(reinterpret_cast<char*>(&name), nameLength);
    stream.read(reinterpret_cast<char*>(&type), sizeof(int));
}

bool Participant::IsAlive()
{
    if (type == Player)
    {
        return spacecraft->GetLifes() > 0;
    }
    return true;
}

