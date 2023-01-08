#pragma once
#include "System.h"
#include "Vector2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_mouse.h>

enum ButtonState
{
    ENone = 0,
    EPressed = 1,
    EReleased = 2,
    EHeld = 3
};

class KeyBoardState
{
public:
    friend class InputSystem;

    bool GetKeyValue(SDL_Scancode keyCode) const;
    ButtonState GetKeyState(SDL_Scancode keyCode) const;

private:
    const Uint8 *mCurrState;
    Uint8 mPrevState[SDL_NUM_SCANCODES];
};

class MouseState
{
public:
    friend class InputSystem;

    const Vector2 &GetMousePosition() const { return mPosition; }
    bool GetButtonValue(int button) const;
    ButtonState GetButtonState(int button) const;

private:
    Vector2 mPosition;
    Uint32 mPrevButtons;
    Uint32 mCurrButtons;
};

struct InputState
{
    KeyBoardState KeyBoard;
    MouseState Mouse;
};

class InputSystem : public System
{
public:
    InputSystem(Game *game, int updateOrder);
    void Initialize();
    void PreProcess();
    void ProcessInput();

    const InputState &GetState() const { return mState; }

private:
    InputState mState;
};