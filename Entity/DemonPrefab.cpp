#include "DemonPrefab.h"
#include "StatusComponent.h"
#include "AIComponent.h"
#include "Constants.h"

DemonPrefab::DemonPrefab(Game* game, Vector2 position)
    : MovablePrefab(game, position)
{
    mCollisionBox->mWidth = 1.0f;
    mCollisionBox->mHeight = 1.0f;
    mAnimComponent->SetAnimSprites(AnimComponent::EIdle, &DEMON_IDLE_ANIM, DEMON_IDLE_LENGTH, ANIM_FRAMERATE);
    mAnimComponent->SetAnimSprites(AnimComponent::EMoving, &DEMON_RUN_ANIM, DEMON_RUN_LENGTH, ANIM_FRAMERATE);
    mAnimComponent->SetAnimSprites(AnimComponent::EHit, &DEMON_HIT_ANIM, DEMON_HIT_LENGTH, ANIM_FRAMERATE / 2);
    StatusComponent *status = new StatusComponent(this, 19);
    status->mHealth = HEALTH_DEMON;
    mHostilityComponent = new HostilityComponent(this, HostilityComponent::EEnemy);
    new AIComponent(this, DEMON_MOVE_SPEED, AIComponent::EHelix);
}