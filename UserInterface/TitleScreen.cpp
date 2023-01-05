#include "TitleScreen.h"
#include "Game.h"
#include "Constants.h"
#include "Color.h"
#include "HelpScreen.h"

TitleScreen::TitleScreen(Game* game):
	UIScreen(game), mEscape(0)
{
	// Run into GPaused to process UI input
	mGame->SetGameState(Game::GameState::EPause);
	//Mix_PlayChannel(-1, mGame->GetSound("Menu"), 0);
	
	// Set background
	SDL_Renderer* renderer = game->GetRenderer();
	mTexBackground = game->GetTexture("UI");
	mBackPos = Vector2(WINDOW_WIDTH / 2, 550);
    mBackSrcRect = UI_MENU_BG;
    mBackWidth = 400;
    mBackHeight = 400;
	// Set main text
	mTextCenter = false;
	mTextPos = Vector2(WINDOW_WIDTH / 2, 180);
	SetText(GAME_TITLE, renderer, Color::White, 96);

	// Set buttons
	mButtonText = game->GetTexture("UI");
    mButtonOffRect = UI_BUTTON_OFF;
	mButtonOnRect = UI_BUTTON_ON;
	// Three buttons are placed in vertical
	Button* b1 = new Button(this);
	b1->SetPosition(Vector2(WINDOW_WIDTH / 2, 450));
    b1->SetWidthHeight(UI_BUTTON_WIDTH, UI_BUTTON_HEIGHT);
	b1->SetText("Play",renderer, Color::White, 32);
	b1->SetOnClick(PlayOnClick());

	Button* b2 = new Button(this);
	b2->SetPosition(Vector2(WINDOW_WIDTH / 2, 550));
    b2->SetWidthHeight(UI_BUTTON_WIDTH, UI_BUTTON_HEIGHT);
	b2->SetText("Help",renderer, Color::White, 32);
	b2->SetOnClick(HelpOnClick());

	Button* b3 = new Button(this);
	b3->SetPosition(Vector2(WINDOW_WIDTH / 2, 650));
    b3->SetWidthHeight(UI_BUTTON_WIDTH, UI_BUTTON_HEIGHT);
	b3->SetText("Exit",renderer, Color::White, 32);
	b3->SetOnClick(QuitOnClick());
}

TitleScreen::~TitleScreen()
{
	mGame->SetGameState(Game::GameState::EGameplay);
}

void TitleScreen::Draw(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    UIScreen::Draw(renderer);
}

std::function<void()> TitleScreen::PlayOnClick()
{
	return [this]()
	{
		Mix_PlayChannel(-1, mGame->GetChunk("button"), 0);
		Close();
	};
}

std::function<void()> TitleScreen::HelpOnClick()
{
	return [this]()
	{
		Mix_PlayChannel(-1, mGame->GetChunk("button"), 0);;
		new HelpScreen(mGame);
	};
}

std::function<void()> TitleScreen::QuitOnClick()
{
	return [this]()
	{
		mGame->SetGameState(Game::GameState::EQuit);
	};
}