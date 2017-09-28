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
    if (invulnerableCounter < 0)
    {
        invulnerableCounter = 0;
    }
}

Projectile* Spacecraft::Shoot(Participant* owner)
{
    Projectile* p = new Projectile(owner, Bullet);
    vector3 location = this->GetLocation() + (forwardVector * float(SPACECRAFT_RADIUS + BULLET_RADIUS));
    p->SetLocation(location);
    p->SetVelocity(forwardVector * (float)BULLET_SPEED);
    return p;
}