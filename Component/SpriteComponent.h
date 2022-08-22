#pragma once
#include "Component.h"
#include <SDL_image.h>
#include "Vector2.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent(class Entity* owner, int order = 100);

    void SetTexture(SDL_Texture* text);
    void SetTexture(SDL_Texture* text, SDL_Rect *part);
    SDL_Texture* GetTexture() const { return mTexture; }

    int mTexWidth;
    int mTexHeight;
    SDL_Rect mSrcRect;
    Vector2 mOffset;
    bool mFaceRight;

protected:
    SDL_Texture* mTexture;

};