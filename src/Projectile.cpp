#include "Projectile.h"

Projectile::Projectile(Participant* owner, Type type) : Rigidbody(type), owner(owner)
{
    if (type == Asteroid)
    {
        radius = ASTEROID_RADIUS;
    }
}


Projectile::~Projectile()
{
}
