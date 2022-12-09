#include "TransientSystem.h"
#include "TransientComponent.h"

void TransientSystem::FetchComponents()
{
    DetectComponent<TransientComponent>(&mTransientComponents);
}

void TransientSystem::Update(float deltaTime)
{
    for (auto c : mTransientComponents)
    {
        if (c->mLifespan <= 0.0f)
        {
            c->Bury();
        }
        c->mLifespan -= deltaTime;
    }
}