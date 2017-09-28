#pragma once
#include "Rigidbody.h"
#include "Projectile.h"

class Spacecraft : public Rigidbody
{
private:
    unsigned int lifes = LIFES;
    double invulnerableCounter = 0;
    vector3 forwardVector;
public:
    Spacecraft();
    unsigned int GetLifes() { return lifes; }
    void OnCollision(Rigidbody* other) override;

    void Update(double deltaTime);
    bool IsVulnerable() { return invulnerableCounter <= 0; }

    Projectile* Shoot(Participant* owner);
};