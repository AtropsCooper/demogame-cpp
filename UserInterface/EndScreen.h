#pragma once
#include "UIScreen.h"

class EndScreen : public UIScreen
{
public:
    EndScreen(class Game* game, bool isWin);
    ~EndScreen();
    void Draw(SDL_Renderer* renderer) override;

private:
	std::function<void()> RetryOnClick();
	std::function<void()> QuitOnClick();
};