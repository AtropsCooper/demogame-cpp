#include "AISystem.h"
#include "Entity.h"
#include "AIComponent.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "HittedComponent.h"
#include "MyMath.h"

void AISystem::FetchComponents()
{
    DetectComponent<AIComponent>(&mAIs);
}

void AISystem::Update(float deltaTime)
{
    if (mPlayer != nullptr)
    {
        for (auto ai : mAIs)
        {
            auto entity = ai->GetOwner();
            auto movecomponent = entity->GetComponent<MoveComponent>();
            Vector2 direction = mPlayer->mPosition - entity->mPosition;
            if (direction.Length() < 16.0f && 
                (entity->GetComponent<HittedComponent>() == nullptr ||
                 entity == mGame->mBoss))
            {
                if (ai->mPattern == AIComponent::EHelix)
                {
                    direction = { (direction.x + direction.y) / MyMath::Sqrt2, (direction.y - direction.x) / MyMath::Sqrt2 };
                }
                else if (ai->mPattern ==AIComponent::ERevHelix)
                {
                    direction = { (direction.x - direction.y) / MyMath::Sqrt2, (direction.x + direction.y) / MyMath::Sqrt2 };
                }
                direction.Normalize();
                movecomponent->mVelocity = direction * ai->mSpeed;
                entity->GetComponent<SpriteComponent>()->mFaceRight = direction.x > 0.0f;
            }
            else
            {
                movecomponent->mVelocity = Vector2::Zero;
            }

        }
    }
}