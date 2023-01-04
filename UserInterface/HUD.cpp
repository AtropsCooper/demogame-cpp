#include "HUD.h"
#include "Game.h"
#include "Constants.h"
#include "Entity.h"
#include "StatusComponent.h"
#include <sstream>
#include <iomanip>

HUD::HUD(Game* game) :
	UIScreen(game),
	mCurHp(6)
{
	mTexBackground = game->GetTexture("UI");
	mBackWidth = UI_HUD_WIDTH;
	mBackHeight = UI_HUD_HEIGHT;
	mBackSrcRect = UI_HUD_BG;
	mBackPos = Vector2(16, 16);
	mHeartRect = UI_HUD_HEART;
	mHalfHeartRect = UI_HUD_HALF_HEART;
	mEmptyHeartRect = UI_HUD_EMPTY_HEART;
}

void HUD::Update()
{
	if (mGame->mPlayer != nullptr && mGame->mPlayer->GetState() == Entity::EActive)
	{
		mCurHp = static_cast<int>(mGame->mPlayer->GetComponent<StatusComponent>()->mHealth);
	}
	else
	{
		mCurHp = 0;
	}
}

void HUD::Draw(SDL_Renderer* renderer)
{
	// Draw Background
	SDL_Rect backRect = {static_cast<int>(mBackPos.x), static_cast<int>(mBackPos.y), mBackWidth, mBackHeight};
	SDL_RenderCopy(renderer, mTexBackground, &mBackSrcRect, &backRect);

	// Draw Hearts
	SDL_Rect dstRect = {UI_HUD_HEART_X_1 + backRect.x, UI_HUD_HEART_Y + backRect.y, UI_HUD_HEART_WIDTH, UI_HUD_HEART_HEIGHT};
	auto DrawHeart = [&](float health) -> void
	{
		if (health >= 2)
		{
			SDL_RenderCopy(renderer, mTexBackground, &mHeartRect, &dstRect);
		}
		else if (health >= 1)
		{
			SDL_RenderCopy(renderer, mTexBackground, &mHalfHeartRect, &dstRect);
		}
		else
		{
			SDL_RenderCopy(renderer, mTexBackground, &mEmptyHeartRect, &dstRect);
		}
	};

	DrawHeart(mCurHp);
	dstRect.x = UI_HUD_HEART_X_2 + backRect.x;
	DrawHeart(mCurHp - 2);
	dstRect.x = UI_HUD_HEART_X_3 + backRect.x;
	DrawHeart(mCurHp - 4);
}