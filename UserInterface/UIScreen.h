#pragma once
#include <SDL2/SDL.h>
#include "MyMath.h"
#include "Vector2.h"
#include "Color.h"
#include "Game.h"
#include <string>
#include <functional>
#include <vector>

class Button
{
public:
	Button(class UIScreen *ui);
	~Button();

	// Set button's text
	void SetText(const std::string &text, SDL_Renderer *renderer, const Color::Color &color = Color::White, int size = 30);
	// Check if mouse cursor is in this button
	bool ContainsMouse(Vector2 mouse);
	// Process function when clicked
	void OnClick();

	void SetOnClick(std::function<void()> func) { mOnClick = func; }
	void SetFont(class Font *font) { mFont = font; }
	Vector2 GetPosition() const { return mPosition; }
	void SetPosition(Vector2 pos) { mPosition = pos; }
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
	void SetWidthHeight(int w, int h)
	{
		mWidth = w;
		mHeight = h;
	}
	SDL_Texture *GetText() const { return mText; }
	bool GetIsSelected() const { return mIsSelected; }
	void SetIsSelected(bool selected) { mIsSelected = selected; }

private:
	std::function<void()> mOnClick;
	SDL_Texture *mText;
	Vector2 mPosition;
	int mWidth;
	int mHeight;
	class Font *mFont;
	bool mIsSelected;
};

class UIScreen
{
public:
	UIScreen(class Game *game);
	virtual ~UIScreen();

	virtual void Update();
	// Draw background, main text, and buttons
	virtual void Draw(SDL_Renderer *renderer);
	void AddButton(class Button *button);
	// Reset all the buttons to the state unselected
	void ResetButtonState();
	// Reset the pointer of current button to null pointer
	void ResetButtonPointer();
	// Set main text
	void SetText(const std::string &text, SDL_Renderer *renderer, const Color::Color &color = Color::White, int size = 30);

	enum class UIState
	{
		EActive,
		EPaused,
		EDead
	};
	// Close and free this UI
	void Close();

	UIState GetState() const { return mState; }

protected:
	// Use texture and its position to get SDL_Rect of this texture
	SDL_Rect TextureRect(SDL_Texture *tex, Vector2 pos);
	SDL_Rect CenterAt(int w, int h, Vector2 pos);

	class Game *mGame;
	UIState mState;
	const InputState *mInputState;

	SDL_Texture *mTexBackground;
	Vector2 mBackPos;
	SDL_Rect mBackSrcRect;
	int mBackWidth;
	int mBackHeight;
	SDL_Texture *mText;
	Vector2 mTextPos;

	SDL_Texture *mButtonText;
	// Texture of selected button
	SDL_Rect mButtonOnRect;
	// Texture of unselected button
	SDL_Rect mButtonOffRect;

	class Font *mFont;
	// If the main text is at the center of the background
	bool mTextCenter;

	// Current button selected by keyboard input
	Button *mCurButton;
	std::vector<class Button *> mButtons;

private:
	Vector2 mPosition;
};