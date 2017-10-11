#include "Participant.h"
#include "GameSettings.h"
#include "Projectile.h"
#include <random>

Participant::Participant(std::string name, Type type) :name(name), type(type)
{
    switch (type)
    {
    case Gamemaster:
        for (size_t i = 0; i < ASTEROID_COUNT; i++)
        {
            Projectile* p = new Projectile(this, Projectile::Type::Asteroid);
            vector3 location
            {
                (float)(std::rand() % ARENA_WIDTH) - (ARENA_WIDTH / 2),
                (float)(std::rand() % ARENA_WIDTH) - (ARENA_WIDTH / 2),
                ((float)(std::rand() % ARENA_WIDTH) - (ARENA_DEPTH / 2)) * !IGNORE_Z_AXIS
            };
            vector3 direction
            {
                (float)(std::rand() % ARENA_WIDTH) - (ARENA_WIDTH / 2),
                (float)(std::rand() % ARENA_WIDTH) - (ARENA_WIDTH / 2),
                ((float)(std::rand() % ARENA_WIDTH) - (ARENA_DEPTH / 2)) * !IGNORE_Z_AXIS
            };
            float length = direction.length();
            direction = direction * (BULLET_SPEED / length);
            p->SetVelocity(direction);
            p->SetLocation(location);
            rigidbodies.push_back(p);
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
    stream << name << std::endl << ",";
    stream << type << ",";
    stream << score << ",";
    stream << rigidbodies.size() << ",";
    for (size_t i = 0; i < rigidbodies.size(); i++)
    {
        stream << rigidbodies[i]->GetType() << ",";
        stream << rigidbodies[i]->GetLocation().x << ",";
        stream << rigidbodies[i]->GetLocation().y << ",";
        stream << rigidbodies[i]->GetLocation().z << ",";
        stream << rigidbodies[i]->GetVelocity().x << ",";
        stream << rigidbodies[i]->GetVelocity().y << ",";
        stream << rigidbodies[i]->GetVelocity().z << ",";
        stream << rigidbodies[i]->GetRadius() << ",";
    }
    stream << (spacecraft != nullptr) << ";";
    if (spacecraft != nullptr)
    {
        stream << spacecraft->GetType() << ",";
        stream << spacecraft->GetLocation().x << ",";
        stream << spacecraft->GetLocation().y << ",";
        stream << spacecraft->GetLocation().z << ",";
        stream << spacecraft->GetVelocity().x << ",";
        stream << spacecraft->GetVelocity().y << ",";
        stream << spacecraft->GetVelocity().z << ",";
        stream << spacecraft->GetRadius() << ",";
        stream << spacecraft->GetShotCooldown() << ",";
        stream << spacecraft->GetLifes() << ",";
        stream << spacecraft->GetForwardVector().x << ",";
        stream << spacecraft->GetForwardVector().y << ",";
        stream << spacecraft->GetForwardVector().z << ",";
    }

}

void Participant::Deserialize(std::istream& stream)
{
    char sep = ';';
    stream >> name >> sep;
    int t = 0;
    stream >> t >> sep;
    type = static_cast<Type>(t);
    stream >> score >> sep;
    size_t rsize = 0;
    stream >> rsize >> sep;
    for (size_t i = 0; i < rsize; i++)
    {
        int t = 0;
        stream >> t >> sep;
        Rigidbody* r = new Projectile(this, static_cast<Rigidbody::Type>(t));
        rigidbodies.push_back(r);
        vector3 loc;
        vector3 vel;

        stream >> loc.x >> sep;
        stream >> loc.y >> sep;
        stream >> loc.z >> sep;
        r->SetLocation(loc);
        stream >> vel.x >> sep;
        stream >> vel.y >> sep;
        stream >> vel.z >> sep;
        r->SetVelocity(vel);
        float rad = 0;
        stream >> rad >> sep;
        r->SetRadius(rad);
    }
    bool sc = false;
    stream >> sc >> sep;
    if (sc)
    {
        spacecraft = new Spacecraft();
        int t = 0;
        stream >> t >> sep;
        vector3 loc;
        vector3 vel;
        vector3 fvec;

        stream >> loc.x >> sep;
        stream >> loc.y >> sep;
        stream >> loc.z >> sep;
        spacecraft->SetLocation(loc);
        stream >> vel.x >> sep;
        stream >> vel.y >> sep;
        stream >> vel.z >> sep;
        spacecraft->SetVelocity(vel);
        float rad = 0;
        stream >> rad >> sep;
        spacecraft->SetRadius(rad);
        double cd = 0;
        stream >> cd >> sep;
        spacecraft->SetShotCooldown(cd);
        int l = 0;
        stream >> l >> sep;
        spacecraft->SetLifes(l);
        stream >> fvec.x >> sep;
        stream >> fvec.y >> sep;
        stream >> fvec.z >> sep;
        spacecraft->SetLocation(fvec);
    }
}

void Participant::RemoveRigidbody(Rigidbody * ridgidbody)
{
    for (std::vector<Rigidbody*>::iterator it = rigidbodies.begin(); it != rigidbodies.end(); ++it)
    {
        if ((*it) == ridgidbody)
        {
            rigidbodies.erase(it);
            return;
        }
    }
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

void Projectile::OnCollision(Rigidbody* other)
{
    if (other != nullptr)
    {
        if (other->GetType() != GetType())
        {
            if (other == owner->GetSpacecraft())
            {
                return;
            }
            if (other->GetType() == Asteroid)
            {
                owner->AddScore(SCORE_PER_ASTEROID_SHOT);
            }
            if (other->GetType() == Player)
            {
                owner->AddScore(SCORE_PER_PLAYER_SHOT);
            }
            if (GetType() == Asteroid)
            {
                Reset();
            }
            else
            {
            }
        }
    }
}