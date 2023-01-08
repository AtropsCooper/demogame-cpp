#pragma once
#include "UIScreen.h"

class Menu : public UIScreen
{
public:
	Menu(class Game *game);
	~Menu();
	void Update() override;

private:
	int mEscape;
	std::function<void()> ResumeOnClick();
	std::function<void()> HelpOnClick();
	std::function<void()> QuitOnClick();
};