#include "SkeletonPrefab.h"
#include "StatusComponent.h"
#include "Constants.h"

SkeletonPrefab::SkeletonPrefab(Game* game, Vector2 position)
    : MovablePrefab(game, position)
{
    SDL_Rect idle = SKELET_IDLE_ANIM;
    SDL_Rect run = SKELET_RUN_ANIM;
    mAnimComponent->SetAnimSprites(AnimComponent::EIdle, &idle, SKELET_IDLE_LENGTH, ANIM_FRAMERATE);
    mAnimComponent->SetAnimSprites(AnimComponent::EMoving, &run, SKELET_RUN_LENGTH, ANIM_FRAMERATE);
    StatusComponent *status = new StatusComponent(this, 19);
    status->mHealth = HEALTH_SKELET;
}