#pragma once
#include "Math.h"
#include <vector>
#include "GameSettings.h"

class Rigidbody
{
private:
    static std::vector<Rigidbody*> physicsObjects;

protected:
    float circleRadius;
    vector3 location;
    vector3 velocity;

    bool hit = false;
    Rigidbody* otherHit;

    void MarkHit(Rigidbody& other);
    void Update(double deltaTime);

public:

    Rigidbody();
    virtual ~Rigidbody();

    virtual void OnCollision(Rigidbody& other) = 0;

    static void UpdatePhysics(double deltaTime);
};

class Spacecraft : public Rigidbody
{
private:
    unsigned int lifes = LIFES;
public:
    Spacecraft();
    unsigned int GetLifes() { return lifes; }
    void OnCollision(Rigidbody& other) override;
};

