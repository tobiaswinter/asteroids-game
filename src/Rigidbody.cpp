#include "Rigidbody.h"
#include <iostream>

std::vector<Rigidbody*> Rigidbody::physicsObjects = std::vector<Rigidbody*>();

void Rigidbody::MarkHit(Rigidbody & other)
{
    hit = true;
    otherHit = &other;
}

Rigidbody::Rigidbody()
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
        }
    }
}

void Rigidbody::Update(double deltaTime)
{
    hit = false;
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
            float minDistance = (*it)->circleRadius + (*other)->circleRadius;
            minDistance *= minDistance;
            float distance = ((*it)->location - (*other)->location).lengthSquared();
            if (minDistance > distance)
            {
                (*it)->OnCollision(**other);
                (*other)->OnCollision(**it);
            }
        }
    }
}

Spacecraft::Spacecraft() : Rigidbody()
{
    circleRadius = SPACECRAFT_RADIUS;
}

void Spacecraft::OnCollision(Rigidbody & other)
{
    --lifes;
}
