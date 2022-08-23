#include "DrawSystem.h"
#include "SpriteComponent.h"
#include "AnimComponent.h"
#include "Entity.h"
#include <SDL_image.h>
#include "Game.h"

DrawSystem::DrawSystem(class Game* game, int updateOrder, SDL_Renderer* renderer)
    : System(game, updateOrder)
    , mRenderer(renderer)
    , mWindowWidth(1024)
    , mWindowHeight(768)
    , mCameraPos(0, 0)
    , mPixelsPerGrid(32.0f)
    , mPlayer(nullptr)
{
}

Vector2 DrawSystem::WorldToScreen(const Vector2 &v) const
{
    return Vector2((v.x - mCameraPos.x) * mPixelsPerGrid, 
                    (v.y - mCameraPos.y) * -mPixelsPerGrid + mWindowHeight);
}
Vector2 DrawSystem::ScreenToWorld(const Vector2 &v) const
{
    return Vector2(v.x / mPixelsPerGrid + mCameraPos.x, 
                    (v.y - mWindowHeight) / -mPixelsPerGrid + mCameraPos.y);
}

void DrawSystem::FetchComponents()
{
    DetectComponent<SpriteComponent>(&mSprites);
}

void DrawSystem::Update(float deltaTime)
{
    // Camera Follows Player
    if (mPlayer != nullptr)
    {
        mCameraPos.x = mPlayer->mPosition.x - 0.5f * mWindowWidth / mPixelsPerGrid;
        mCameraPos.y = mPlayer->mPosition.y - 0.5f * mWindowHeight / mPixelsPerGrid; // Left Top Corner of the Window, By Grid
        // TODO: prevent of moving out of map
    }
}

void DrawSystem::Draw() const
{
    for (auto sprite : mSprites)
    {
        auto owner = sprite->GetOwner();
        SDL_Rect imageRect = sprite->mSrcRect;
        SDL_Rect dstRect;
        float widthInGrid = sprite->mTexWidth * owner->mScale / 16;
        float hightInGrid = sprite->mTexHeight * owner->mScale / 16;
        dstRect.w = static_cast<int>(widthInGrid * mPixelsPerGrid);
        dstRect.h = static_cast<int>(hightInGrid * mPixelsPerGrid);
        dstRect.x = static_cast<int>((owner->mPosition.x + sprite->mOffset.x - mCameraPos.x) * mPixelsPerGrid - 0.5f * dstRect.w);
        dstRect.y = static_cast<int>((owner->mPosition.y + sprite->mOffset.y - mCameraPos.y) * -mPixelsPerGrid + 0.5f * dstRect.h + mWindowHeight);
        SDL_Point center;
        center.x = owner->mPosition.x;
        center.y = owner->mPosition.y;
        SDL_RendererFlip flip = sprite->mFaceRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(mRenderer, sprite->GetTexture(), 
                        &imageRect, &dstRect, -MyMath::ToDegrees(owner->mRotation), &center, flip);
    }
}

void DrawSystem::SetPlayer(Entity* player)
{
    mPlayer = player;
}