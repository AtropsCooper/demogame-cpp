#pragma once
#include "UIScreen.h"

class TitleScreen : public UIScreen
{
public:
	TitleScreen(class Game* game);
	~TitleScreen();
    void Draw(SDL_Renderer* renderer) override;

private:
    int mEscape;
	std::function<void()> PlayOnClick();
	std::function<void()> HelpOnClick();
	std::function<void()> QuitOnClick();
};