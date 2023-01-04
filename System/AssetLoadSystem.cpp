#include "AssetLoadSystem.h"
#include <SDL2/SDL_image.h>
#include <string>

// Assets
#include "cursor.h"
#include "dungeonfont.h"
#include "help.h"
#include "tiles.h"
#include "UI.h"

AssetLoadSystem::AssetLoadSystem(class Game* game, int updateOrder, SDL_Renderer* renderer)
    : System(game, updateOrder)
    , mRenderer(renderer)
    , mCursor(nullptr)
{
}

AssetLoadSystem::~AssetLoadSystem()
{
    IMG_Quit();
    for (auto tex : mTextures)
    {
        SDL_DestroyTexture(tex.second);
    }
    mTextures.clear();
    SDL_FreeCursor(mCursor);
}

void AssetLoadSystem::Initialize()
{
    IMG_Init(IMG_INIT_PNG);
    // LoadTexture("Assets/bin/0x72_DungeonTilesetII_v1.4.png", "dungeon");
    // LoadTexture("Assets/bin/UI.png", "UI");
    // LoadTexture("Assets/bin/help.png", "help");
    LoadTexture(TILES, TILES_length, "dungeon");
    LoadTexture(UI, UI_length, "UI");
    LoadTexture(HELP, HELP_length, "help");

    SDL_Surface* surf = IMG_LoadPNG_RW(SDL_RWFromMem((void*)CURSOR, CURSOR_length));
    if (surf != nullptr)
    {
        mCursor = SDL_CreateColorCursor(surf, 18, 18);
        SDL_SetCursor(mCursor);
        SDL_FreeSurface(surf);
    }
}

SDL_Texture* AssetLoadSystem::GetTexture(const std::string& fileName) const
{
	SDL_Texture* text = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		text = iter->second;
	}
	return text;
}

void AssetLoadSystem::LoadTexture (const std::string& filename, const std::string& newName)
{
    auto iter = mTextures.find(newName);
	if (iter != mTextures.end())
	{
		SDL_DestroyTexture(iter->second);
		mTextures.erase(iter);
	}

    SDL_Surface* surf = IMG_Load(filename.c_str());
    if (!surf)
    {
        SDL_Log("Failed to load texture file %s", filename.c_str());
        return;
    }

    SDL_Texture* text = SDL_CreateTextureFromSurface(mRenderer, surf);
    SDL_FreeSurface(surf);
    if (!text)
    {
        SDL_Log ("Failed to convert surface to texture for %s", filename.c_str());
        return;
    }
    mTextures.emplace(newName, text);
}

void AssetLoadSystem::LoadTexture (const unsigned char* resource, int size, const std::string& newName)
{
    auto iter = mTextures.find(newName);
	if (iter != mTextures.end())
	{
		SDL_DestroyTexture(iter->second);
		mTextures.erase(iter);
	}

    SDL_Surface* surf = IMG_LoadPNG_RW(SDL_RWFromMem((void*)resource, size));
    if (!surf)
    {
        SDL_Log("Failed to load texture %s", newName.c_str());
        return;
    }

    SDL_Texture* text = SDL_CreateTextureFromSurface(mRenderer, surf);
    SDL_FreeSurface(surf);
    if (!text)
    {
        SDL_Log ("Failed to convert surface to texture for %s", newName.c_str());
        return;
    }
    mTextures.emplace(newName, text);
}