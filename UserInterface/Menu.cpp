#include "Menu.h"
#include "Game.h"
#include "Constants.h"
#include "Color.h"
#include "HelpScreen.h"

Menu::Menu(Game *game) : UIScreen(game), mEscape(0)
{
	// Run into GPaused to process UI input
	mGame->SetGameState(Game::GameState::EPause);
	Mix_PlayChannel(-1, mGame->GetChunk("button"), 0);

	// Set background
	SDL_Renderer *renderer = game->GetRenderer();
	mTexBackground = game->GetTexture("UI");
	mBackPos = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mBackSrcRect = UI_MENU_BG;
	mBackWidth = 400;
	mBackHeight = 500;
	// Set main text
	mTextCenter = false;
	mTextPos = Vector2(WINDOW_WIDTH / 2, 220);
	SetText("Paused", renderer, Color::White, 48);

	// Set buttons
	mButtonText = game->GetTexture("UI");
	mButtonOffRect = UI_BUTTON_OFF;
	mButtonOnRect = UI_BUTTON_ON;
	// Three buttons are placed in vertical
	Button *b1 = new Button(this);
	b1->SetPosition(Vector2(WINDOW_WIDTH / 2, 350));
	b1->SetWidthHeight(UI_BUTTON_WIDTH, UI_BUTTON_HEIGHT);
	b1->SetText("Resume", renderer, Color::White, 32);
	b1->SetOnClick(ResumeOnClick());

	Button *b2 = new Button(this);
	b2->SetPosition(Vector2(WINDOW_WIDTH / 2, 450));
	b2->SetWidthHeight(UI_BUTTON_WIDTH, UI_BUTTON_HEIGHT);
	b2->SetText("Help", renderer, Color::White, 32);
	b2->SetOnClick(HelpOnClick());

	Button *b3 = new Button(this);
	b3->SetPosition(Vector2(WINDOW_WIDTH / 2, 550));
	b3->SetWidthHeight(UI_BUTTON_WIDTH, UI_BUTTON_HEIGHT);
	b3->SetText("Exit", renderer, Color::White, 32);
	b3->SetOnClick(QuitOnClick());
}

Menu::~Menu()
{
	mGame->SetGameState(Game::GameState::EGameplay);
}

void Menu::Update()
{
	UIScreen::Update();
	if (mInputState->KeyBoard.GetKeyState(SDL_SCANCODE_ESCAPE) == EReleased)
	{
		if (mEscape >= 1)
		{
			Close();
		}
		mEscape++;
	}
}

std::function<void()> Menu::ResumeOnClick()
{
	return [this]()
	{
		Mix_PlayChannel(-1, mGame->GetChunk("button"), 0);
		Close();
	};
}

std::function<void()> Menu::HelpOnClick()
{
	return [this]()
	{
		Mix_PlayChannel(-1, mGame->GetChunk("button"), 0);
		new HelpScreen(mGame);
	};
}

std::function<void()> Menu::QuitOnClick()
{
	return [this]()
	{
		mGame->SetGameState(Game::GameState::EQuit);
	};
}