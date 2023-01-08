#pragma once
#include "MovablePrefab.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionBoxComponent.h"
#include "HostilityComponent.h"

class ArrowPrefab : public Entity
{
public:
    explicit ArrowPrefab(class Game *game, Vector2 position, float life);

private:
    class SpriteComponent *mSpriteComponent;
    class MoveComponent *mMoveComponent;
    class CollisionBoxComponent *mCollisionBox;
    class HostilityComponent *mHostilityComponent;
};
