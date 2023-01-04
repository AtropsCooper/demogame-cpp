#include "InputSystem.h"
#include "Game.h"
#include "Menu.h"
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

}

void InputSystem::PreProcess()
{
    memcpy(mState.KeyBoard.mPrevState, mState.KeyBoard.mCurrState, SDL_NUM_SCANCODES);

    mState.Mouse.mPrevButtons = mState.Mouse.mCurrButtons;
}

void InputSystem::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
       switch (event.type)
       {
        case SDL_QUIT:
            mGame->SetGameState(Game::EQuit);
            break;

        default:
            break;

       }
    }
    if (mState.KeyBoard.GetKeyState(SDL_SCANCODE_ESCAPE) == EPressed && mGame->GetGameState() == Game::EGameplay)
    {
        new Menu(mGame);
    }
    
    int x = 0, y = 0;
    mState.Mouse.mCurrButtons = SDL_GetMouseState(&x, &y);
    mState.Mouse.mPosition.x = static_cast<float>(x);
    mState.Mouse.mPosition.y = static_cast<float>(y);

}