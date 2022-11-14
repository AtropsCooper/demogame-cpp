#include "DamageSystem.h"
#include "Game.h"
#include "Entity.h"
#include "DamageComponent.h"
#include "StatusComponent.h"


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
        float damage = collidePairs.second->GetComponent<DamageComponent>()->mDamage;
        auto injured = collidePairs.first->GetComponent<StatusComponent>();
        injured->mHealth -= damage;
        collidePairs.second->SetState(Entity::EDead);
        if (injured->mHealth <= 0.0f)
        {
            injured->GetOwner()->SetState(Entity::EDead);
            SDL_Log("Dead!");
        }
    }
}