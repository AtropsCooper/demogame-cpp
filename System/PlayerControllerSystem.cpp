#include "PlayerControllerSystem.h"
#include "InputSystem.h"
#include "MoveComponent.h"
#include "Vector2.h"
#include "Game.h"
#include "Entity.h"
#include "SpriteComponent.h"

void PlayerControllerSystem::SetPlayer(Entity* player)
{
    mPlayer = player;
    mPMC = mPlayer->GetComponent<MoveComponent>();
}

void PlayerControllerSystem::Update(float deltaTime)
{
    const InputState *state = mGame->GetInputState();
    if (mPMC != nullptr)
    {
        Vector2 movement;
        movement.x = (state->KeyBoard.GetKeyValue(SDL_SCANCODE_D) - state->KeyBoard.GetKeyValue(SDL_SCANCODE_A));
        movement.y = (state->KeyBoard.GetKeyValue(SDL_SCANCODE_W) - state->KeyBoard.GetKeyValue(SDL_SCANCODE_S));
        if (movement.x !=0 && movement.y != 0)
        {
            movement.Normalize();
        }
        movement *= 2.0f;
        mPMC->mVelocity = movement;
    }
    else
    {
        mPMC = mPlayer->GetComponent<MoveComponent>();
    }
    
    if (state->Mouse.GetMousePosition().x >= mPlayer->mPosition.x)
    {
        mPlayer->GetComponent<SpriteComponent>()->mFaceRight = true;
    }
    else
    {
        mPlayer->GetComponent<SpriteComponent>()->mFaceRight = false;
    }
}