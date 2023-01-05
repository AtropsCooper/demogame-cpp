#include "Font.h"
#include "Game.h"

Font::Font(Game* game):
	mGame(game)
{

}

Font::~Font()
{
	for (auto& font : mFontData)
	{
		TTF_CloseFont(font.second);
	}
	TTF_Quit();
}

bool Font::LoadFont(const unsigned char* fontData, int dataSize)
{
	// For each font size, make a TTF_Font
	std::vector<int> fontSizes = { 24, 32, 48, 72, 96 };
	for (auto& size : fontSizes)
	{
		TTF_Font* font = TTF_OpenFontRW(SDL_RWFromMem((void*)fontData, dataSize), 1, size);
		printf("%s", TTF_GetError());
		if (font == nullptr)
		{
			SDL_Log("Failed to load font.");
			return false;
		}
		// Add font to mFontData
		mFontData.emplace(size, font);
	}
	return true;
}

SDL_Surface* Font::CreateText(const std::string& text, const Color::Color& color, int size)
{
	SDL_Surface* surf = nullptr;
	SDL_Color sdlColor;

	sdlColor.r = color.r;
	sdlColor.g = color.g;
	sdlColor.b = color.b;
	sdlColor.a = 255;

	auto iter = mFontData.find(size);
	if (iter != mFontData.end())
	{
		TTF_Font* font = iter->second;
		// Transform the TTF_Font to SDL_Surface
		surf = TTF_RenderText_Blended(font, text.c_str(), sdlColor);
	}
	return surf;
}