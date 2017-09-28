#include "Projectile.h"
#include <random>
#include <iostream>

Projectile::Projectile(Participant* owner, Type type) : Rigidbody(type), owner(owner)
{
    Reset();
}


Projectile::~Projectile()
{
}


void Projectile::Reset()
{
    if (type == Asteroid)
    {
        radius = ASTEROID_RADIUS;
        if (velocity.x < 0)
        {
            location.x = (ARENA_WIDTH / 2) + 20;
        }
        else
        {
            location.x = -((ARENA_WIDTH / 2) + 20);
        }
        if (velocity.y < 0)
        {
            location.y = (ARENA_HEIGHT / 2) - 20;
        }
        else
        {
            location.y = -((ARENA_HEIGHT / 2) - 20);
        }
#if !IGNORE_Z_AXIS
        if (velocity.z < 0)
        {
            location.z = (ARENA_DEPTH / 2) - 20;
        }
        else
        {
            location.z = -((ARENA_DEPTH / 2) - 20);
        }
#endif
    }
    else if (type = Bullet)
    {
        radius = BULLET_RADIUS;
    }
}

void Projectile::OnCollision(Rigidbody* other)
{
    if (other == nullptr || other->GetType() != GetType())
    {
        Reset();
    }

}
