#pragma once
#include "System.h"
#include <SDL.h>
#include <vector>

class CollisionSystem : public System
{
public:
    CollisionSystem(class Game *game, int order);

    void FetchComponents() override;
    void Update(float deltaTime) override;

private:
    bool Collides(class Entity* first, class CollisionBoxComponent *FCB , class Entity* second, class CollisionBoxComponent *SCB);
    bool Contains(SDL_FRect &box, float pointX, float pointY);
    std::vector<class CollisionBoxComponent *> mCollisionBoxes;
    std::vector<class CollisionBoxComponent *> mBoxesNearby;
};