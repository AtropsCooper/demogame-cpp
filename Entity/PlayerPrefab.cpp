#include "PlayerPrefab.h"
#include "StatusComponent.h"
#include "Constants.h"

PlayerPrefab::PlayerPrefab(Game* game, Vector2 position)
    : MovablePrefab(game, position)
{
    mAnimComponent->mOffset.y = 0.8f;
    mAnimComponent->mUpdateOrder = 300;
    SDL_Rect idle = PLAYER_IDLE_ANIM;
    SDL_Rect run = PLAYER_RUN_ANIM;
    SDL_Rect hit = PLAYER_HIT_ANIM;
    mAnimComponent->SetAnimSprites(AnimComponent::EIdle, &idle, PLAYER_IDLE_LENGTH, ANIM_FRAMERATE);
    mAnimComponent->SetAnimSprites(AnimComponent::EMoving, &run, PLAYER_RUN_LENGTH, ANIM_FRAMERATE);
    mAnimComponent->SetAnimSprites(AnimComponent::EHit, &hit, PLAYER_HIT_LENGTH, ANIM_FRAMERATE);
    StatusComponent *status = new StatusComponent(this, 19);
    status->mHealth = HEALTH_PLAYER;
}
