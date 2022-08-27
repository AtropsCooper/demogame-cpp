#include "ArrowPrefab.h"
#include "Constants.h"
#include "TransientComponent.h"

ArrowPrefab::ArrowPrefab(class Game *game, Vector2 position, float life)
    : MovablePrefab(game, position)
{
    mAnimComponent->SetTexture(mGame->GetTexture("dungeon"), &SPRITE_ARROW);
    MoveComponent *arrowMoveComponent = new MoveComponent(this, 10);
    new TransientComponent(this, 1, life, Entity::EDead);
}