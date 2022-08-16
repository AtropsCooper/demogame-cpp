#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(class Entity* owner, int drawOrder)
    : Component(owner)
{
    mDrawOrder = drawOrder;
}

SpriteComponent::~SpriteComponent()
{
  //  if (mTexture != nullptr)
    //{
     //   SDL_DestroyTexture(mTexture);
    //}
}

void SpriteComponent::SetTexture(SDL_Texture* text)
{
    mTexture = text;
    SDL_QueryTexture(text, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
