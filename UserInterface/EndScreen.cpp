#include "EndScreen.h"
#include "Game.h"
#include "Constants.h"
#include "Color.h"
#include "HelpScreen.h"

EndScreen::EndScreen(Game* game, bool isWin):
	UIScreen(game)
{
	// Run into GPaused to process UI input
	mGame->SetGameState(Game::GameState::EPause);
	//Mix_PlayChannel(-1, mGame->GetSound("Menu"), 0);
	
	// Set background
	SDL_Renderer* renderer = game->GetRenderer();
	mTexBackground = game->GetTexture("UI");
	mBackPos = Vector2(WINDOW_WIDTH / 2, 480);
    mBackSrcRect = UI_MENU_BG;
    mBackWidth = 400;
    mBackHeight = 300;
	// Set main text
	mTextCenter = false;
	mTextPos = Vector2(WINDOW_WIDTH / 2, 150);
    std::string title = isWin ? "You Win!" : "You Dead!";
	SetText(title, renderer, Color::White, 72);

	// Set buttons
	mButtonText = game->GetTexture("UI");
    mButtonOffRect = UI_BUTTON_OFF;
	mButtonOnRect = UI_BUTTON_ON;
	// Three buttons are placed in vertical
	Button* b1 = new Button(this);
	b1->SetPosition(Vector2(WINDOW_WIDTH / 2, 430));
    b1->SetWidthHeight(UI_BUTTON_WIDTH, UI_BUTTON_HEIGHT);
	b1->SetText("Retry",renderer, Color::White, 32);
	b1->SetOnClick(RetryOnClick());

	Button* b2 = new Button(this);
	b2->SetPosition(Vector2(WINDOW_WIDTH / 2, 530));
    b2->SetWidthHeight(UI_BUTTON_WIDTH, UI_BUTTON_HEIGHT);
	b2->SetText("Exit",renderer, Color::White, 32);
	b2->SetOnClick(QuitOnClick());
}

EndScreen::~EndScreen()
{
    mGame->SetGameState(Game::EGameplay);
}

void EndScreen::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(
        renderer,
        34, 34, 34, 255);
    SDL_RenderClear(renderer);
    UIScreen::Draw(renderer);
}

std::function<void()> EndScreen::RetryOnClick()
{
	return [this]()
	{
		//Mix_PlayChannel(-1, mGame->GetSound("Menu"), 0);
		mGame->Replay();
        mGame->SetGameState(Game::EGameplay);
        Close();
	};
}

std::function<void()> EndScreen::QuitOnClick()
{
	return [this]()
	{
		mGame->SetGameState(Game::GameState::EQuit);
	};
}