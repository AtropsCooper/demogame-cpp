#pragma once
#include "UIScreen.h"

class HUD : public UIScreen
{
public:
	HUD(class Game* game);
	void Update() override;
	void Draw(SDL_Renderer* renderer) override;

private:

	int mCurHp;
	SDL_Rect mHeartRect;
	SDL_Rect mHalfHeartRect;
	SDL_Rect mEmptyHeartRect;
};