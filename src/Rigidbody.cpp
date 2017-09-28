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
    location = GetLocation() + (GetVelocity() * deltaTime);
}

void Rigidbody::UpdatePhysics(double deltaTime)
{
    for (std::vector<Rigidbody*>::iterator it = physicsObjects.begin(); it != physicsObjects.end(); ++it)
    {
        (*it)->Update(deltaTime);
    }

    for (std::vector<Rigidbody*>::iterator it = physicsObjects.begin(); it != physicsObjects.end(); ++it)
    {
        if ((*it)->GetLocation().x > ((ARENA_WIDTH / 2) + 20) ||
            (*it)->GetLocation().x < (-(ARENA_WIDTH / 2) - 20) ||
            (*it)->GetLocation().y >((ARENA_HEIGHT / 2) + 20) ||
            (*it)->GetLocation().y < (-(ARENA_HEIGHT / 2) - 20) ||
            (*it)->GetLocation().z >((ARENA_DEPTH / 2) + 20) ||
            (*it)->GetLocation().z < (-(ARENA_DEPTH / 2) - 20))
        {
            (*it)->OnCollision(nullptr);
        }
        for (std::vector<Rigidbody*>::iterator other = it + 1; other != physicsObjects.end(); ++other)
        {
            float minDistance = (*it)->radius + (*other)->radius;
            minDistance *= minDistance;
            float distance = ((*it)->GetLocation() - (*other)->GetLocation()).lengthSquared();
            if (minDistance > distance)
            {
                (*it)->OnCollision(*other);
                (*other)->OnCollision(*it);
            }
        }
    }
}
