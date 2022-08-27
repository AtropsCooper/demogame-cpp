#include "SkeletonPrefab.h"
#include "StatusComponent.h"
#include "Constants.h"

SkeletonPrefab::SkeletonPrefab(Game* game, Vector2 position)
    : MovablePrefab(game, position)
{
    mAnimComponent->SetAnimSprites(AnimComponent::EIdle, &SKELET_IDLE_ANIM, SKELET_IDLE_LENGTH, ANIM_FRAMERATE);
    mAnimComponent->SetAnimSprites(AnimComponent::EMoving, &SKELET_RUN_ANIM, SKELET_RUN_LENGTH, ANIM_FRAMERATE);
    StatusComponent *status = new StatusComponent(this, 19);
    status->mHealth = HEALTH_SKELET;
}