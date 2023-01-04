#include "GoblinPrefab.h"
#include "StatusComponent.h"
#include "Constants.h"

GoblinPrefab::GoblinPrefab(Game* game, Vector2 position)
    : MovablePrefab(game, position)
{
    mCollisionBox->mWidth = 1.0f;
    mCollisionBox->mHeight = 1.0f;
    mAnimComponent->SetAnimSprites(AnimComponent::EIdle, &GOBLIN_IDLE_ANIM, GOBLIN_IDLE_LENGTH, ANIM_FRAMERATE);
    mAnimComponent->SetAnimSprites(AnimComponent::EMoving, &GOBLIN_RUN_ANIM, GOBLIN_RUN_LENGTH, ANIM_FRAMERATE);
    mAnimComponent->SetAnimSprites(AnimComponent::EHit, &GOBLIN_HIT_ANIM, GOBLIN_HIT_LENGTH, ANIM_FRAMERATE / 2);
    StatusComponent *status = new StatusComponent(this, 19);
    status->mHealth = HEALTH_GOBLIN;
    mHostilityComponent = new HostilityComponent(this, HostilityComponent::EEnemy);
}