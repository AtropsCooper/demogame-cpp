#include "DrawSystem.h"
#include "SpriteComponent.h"
#include "AnimComponent.h"
#include "Entity.h"
#include <SDL2/SDL_image.h>
#include "Game.h"
#include "InputSystem.h"
#include "MyMath.h"
#include "CollisionBoxComponent.h"

DrawSystem::DrawSystem(class Game *game, int updateOrder, SDL_Renderer *renderer)
    : System(game, updateOrder), mRenderer(renderer), mWindowWidth(1024), mWindowHeight(768), mCameraPos(0, 0), mPixelsPerGrid(32.0f)
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
            float diffX = (mousePos.x - mPlayer->mPosition.x) * 0.3f;
            float diffY = (mousePos.y - mPlayer->mPosition.y) * 0.3f;
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
        Entity *owner = sprite->GetOwner();
        const Vector2 &position = owner->mPosition;
        SDL_Rect imageRect = sprite->mSrcRect;
        SDL_Rect dstRect;

        float widthInGrid = sprite->mTexWidth * owner->mScale / 16.0f;
        float heightInGrid = sprite->mTexHeight * owner->mScale / 16.0f;

        if ((position.x + widthInGrid) > mCameraPos.x &&
            (position.y + heightInGrid) > mCameraPos.y &&
            (position.x - widthInGrid) < mCameraPos.x + mWindowWidth / mPixelsPerGrid &&
            (position.y - heightInGrid) < mCameraPos.y + mWindowHeight / mPixelsPerGrid)
        {
            dstRect.w = static_cast<int>(floor(widthInGrid * mPixelsPerGrid));
            dstRect.h = static_cast<int>(floor(heightInGrid * mPixelsPerGrid));
            Vector2 dstVec = WorldToScreen(position + sprite->mOffset);
            dstRect.x = static_cast<int>(floor(dstVec.x - 0.5f * dstRect.w));
            dstRect.y = static_cast<int>(floor(dstVec.y - 0.5f * dstRect.h));

            SDL_RendererFlip flip = sprite->mFaceRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
            SDL_RenderCopyEx(mRenderer, sprite->GetTexture(),
                             &imageRect, &dstRect, -MyMath::ToDegrees(owner->mRotation), nullptr, flip);

            // CollisionBoxComponent *CBC = owner->GetComponent<CollisionBoxComponent>();

            // if (CBC != nullptr)
            // {
            //     Vector2 cPos(position.x + CBC->mOffset.x - CBC->mWidth * 0.5f, position.y + CBC->mOffset.y + CBC->mHeight * 0.5f);
            //     Vector2 cSize(CBC->mWidth, CBC->mHeight);
            //     cPos = WorldToScreen(cPos);
            //     cSize = cSize * mPixelsPerGrid;
            //     SDL_Rect CollisionBox = {
            //         static_cast<int>(cPos.x),
            //         static_cast<int>(cPos.y),
            //         static_cast<int>(cSize.x),
            //         static_cast<int>(cSize.y)};
            //     SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
            //     SDL_RenderDrawRect(mRenderer, &CollisionBox);
            // }
        }
    }
}

void DrawSystem::SetPlayer(Entity *player)
{
    mPlayer = player;
}