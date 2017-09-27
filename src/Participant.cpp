#include "Participant.h"
#include "GameSettings.h"
#include "Projectile.h"
#include <random>

Participant::Participant(char* name, Type type) :name(name), type(type)
{
    switch (type)
    {
    case Gamemaster:
        for (size_t i = 0; i < ASTEROID_COUNT; i++)
        {
            rigidbodies.push_back(new Projectile(this, Projectile::Type::Asteroid));
        }
        break;
    case Player:
        spacecraft = new Spacecraft();
        break;
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

void Participant::Update(double deltaTime)
{
    if (IsAlive())
    {
        if (spacecraft != nullptr)
        {
            if (spacecraft->IsVulnerable())
            {
                scoreTimeCounter += deltaTime;
                if (scoreTimeCounter > 1)
                {
                    score += SCORE_PER_SECOND;
                    scoreTimeCounter = 0;
                }
            }

            spacecraft->Update(deltaTime);
            if (spacecraft->GetLifes() <= 0)
            {
                delete spacecraft;
                spacecraft = nullptr;
            }

        }
    }
}

bool Participant::IsAlive()
{
    return spacecraft != nullptr || type != Player;
}

void Projectile::OnCollision(Rigidbody& other)
{
}