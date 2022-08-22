#include "InputSystem.h"
#include "Game.h"
#include <SDL.h>

ButtonState KeyBoardState::GetKeyState(SDL_Scancode keyCode) const
{
    if (mPrevState[keyCode] == 0)
    {
        if (mCurrState[keyCode] == 0)
        { return ENone; }
        else
        { return EPressed; }
    }
    else
    {
        if (mCurrState[keyCode] == 0)
        { return EReleased; }
        else
        { return EHeld; }
    }
}

bool KeyBoardState::GetKeyValue(SDL_Scancode keyCode) const
{
    return mCurrState[keyCode] == 1;
}

ButtonState MouseState::GetButtonState(int button) const
{
    int mask = SDL_BUTTON(button);
    if ((mask & mPrevButtons) == 0)
    {
        if ((mask & mCurrButtons) == 0)
        { return ENone; }
        else
        { return EPressed; }
    }
    else
    {
        if ((mask & mCurrButtons) == 0)
        { return EReleased; }
        else
        { return EHeld; }
    }
}

bool MouseState::GetButtonValue(int button) const
{
    return (SDL_BUTTON(button) & mCurrButtons) == 1;
}

InputSystem::InputSystem(Game* game, int updateOrder)
    : System(game, updateOrder)
{
}

void InputSystem::Initialize()
{
    // Keyboard
    mState.KeyBoard.mCurrState = SDL_GetKeyboardState(NULL);
    memset(mState.KeyBoard.mPrevState, 0, SDL_NUM_SCANCODES);

    // Mouse
    mState.Mouse.mPrevButtons = 0;
    mState.Mouse.mCurrButtons = 0;

    // Hide the cursor
    // SDL_ShowCursor(SDL_FALSE);
}

void InputSystem::PreUpdate()
{
    memcpy(mState.KeyBoard.mPrevState, mState.KeyBoard.mCurrState, SDL_NUM_SCANCODES);

    mState.Mouse.mPrevButtons = mState.Mouse.mCurrButtons;
}

void InputSystem::Update(float deltaTime)
{
    PreUpdate();
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
       switch (event.type)
       {
        case SDL_QUIT:
            mGame->SetIsRunning(false);
            break;
        default:
            break;
       }
    }
    if (mState.KeyBoard.GetKeyState(SDL_SCANCODE_ESCAPE) == EReleased)
    {
        mGame->SetIsRunning(false);
    }
    
    int x = 0, y = 0;
    mState.Mouse.mCurrButtons = SDL_GetMouseState(&x, &y);
    mState.Mouse.mPosition.x = static_cast<float>(x);
    mState.Mouse.mPosition.y = static_cast<float>(y);

}