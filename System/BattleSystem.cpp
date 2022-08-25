#include "BattleSystem.h"
#include "SpriteComponent.h"
#include "Entity.h"

BattleSystem::BattleSystem(class Game* game, int order)
    : System(game, order)
{
}

void BattleSystem::FetchComponents()
{
    DetectComponent<AttackComponent>(&mAttackComponents);
}

void BattleSystem::Update(float deltaTime)
{
    for (auto a : mAttackComponents)
    {
        Entity* weapon = a->GetOwner();
        SpriteComponent* sprite = weapon->GetComponent<SpriteComponent>();
        if (sprite != nullptr)
        {
            if (MyMath::Abs(weapon->mRotation + MyMath::PiOver2) > MyMath::PiOver2)
            {
                weapon->GetComponent<SpriteComponent>()->mFaceRight = false;
            }
            else
            {
                weapon->GetComponent<SpriteComponent>()->mFaceRight = true;
            }
        }

        
        if (a->cooldown > 0.0f)
        {
            float rotation = a->rotation + 0.7f * MyMath::Sin(MyMath::Lerp(0.0f, MyMath::TwoPi, a->cooldown / a->interval));
            weapon->mRotation = rotation;
            sprite->mOffset.y = MyMath::Cos(rotation) * 0.87f;
            sprite->mOffset.x = -MyMath::Sin(rotation) * 0.87f;
            a->cooldown -= deltaTime;
        }
    }
}