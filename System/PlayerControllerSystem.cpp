#include "PlayerControllerSystem.h"
#include "InputSystem.h"
#include "MoveComponent.h"
#include "Vector2.h"
#include "Game.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "DrawSystem.h"
#include "AttackComponent.h"
#include "ArrowPrefab.h"
#include "Constants.h"

PlayerControllerSystem::~PlayerControllerSystem()
{
    if (mWeapon != nullptr)
    {
        mGame->RemoveEntity(mWeapon);
        delete mWeapon;
    }
}

void PlayerControllerSystem::SetPlayer(Entity *player)
{
    mPlayer = player;
    mPMC = mPlayer->GetComponent<MoveComponent>();
    SetupWeapon(0);
}

void PlayerControllerSystem::SetupWeapon(int playerJob)
{
    if (mWeapon == nullptr)
    {
        mWeapon = new Entity(mGame);
        mAttackComponent = new AttackComponent(mWeapon, 120);
        SpriteComponent *weaponSprite = new SpriteComponent(mWeapon, mPlayer->GetComponent<SpriteComponent>()->GetUpdateOrder() - 1);
        weaponSprite->SetTexture(mGame->GetTexture("dungeon"), &SRRITE_BOW);
        weaponSprite->mOffset.y = 1.17f;
        mWeapon->mPosition.x = mPlayer->mPosition.x;
        mWeapon->mPosition.y = mPlayer->mPosition.y + 0.5f;
        mWMC = new MoveComponent(mWeapon, 100);
    }
}

const Entity *PlayerControllerSystem::GetWeapon() const
{
    return mWeapon;
}

void PlayerControllerSystem::DestroyWeapon()
{
    if (mWeapon != nullptr)
    {
        mWeapon->SetState(Entity::EDead);
        mWeapon = nullptr;
    }
}

void PlayerControllerSystem::Update(float deltaTime)
{
    const InputState *state = mGame->GetInputState();
    if (mPMC != nullptr)
    {
        Vector2 movement;
        movement.x = (state->KeyBoard.GetKeyValue(SDL_SCANCODE_D) - state->KeyBoard.GetKeyValue(SDL_SCANCODE_A));
        movement.y = (state->KeyBoard.GetKeyValue(SDL_SCANCODE_W) - state->KeyBoard.GetKeyValue(SDL_SCANCODE_S));
        if (movement.x != 0 && movement.y != 0)
        {
            movement.Normalize();
        }
        movement *= PLAYER_MOVE_SPEED;
        mPMC->mVelocity = movement;
        if (mWMC != nullptr)
        {
            mWMC->mVelocity = movement;
        }
    }
    else
    {
        mPMC = mPlayer->GetComponent<MoveComponent>();
    }

    Vector2 mousePos = mGame->GetDrawSystem()->ScreenToWorld(state->Mouse.GetMousePosition());
    if (mousePos.x >= mPlayer->mPosition.x)
    {
        mPlayer->GetComponent<SpriteComponent>()->mFaceRight = true;
    }
    else
    {
        mPlayer->GetComponent<SpriteComponent>()->mFaceRight = false;
    }

    Vector2 orientation = Vector2::Normalize(mousePos - mWeapon->mPosition);
    mWeapon->GetComponent<SpriteComponent>()->mOffset = orientation * 0.87f;
    mWeapon->mRotation = MyMath::Atan2(orientation.y, orientation.x);

    mAttackComponent->cooldown -= deltaTime;

    if (state->Mouse.GetButtonValue(SDL_BUTTON_LEFT) == 1 && mAttackComponent->cooldown <= 0.0f)
    {
        Mix_PlayChannel(-1, mGame->GetChunk("arrow"), 0);
        mAttackComponent->cooldown = mAttackComponent->interval;
        // Would be varied by items
        float range = 12.0f;
        float speed = 20.0f;
        Vector2 arrowPos = mWeapon->mPosition + orientation * 0.87f;
        ArrowPrefab *arrow = new ArrowPrefab(mGame, arrowPos, range / speed);
        arrow->mRotation = mWeapon->mRotation - MyMath::PiOver2;
        arrow->GetComponent<MoveComponent>()->mVelocity = orientation * speed;
    }
}