#pragma once
#include "Math.h"
#include <vector>
#include "GameSettings.h"

class Rigidbody
{
public:
    enum Type {
        Player = 0,
        Asteroid = 1,
        Bullet = 2
    };
private:
    static std::vector<Rigidbody*> physicsObjects;

protected:
    Type type;
    float radius;
    vector3 location;
    vector3 velocity;

    bool hit = false;
    Rigidbody* otherHit;

    void MarkHit(Rigidbody& other);
    void Update(double deltaTime);

public:

    Rigidbody(Type type);
    virtual ~Rigidbody();

    virtual void OnCollision(Rigidbody* other) = 0;

    static void UpdatePhysics(double deltaTime);

    vector3 GetLocation() { return location; }
    void SetLocation(vector3 newLocation) { location = newLocation; }
    vector3 GetVelocity() { return velocity; }
    void SetVelocity(vector3 newVelocity) { velocity = newVelocity; }
    Type GetType() { return type; }
};

class Spacecraft : public Rigidbody
{
private:
    unsigned int lifes = LIFES;
    double invulnerableCounter = 0;
public:
    Spacecraft();
    unsigned int GetLifes() { return lifes; }
    void OnCollision(Rigidbody* other) override;

    void Update(double deltaTime);
    bool IsVulnerable() { return invulnerableCounter <= 0; }
};

