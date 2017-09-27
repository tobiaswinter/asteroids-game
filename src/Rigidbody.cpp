#include "Rigidbody.h"
#include <iostream>

std::vector<Rigidbody*> Rigidbody::physicsObjects = std::vector<Rigidbody*>();

void Rigidbody::MarkHit(Rigidbody & other)
{
    hit = true;
    otherHit = &other;
}

Rigidbody::Rigidbody(Type type) : type(type)
{
    physicsObjects.push_back(this);
}

Rigidbody::~Rigidbody()
{
    for (std::vector<Rigidbody*>::iterator it = physicsObjects.begin(); it != physicsObjects.end(); ++it)
    {
        if (this == *it)
        {
            physicsObjects.erase(it);
            return;
        }
    }
}

void Rigidbody::Update(double deltaTime)
{
    location = location + (velocity * deltaTime);
}

void Rigidbody::UpdatePhysics(double deltaTime)
{
    for (std::vector<Rigidbody*>::iterator it = physicsObjects.begin(); it != physicsObjects.end(); ++it)
    {
        (*it)->Update(deltaTime);
    }

    for (std::vector<Rigidbody*>::iterator it = physicsObjects.begin(); it != physicsObjects.end(); ++it)
    {
        for (std::vector<Rigidbody*>::iterator other = it + 1; other != physicsObjects.end(); ++other)
        {
            float minDistance = (*it)->radius + (*other)->radius;
            minDistance *= minDistance;
            float distance = ((*it)->GetLocation() - (*other)->GetLocation()).lengthSquared();
            if (minDistance > distance)
            {
                (*it)->OnCollision(**other);
                (*other)->OnCollision(**it);
            }
        }
    }
}

Spacecraft::Spacecraft() : Rigidbody(Type::Player)
{
    radius = SPACECRAFT_RADIUS;
    invulnerableCounter = INVULNERABLE_ON_START;

    //location =
    //{
    //    (float)(std::rand() % ARENA_WIDTH )- (ARENA_WIDTH / 2),
    //    (float)(std::rand() % ARENA_WIDTH) - (ARENA_WIDTH / 2),
    //    (float)(std::rand() % ARENA_WIDTH) - (ARENA_DEPTH / 2)
    //};
}

void Spacecraft::OnCollision(Rigidbody & other)
{
    if (IsVulnerable())
    {
        --lifes;
        std::cout << "Player was hit - " << lifes << " Lifes remaining" << std::endl;
        invulnerableCounter = INVULNERABLE_AFTER_HIT;
    }
}

void Spacecraft::Update(double deltaTime)
{
    invulnerableCounter -= deltaTime;
    if (invulnerableCounter < 0)
    {
        invulnerableCounter = 0;
    }
}
