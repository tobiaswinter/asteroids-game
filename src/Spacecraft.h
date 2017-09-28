#pragma once
#include "Rigidbody.h"
#include "Projectile.h"

class Spacecraft : public Rigidbody
{
private:
    unsigned int lifes = LIFES;
    double invulnerableCounter = 0;
    double shotCooldown = 0;
    vector3 forwardVector;
public:
    Spacecraft();
    unsigned int GetLifes() { return lifes; }
    void SetLifes(unsigned int l) { lifes = l; }
    void OnCollision(Rigidbody* other) override;

    void Update(double deltaTime);
    bool IsVulnerable() { return invulnerableCounter <= 0; }

    Projectile* Shoot(Participant* owner);

    vector3 GetForwardVector() { return forwardVector; }
    void SetForwardVector(vector3 forward) { forwardVector = forward; }
    double GetInvulnerableCounter() { return invulnerableCounter; }
    void SetInvulnerableCounter(double time) { invulnerableCounter = time; }
    double GetShotCooldown() { return shotCooldown; }
    void SetShotCooldown(double cooldown) { shotCooldown = cooldown; }
};