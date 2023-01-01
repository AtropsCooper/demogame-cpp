#include "DamageSystem.h"
#include "Game.h"
#include "Entity.h"
#include "DamageComponent.h"
#include "StatusComponent.h"
#include "HittedComponent.h"
#include "AnimComponent.h"
#include "HostilityComponent.h"
#include "DeadOnCollisionComponent.h"
#include "PlayerPrefab.h"
#include "SkeletonPrefab.h"

DamageSystem::DamageSystem(Game *game, int order)
    : System(game, order)
{

}

void DamageSystem::FetchComponents()
{
    mColliders.clear();
    auto messages = *(mGame->GetCollisionMessages());
    for (auto msg : messages)
    {
        if (msg.first->GetState() == Entity::EActive && msg.second->GetState() == Entity::EActive)
        {
            if (MyMath::Abs(msg.first->GetComponent<HostilityComponent>()->mHostility
                + msg.second->GetComponent<HostilityComponent>()->mHostility) != 2)
            {
                mColliders.emplace_back(std::make_pair(msg.first, msg.second));
            }
        }
    }
}

void DamageSystem::Update(float deltaTime)
{
    auto TakeDamage = [](Entity *attacker, Entity* sufferer)
    {
        float damage = attacker->GetComponent<DamageComponent>()->mDamage;
        auto suffererState = sufferer->GetComponent<StatusComponent>();
        if (sufferer->GetState() == Entity::EActive &&
            sufferer->GetComponent<HittedComponent>() == nullptr)
        {
            suffererState->mHealth -= damage;
            if (suffererState->mHealth <= 0.0f)
            {
                suffererState->GetOwner()->SetState(Entity::EDead);
            }
            else
            {
                new HittedComponent(sufferer, 2, 0.6f);
            }
        }
    };

    for (auto collidePairs : mColliders)
    {
        if (collidePairs.first->GetComponent<DamageComponent>() != nullptr &&
            collidePairs.second->GetComponent<StatusComponent>() != nullptr)
        {
            auto attacker = collidePairs.first;
            auto sufferer = collidePairs.second;
            TakeDamage(attacker, sufferer);
        }
        if (collidePairs.second->GetComponent<DamageComponent>() != nullptr &&
            collidePairs.first->GetComponent<StatusComponent>() != nullptr)
        {
            auto attacker = collidePairs.second;
            auto sufferer = collidePairs.first;
            TakeDamage(attacker, sufferer);
        }

        // Kill Entities with DeadOnCollisionComponent
        if (collidePairs.first->GetComponent<DeadOnCollisionComponent>() != nullptr)
        {
            collidePairs.first->SetState(Entity::EDead);
        }
        if (collidePairs.second->GetComponent<DeadOnCollisionComponent>() != nullptr)
        {
            collidePairs.second->SetState(Entity::EDead);
        }
    }
}