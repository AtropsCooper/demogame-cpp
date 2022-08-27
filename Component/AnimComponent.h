#pragma once
#include "SpriteComponent.h"

class AnimComponent : public SpriteComponent
{
public:
    enum State
    {
        EIdle = 0,
        EMoving = 1,
        EHit = 2
    };
    struct Anim
    {
        SDL_Rect firstSprite;
        int sprites;
        float frameRate;
    };

    AnimComponent(class Entity* owner, int order);
    void SetAnimSprites(AnimComponent::State state, const SDL_Rect *firstSprite, int sprites, float frameRate);
    void SetState(State state);
    State GetState() const { return mState; }


    float mTime;
    Anim mAnims[3];
protected:
    State mState;
};