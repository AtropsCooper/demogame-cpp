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
    for (auto itColBox1 = mBoxesNearby.begin();
         itColBox1 != mBoxesNearby.end() - 1;
         itColBox1++)
    {
        for (auto itColBox2 = itColBox1 + 1;
                itColBox2 != mBoxesNearby.end();
                itColBox2++)
        {
            Entity *entity1 = (*itColBox1)->GetOwner();
            Entity *entity2 = (*itColBox2)->GetOwner();
            MoveComponent *moveComponent1 = entity1->GetComponent<MoveComponent>();
            MoveComponent *moveComponent2 = entity2->GetComponent<MoveComponent>();
            if (moveComponent1 == nullptr && moveComponent2 == nullptr)
            {
                // Static entities will not collide
                continue;
            }
            if(Collides(*itColBox1, *itColBox2))
            {
                // if enemy vs. friend -> damage
                // else -> move velocity

                // Calculate the distance between the two entities on the x and y axes
                Vector2 d = (*itColBox1)->GetPosition() - (*itColBox2)->GetPosition();
                float dx = d.x;
                float dy = d.y;

                // Check if the collision is more horizontal or vertical
                if (abs(dx) > abs(dy)) {
                // The collision is more horizontal, so stop the movement on the x axis
                    if (moveComponent1 != nullptr && dx * moveComponent1->mVelocity.x < 0)
                    {
                        moveComponent1->mVelocity.x = 0;
                    }
                    if (moveComponent2 != nullptr && dx * moveComponent2->mVelocity.x > 0)
                    {
                        moveComponent2->mVelocity.x = 0;
                    }
                } else {
                // The collision is more vertical, so stop the movement on the y axis
                    if (moveComponent1 != nullptr && dy * moveComponent1->mVelocity.y < 0)
                    {
                        moveComponent1->mVelocity.y = 0;
                    }
                    if (moveComponent2 != nullptr && dy * moveComponent2->mVelocity.y > 0)
                    {
                        moveComponent2->mVelocity.y = 0;
                    }
                }
                mGame->CollisionMessage(entity1, entity2);
            }
        }
    }
}

bool CollisionSystem::Collides(CollisionBoxComponent *FCB, CollisionBoxComponent *SCB)
{
    Vector2 firstPos = FCB->GetPosition();
    Vector2 secondPos = SCB->GetPosition();
 
    SDL_FRect fstBox = {firstPos.x, firstPos.y, FCB->mWidth, FCB->mHeight};
    SDL_FRect seitColBox = {secondPos.x, secondPos.y, SCB->mWidth, SCB->mHeight};
    if (Contains(seitColBox, firstPos.x, firstPos.y) ||     
        Contains(seitColBox, firstPos.x + FCB->mWidth, firstPos.y) ||
        Contains(seitColBox, firstPos.x, firstPos.y - FCB->mHeight) || 
        Contains(seitColBox, firstPos.x + FCB->mWidth, firstPos.y - FCB->mHeight) ||
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