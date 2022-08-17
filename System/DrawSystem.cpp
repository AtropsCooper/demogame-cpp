#include "DrawSystem.h"
#include "SpriteComponent.h"
#include "Entity.h"
#include <SDL_image.h>
#include "Game.h"


DrawSystem::DrawSystem(class Game* game, int updateOrder, SDL_Renderer* renderer)
    : System(game, updateOrder)
    , mRenderer(renderer)
{
}

DrawSystem::~DrawSystem()
{
    for (auto sprite : mSprites)
    {
        delete sprite;
    }
    mSprites.clear();
}

void DrawSystem::FetchComponents()
{
    DetectComponent<SpriteComponent>(&mSprites);
}

void DrawSystem::Draw() const
{
    for (auto sprite : mSprites)
    {
        auto owner = sprite->GetOwner();
        SDL_Rect imageRect = sprite->srcRect;
        SDL_Rect dstRect;
        dstRect.w = static_cast<int>(sprite->mTexWidth * owner->mScale);
        dstRect.h = static_cast<int>(sprite->mTexHeight * owner->mScale);
        dstRect.x = static_cast<int>(owner->mPosition.x - dstRect.w / 2 + sprite->mOffset.x);
        dstRect.y = static_cast<int>(owner->mPosition.y - dstRect.h / 2 + sprite->mOffset.y);

        
        SDL_RenderCopyEx(mRenderer, sprite->GetTexture(), 
                        &imageRect, &dstRect, -MyMath::ToDegrees(owner->mRotation), nullptr, SDL_FLIP_NONE);
    }
}

void DrawSystem::AddSprite(class SpriteComponent* sprite)
{
    int myOrder = sprite->mDrawOrder;
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); iter++)
    {
        if (myOrder < (*iter)->mDrawOrder)
        {
            break;
        }
    }
    mSprites.insert(iter, sprite);
}

void DrawSystem::RemoveSprite(class SpriteComponent* sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    if (iter != mSprites.end())
    {
        mSprites.erase(iter);
    }
}