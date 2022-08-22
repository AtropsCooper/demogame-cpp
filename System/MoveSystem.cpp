#include "MoveSystem.h"
#include "Entity.h"
#include "AnimComponent.h"

void MoveSystem::FetchComponents()
{
    DetectComponent<MoveComponent>(&mMoveComponents);
}

void MoveSystem::Update(float deltaTime)
{
    // Move Every Entity
    for (auto c : mMoveComponents)
    {
        c->GetOwner()->mPosition += c->mVelocity * deltaTime;
        AnimComponent* anim = c->GetOwner()->GetComponent<AnimComponent>();
        if (anim != nullptr)
        {
            if (c->mVelocity != Vector2::Zero)
            {
                anim->SetState(AnimComponent::EMoving);
            }
            else
            {
                anim->SetState(AnimComponent::EIdle);
            }
        }
    }
}