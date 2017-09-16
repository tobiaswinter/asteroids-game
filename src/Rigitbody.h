#pragma once
#include "Math.h"
#include <vector>

class Rigitbody
{
private:
    static std::vector<Rigitbody*> physicsObjects;

    float circleRadius;
    vector3 location;
    vector3 velocity;

public:

    Rigitbody();
    virtual ~Rigitbody();

    virtual void OnCollision(Rigitbody& other) = 0;

    static void UpdatePhysics(double deltaTime);

};

