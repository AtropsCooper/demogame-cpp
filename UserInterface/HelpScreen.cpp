#include "HelpScreen.h"
#include "Constants.h"

HelpScreen::HelpScreen(Game* game) : UIScreen(game)
{
	game->SetGameState(Game::GameState::EPause);
    mTexBackground = game->GetTexture("help");
    SDL_QueryTexture(mTexBackground, nullptr, nullptr, &mBackWidth, &mBackHeight);
    mBackSrcRect = {0, 0, mBackWidth, mBackHeight};
	mBackPos = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    // Set buttons
	mButtonText = game->GetTexture("UI");
    mButtonOffRect = UI_BUTTON_OFF;
	mButtonOnRect = UI_BUTTON_ON;
	// Three buttons are placed in vertical
	Button* b1 = new Button(this);
	b1->SetPosition(Vector2(WINDOW_WIDTH / 2, 580));
    b1->SetWidthHeight(UI_BUTTON_WIDTH / 2, UI_BUTTON_HEIGHT / 2);
    SDL_Renderer* renderer = mGame->GetRenderer();
	b1->SetText("OK",renderer, Color::White, 32);
	b1->SetOnClick(OkOnClick());
}

std::function<void()> HelpScreen::OkOnClick()
{
	return [this]()
	{
		//Mix_PlayChannel(-1, mGame->GetSound("Menu"), 0);
		Close();
	};
}