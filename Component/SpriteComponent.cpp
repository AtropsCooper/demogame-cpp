#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(class Entity *owner, int drawOrder)
    : Component(owner, drawOrder), mSrcRect({0, 0, 0, 0}), mOffset(0.0f, 0.0f), mFaceRight(true)
{
}

void SpriteComponent::SetTexture(SDL_Texture *text)
{
    mTexture = text;
    SDL_QueryTexture(text, nullptr, nullptr, &mTexWidth, &mTexHeight);
    mSrcRect.x = 0;
    mSrcRect.y = 0;
    mSrcRect.w = mTexWidth;
    mSrcRect.h = mTexHeight;
}

void SpriteComponent::SetTexture(SDL_Texture *text, const SDL_Rect *part)
{
    mTexture = text;
    mSrcRect = *part;
    mTexHeight = mSrcRect.h;
    mTexWidth = mSrcRect.w;
}