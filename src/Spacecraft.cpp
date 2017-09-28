#include "Spacecraft.h"
#include <iostream>

Spacecraft::Spacecraft() : Rigidbody(Type::Player)
{
    radius = SPACECRAFT_RADIUS;
    invulnerableCounter = INVULNERABLE_ON_START;
}

void Spacecraft::OnCollision(Rigidbody* other)
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
    shotCooldown -= deltaTime;
    if (invulnerableCounter < 0)
    {
        invulnerableCounter = 0;
    }
    if (shotCooldown < 0)
    {
        shotCooldown = 0;
    }
}

Projectile* Spacecraft::Shoot(Participant* owner)
{
    if (shotCooldown <= 0)
    {
        Projectile* p = new Projectile(owner, Bullet);
        vector3 location = this->GetLocation() + (forwardVector * float(SPACECRAFT_RADIUS + BULLET_RADIUS));
        p->SetLocation(location);
        p->SetVelocity(forwardVector * (float)BULLET_SPEED);
        shotCooldown = SHOOT_COOLDOWN;
        return p;
    }
    return nullptr;
}