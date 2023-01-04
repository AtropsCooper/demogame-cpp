#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <unordered_map>
#include "MyMath.h"
#include "Color.h"

class Font
{
public:
	Font(class Game* game);
	~Font();

	bool LoadFont(const unsigned char* fontData, int size);
	SDL_Surface* CreateText(const std::string& text, 
                            const Color::Color& color = Color::White,
                            int size = 30);

private:
	std::unordered_map<int, TTF_Font*> mFontData;
	class Game* mGame;
};