#pragma once
#include "Entity.h"
#include "Game.h"
#include "AnimComponent.h"
#include "MoveComponent.h"
#include "CollisionBoxComponent.h"
#include "HostilityComponent.h"
#include "DamageComponent.h"

class MovablePrefab : public Entity
{
public:
    MovablePrefab(class Game *game, Vector2 position);

protected:
    class AnimComponent *mAnimComponent;
    class MoveComponent *mMoveComponent;
    class CollisionBoxComponent *mCollisionBox;
    class HostilityComponent *mHostilityComponent;
    class DamageComponent *mDamageComponent;
};

inline MovablePrefab::MovablePrefab(class Game *game, Vector2 position)
    : Entity(game)
{
    mPosition = position;
    mAnimComponent = new AnimComponent(this, 200);
    mMoveComponent = new MoveComponent(this, 100);
    mAnimComponent->SetTexture(mGame->GetTexture("dungeon"));
    mCollisionBox = new CollisionBoxComponent(this, 100);
    mDamageComponent = new DamageComponent(this, 1.0f);
}
