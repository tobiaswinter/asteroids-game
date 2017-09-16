#include "Rigitbody.h"

std::vector<Rigitbody*> Rigitbody::physicsObjects = std::vector<Rigitbody*>();

Rigitbody::Rigitbody()
{
    physicsObjects.push_back(this);
}

Rigitbody::~Rigitbody()
{
    for (std::vector<Rigitbody*>::iterator it = physicsObjects.begin(); it != physicsObjects.end(); ++it)
    {
        if (this == *it)
        {
            physicsObjects.erase(it);
        }
    }
}

void Rigitbody::UpdatePhysics(double deltaTime)
{
}
