#include "AssetLoadSystem.h"
#include <SDL_image.h>
#include <string>

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
    LoadTexture("Assets/0x72_DungeonTilesetII_v1.4.png", "dungeon");
    LoadTexture("Assets/UI.png", "UI");
    LoadTexture("Assets/help.png", "help");

    SDL_Surface* surf = IMG_Load("Assets/cursor.png");
    if (surf != nullptr)
    {
        mCursor = SDL_CreateColorCursor(surf, 27, 27);
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
