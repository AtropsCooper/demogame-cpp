#include "AnimComponent.h"

AnimComponent::AnimComponent(class Entity *owner, int order)
    : SpriteComponent(owner, order)
    , mTime(0)
    , mState(EIdle)
{
}

void AnimComponent::SetAnimSprites(AnimComponent::State state,
                                   const SDL_Rect *firstSprite, int sprites, float frameRate)
{
    mAnims[state].firstSprite = *firstSprite;
    mTexWidth = firstSprite->w;
    mTexHeight = firstSprite->h;
    mAnims[state].sprites = sprites;
    mAnims[state].frameRate = frameRate;
    if (mSrcRect.w == 0)
    {
        mSrcRect = *firstSprite;
    }
}

void AnimComponent::SetState(State state)
{
    if(mState != state)
    {
        mState = state;
        mTime = 0.0f;
    }
}