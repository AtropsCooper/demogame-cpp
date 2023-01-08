#include "MoveSystem.h"
#include "Entity.h"
#include "AnimComponent.h"
#include "HittedComponent.h"
#include "PlayerControllerSystem.h"

void MoveSystem::FetchComponents()
{
    DetectComponent<MoveComponent>(&mMoveComponents);
}

void MoveSystem::Update(float deltaTime)
{
    // Set weapon speed to match player
    auto player = mGame->mPlayer;
    auto weapon = mGame->GetPlayerControllerSystem()->GetWeapon();
    if (player != nullptr && weapon != nullptr)
    {
        weapon->GetComponent<MoveComponent>()->mVelocity = player->GetComponent<MoveComponent>()->mVelocity;
    }

    // Move Every Entity
    for (auto c : mMoveComponents)
    {
        c->GetOwner()->mPosition += c->mVelocity * deltaTime;
        AnimComponent *anim = c->GetOwner()->GetComponent<AnimComponent>();
        if (anim != nullptr && c->GetOwner()->GetComponent<HittedComponent>() == nullptr)
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