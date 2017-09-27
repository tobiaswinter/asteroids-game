#pragma once
#include "Rigidbody.h"

class Participant;

class Projectile :
    public Rigidbody
{
private:
    Participant* owner;
public:
    Projectile(Participant* owner, Type type);
    ~Projectile();

    void OnCollision(Rigidbody& other) override;
};

