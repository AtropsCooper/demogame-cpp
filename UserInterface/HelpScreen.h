#pragma once
#include "UIScreen.h"
#include "Game.h"

class HelpScreen : UIScreen
{
public:
    HelpScreen(class Game* game);
private:
    std::function<void()> OkOnClick();
};