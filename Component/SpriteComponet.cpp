#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(class Entity* owner, int drawOrder)
    : Component(owner)
    , srcRect({0, 0, 0, 0})
    , mOffset(0.0f, 0.0f)
{
    mDrawOrder = drawOrder;
}

SpriteComponent::~SpriteComponent()
{

}

void SpriteComponent::SetTexture(SDL_Texture* text)
{
    mTexture = text;
    SDL_QueryTexture(text, nullptr, nullptr, &mTexWidth, &mTexHeight);
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = mTexWidth;
    srcRect.h = mTexHeight;
}

void SpriteComponent::SetTexture(SDL_Texture* text, SDL_Rect* part)
{
    mTexture = text;
    srcRect = *part;
    mTexHeight = srcRect.h;
    mTexWidth = srcRect.w;
}