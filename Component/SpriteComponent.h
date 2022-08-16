#pragma once
#include "Component.h"
#include <SDL_image.h>

class SpriteComponent : public Component
{
public:
    SpriteComponent(class Entity* owner, int order);
    ~SpriteComponent();

    void SetTexture(SDL_Texture* text);
    SDL_Texture* GetTexture() const { return mTexture; }

    int mTexWidth;
    int mTexHeight;
    int mDrawOrder;

private:
    SDL_Texture* mTexture;

};