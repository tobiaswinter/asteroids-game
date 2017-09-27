#include "Projectile.h"

Projectile::Projectile(Participant* owner, Type type) : Rigidbody(type), owner(owner)
{
}


Projectile::~Projectile()
{
}
