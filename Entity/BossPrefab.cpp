#include "BossPrefab.h"
#include "StatusComponent.h"
#include "Constants.h"

BossPrefab::BossPrefab(Game* game, Vector2 position)
    : MovablePrefab(game, position)
{
    mCollisionBox->mWidth = 1.0f;
    mCollisionBox->mHeight = 1.0f;
    mAnimComponent->SetAnimSprites(AnimComponent::EIdle, &BOSS_IDLE_ANIM, BOSS_IDLE_LENGTH, ANIM_FRAMERATE);
    mAnimComponent->SetAnimSprites(AnimComponent::EMoving, &BOSS_RUN_ANIM, BOSS_RUN_LENGTH, ANIM_FRAMERATE);
    mAnimComponent->SetAnimSprites(AnimComponent::EHit, &BOSS_HIT_ANIM, BOSS_HIT_LENGTH, ANIM_FRAMERATE / 2);
    StatusComponent *status = new StatusComponent(this, 19);
    status->mHealth = HEALTH_BOSS;
    mHostilityComponent = new HostilityComponent(this, HostilityComponent::EEnemy);
}