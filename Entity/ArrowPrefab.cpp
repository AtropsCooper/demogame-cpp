#include "ArrowPrefab.h"
#include "Constants.h"
#include "TransientComponent.h"
#include "SuicideComponent.h"
#include "DamageComponent.h"
#include "Constants.h"

ArrowPrefab::ArrowPrefab(class Game *game, Vector2 position, float life)
    : Entity(game)
{
    mPosition = position;
    mSpriteComponent = new SpriteComponent(this, 200);
    mMoveComponent = new MoveComponent(this, 100);
    mCollisionBox = new CollisionBoxComponent(this, 100);
    mCollisionBox->mHeight = 0.6f;
    mCollisionBox->mWidth = 0.6f;
    mSpriteComponent->SetTexture(mGame->GetTexture("dungeon"), &SPRITE_ARROW);
    new SuicideComponent(this, 1, life);
    new DamageComponent(this, 10.0f);
}