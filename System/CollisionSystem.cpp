#include "CollisionSystem.h"
#include "DrawSystem.h"
#include "CollisionBoxComponent.h"
#include "MoveComponent.h"
#include "Entity.h"
#include "Game.h"
#include "MyMath.h"

CollisionSystem::CollisionSystem(Game *game, int order)
    : System(game, order)
{

}

void CollisionSystem::FetchComponents()
{
    DetectComponent<CollisionBoxComponent>(&mCollisionBoxes);
    // Compute only for nearby entities
    mBoxesNearby.clear();
    auto player = mGame->mPlayer;
    auto drawSys = mGame->GetDrawSystem();
    if (player == nullptr || drawSys == nullptr)
    {
        return;
    }
    for (auto box : mCollisionBoxes)
    {
        auto entity = box->GetOwner();

        if (entity != nullptr && (entity->mPosition - player->mPosition).Length() < 15.0f)
        {
            mBoxesNearby.emplace_back(box);
        }  
    }
}

void CollisionSystem::Update(float deltaTime)
{
    if (mBoxesNearby.size() < 2)
    {
        return;
    }
    for (auto first = mBoxesNearby.begin();
         first != mBoxesNearby.end() - 1;
         first++)
    {
        for (auto second = first + 1;
                second != mBoxesNearby.end();
                second++)
        {
            Entity *firstEntity = (*first)->GetOwner();
            Entity *secondEntity = (*second)->GetOwner();
            if(Collides(firstEntity, *first, secondEntity, *second))
            {
                mGame->CollisionMessage(firstEntity, secondEntity);
            }
        }
    }
}

bool CollisionSystem::Collides(Entity* first, CollisionBoxComponent *FCB , Entity* second, CollisionBoxComponent *SCB)
{
    MoveComponent *MC = first->GetComponent<MoveComponent>();
    MoveComponent *SMC = second->GetComponent<MoveComponent>();
    Vector2 firstPos(first->mPosition.x + FCB->mOffset.x - FCB->mWidth * 0.5f, first->mPosition.y + FCB->mOffset.y + FCB->mHeight * 0.5f);
    Vector2 secondPos(second->mPosition.x + SCB->mOffset.x - SCB->mWidth * 0.5f, second->mPosition.y + SCB->mOffset.y + SCB->mHeight * 0.5f);
    
    SDL_FRect fstBox = {firstPos.x, firstPos.y, FCB->mWidth, FCB->mHeight};
    SDL_FRect secBox = {secondPos.x, secondPos.y, SCB->mWidth, SCB->mHeight};
    if (Contains(secBox, firstPos.x, firstPos.y) || 
        Contains(secBox, firstPos.x + FCB->mWidth, firstPos.y) ||
        Contains(secBox, firstPos.x, firstPos.y - FCB->mHeight) || 
        Contains(secBox, firstPos.x + FCB->mWidth, firstPos.y - FCB->mHeight) ||
        Contains(fstBox, secondPos.x, secondPos.y) || 
        Contains(fstBox, secondPos.x + SCB->mWidth, secondPos.y) ||
        Contains(fstBox, secondPos.x, secondPos.y - SCB->mHeight) || 
        Contains(fstBox, secondPos.x + SCB->mWidth, secondPos.y - SCB->mHeight)) 
    {
        return true;
    }
    else
    {
        return false;
    }
 
}

bool CollisionSystem::Contains(SDL_FRect &box, float pointX, float pointY)
{
    if (pointX > box.x && pointX < box.x + box.h && pointY < box.y && pointY > box.y - box.h)
    {
        return true;
    }
    else
    {
        return false;
    }
}