#include "PlayerPrefab.h"
#include "StatusComponent.h"
#include "Constants.h"

PlayerPrefab::PlayerPrefab(Game* game, Vector2 position)
    : MovablePrefab(game, position)
{
    mAnimComponent->mOffset.y = 0.8f;
    mAnimComponent->mUpdateOrder = 300;
    mAnimComponent->SetAnimSprites(AnimComponent::EIdle, &PLAYER_IDLE_ANIM, PLAYER_IDLE_LENGTH, ANIM_FRAMERATE);
    mAnimComponent->SetAnimSprites(AnimComponent::EMoving, &PLAYER_RUN_ANIM, PLAYER_RUN_LENGTH, ANIM_FRAMERATE);
    mAnimComponent->SetAnimSprites(AnimComponent::EHit, &PLAYER_HIT_ANIM, PLAYER_HIT_LENGTH, ANIM_FRAMERATE);
    //StatusComponent *status = new StatusComponent(this, 19);
    //status->mHealth = HEALTH_PLAYER;
}
