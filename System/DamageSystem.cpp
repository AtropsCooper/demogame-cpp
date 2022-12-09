#include "DamageSystem.h"
#include "Game.h"
#include "Entity.h"
#include "DamageComponent.h"
#include "StatusComponent.h"
#include "AnimComponent.h"

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
            if (msg.second->GetComponent<DamageComponent>() != nullptr &&
                msg.first->GetComponent<StatusComponent>() != nullptr)
            {
                mColliders.emplace_back(std::make_pair(msg.first, msg.second));
            }
            else if (msg.first->GetComponent<DamageComponent>() != nullptr &&
                     msg.second->GetComponent<StatusComponent>() != nullptr)
            {
                mColliders.emplace_back(std::make_pair(msg.second, msg.first));
            }
        }
    }
}

void DamageSystem::Update(float deltaTime)
{
    for (auto collidePairs : mColliders)
    {
        auto arrow = collidePairs.second;
        auto enemy = collidePairs.first;
        float damage = arrow->GetComponent<DamageComponent>()->mDamage;
        auto enemyState = enemy->GetComponent<StatusComponent>();
        
        arrow->SetState(Entity::EDead);

        auto enemyAnimComp = enemy->GetComponent<AnimComponent>();
        if (enemy->GetState() == Entity::EActive &&
            enemyAnimComp != nullptr &&
            enemyAnimComp->GetState() != AnimComponent::EHit)
        {
            enemyState->mHealth -= damage;
            if (enemyState->mHealth <= 0.0f)
            {
                enemyState->GetOwner()->SetState(Entity::EDead);
                SDL_Log("Dead!");
            }
        }

    }
}