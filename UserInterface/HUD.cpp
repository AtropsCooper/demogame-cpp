#include "HUD.h"
#include "Game.h"
#include "Constants.h"
#include "Entity.h"
#include "StatusComponent.h"
#include <sstream>
#include <iomanip>

HUD::HUD(Game* game) :
	UIScreen(game),
	mCurHp(6),
	mMaxHp(6)
{
	mTexBackground = game->GetTexture("UI");
	mBackWidth = UI_HUD_WIDTH;
	mBackHeight = UI_HUD_HEIGHT;
	mBackSrcRect = UI_HUD_BG;
	//SDL_SetTextureAlphaMod(mTexBackground, 128);
	mBackPos = Vector2(16, 16);
}

void HUD::Update()
{
	if (mGame->mPlayer != nullptr && mGame->mPlayer->GetState() == Entity::EActive)
	{
		mCurHp = mGame->mPlayer->GetComponent<StatusComponent>()->mHealth;
	}

}

void HUD::Draw(SDL_Renderer* renderer)
{
	// Draw Background
	SDL_Rect backRect = {16, 16, mBackWidth, mBackHeight};
	SDL_RenderCopy(renderer, mTexBackground, &mBackSrcRect, &backRect);

	// Draw Hearts
}