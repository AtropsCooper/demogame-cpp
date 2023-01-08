#include "AnimationSystem.h"
#include "MyMath.h"

AnimationSystem::AnimationSystem(class Game *game, int updateOrder)
    : System(game, updateOrder)
{
}

void AnimationSystem::FetchComponents()
{
    DetectComponent<AnimComponent>(&mAnimComponents);
}

void AnimationSystem::Update(float deltaTime)
{
    for (auto c : mAnimComponents)
    {
        c->mTime += deltaTime;
        SDL_Rect firstSprite = c->mAnims[c->GetState()].firstSprite;
        float frameRate = c->mAnims[c->GetState()].frameRate;
        int sprites = c->mAnims[c->GetState()].sprites;

        c->mSrcRect.x = firstSprite.x + firstSprite.w * static_cast<int>(MyMath::Fmod((c->mTime / frameRate), static_cast<float>(sprites)));
        c->mSrcRect.y = firstSprite.y;
        c->mSrcRect.w = firstSprite.w;
        c->mSrcRect.h = firstSprite.h;
    }
}