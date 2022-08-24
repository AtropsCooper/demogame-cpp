#include "DrawSystem.h"
#include "SpriteComponent.h"
#include "AnimComponent.h"
#include "Entity.h"
#include <SDL_image.h>
#include "Game.h"
#include "InputSystem.h"
#include "MyMath.h"

DrawSystem::DrawSystem(class Game* game, int updateOrder, SDL_Renderer* renderer)
    : System(game, updateOrder)
    , mRenderer(renderer)
    , mWindowWidth(1024)
    , mWindowHeight(768)
    , mCameraPos(0, 0)
    , mPixelsPerGrid(32.0f)
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
    // Camera Follows player
    if (mPlayer != nullptr)
    {
        mCameraPos.x = mPlayer->mPosition.x - 0.5f * mWindowWidth / mPixelsPerGrid;
        mCameraPos.y = mPlayer->mPosition.y - 0.5f * mWindowHeight / mPixelsPerGrid; // Left Top Corner of the Window, By Grid
        const InputState *mInputState = mGame->GetInputState();
        if (mInputState != nullptr)
        {
           Vector2 mousePos = ScreenToWorld(mInputState->Mouse.GetMousePosition());
           float diffX = (mousePos.x - mPlayer->mPosition.x) * 0.4f;
           float diffY = (mousePos.y - mPlayer->mPosition.y) * 0.4f;
           if (diffX >= 0.0f)
           {
                mCameraPos.x += log(diffX + 1) * 0.5f;
           }
           else
           {
                mCameraPos.x -= log(MyMath::Abs(diffX - 1)) * 0.5f;
           }
            if (diffY >= 0.0f)
           {
                mCameraPos.y += log(diffY + 1) * 0.5f;
           }
           else
           {
                mCameraPos.y -= log(MyMath::Abs(diffY - 1)) * 0.5f;
           }
        } 

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