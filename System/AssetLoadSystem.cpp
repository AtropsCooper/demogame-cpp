#include "AssetLoadSystem.h"
#include <SDL2/SDL_image.h>
#include <string>

// Assets
#include "cursor.h"
#include "dungeonfont.h"
#include "help.h"
#include "tiles.h"
#include "UI.h"
// sounds
#include "bgm.h"
#include "victory.h"
#include "arrow_wav.h"
#include "button_wav.h"
#include "damage_wav.h"
#include "death_wav.h"
#include "hit_wav.h"

AssetLoadSystem::AssetLoadSystem(class Game *game, int updateOrder, SDL_Renderer *renderer)
    : System(game, updateOrder), mRenderer(renderer), mCursor(nullptr)
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
    for (auto music : mMusics)
    {
        Mix_FreeMusic(music.second);
    }
    mMusics.clear();
    for (auto chunk : mChunks)
    {
        Mix_FreeChunk(chunk.second);
    }
    mChunks.clear();

    SDL_FreeCursor(mCursor);
}

void AssetLoadSystem::Initialize()
{
    IMG_Init(IMG_INIT_PNG);
    LoadTexture(TILES, TILES_length, "dungeon");
    LoadTexture(UI, UI_length, "UI");
    LoadTexture(HELP, HELP_length, "help");
    LoadMusic(bgm, bgm_length, "bgm");
    LoadMusic(victory, victory_length, "victory");
    LoadChunk(ARROW_WAV, ARROW_WAV_length, "arrow");
    LoadChunk(BUTTON_WAV, BUTTON_WAV_length, "button");
    LoadChunk(DAMAGE_WAV, DAMAGE_WAV_length, "damage");
    LoadChunk(DEATH_WAV, DEATH_WAV_length, "death");
    LoadChunk(HIT_WAV, HIT_WAV_length, "hit");

    SDL_Surface *surf = IMG_LoadPNG_RW(SDL_RWFromMem((void *)CURSOR, CURSOR_length));
    if (surf != nullptr)
    {
        mCursor = SDL_CreateColorCursor(surf, 18, 18);
        SDL_SetCursor(mCursor);
        SDL_FreeSurface(surf);
    }
}

SDL_Texture *AssetLoadSystem::GetTexture(const std::string &fileName) const
{
    SDL_Texture *text = nullptr;
    auto iter = mTextures.find(fileName);
    if (iter != mTextures.end())
    {
        text = iter->second;
    }
    return text;
}

void AssetLoadSystem::LoadTexture(const std::string &filename, const std::string &newName)
{
    auto iter = mTextures.find(newName);
    if (iter != mTextures.end())
    {
        SDL_DestroyTexture(iter->second);
        mTextures.erase(iter);
    }

    SDL_Surface *surf = IMG_Load(filename.c_str());
    if (!surf)
    {
        SDL_Log("Failed to load texture file %s", filename.c_str());
        return;
    }

    SDL_Texture *text = SDL_CreateTextureFromSurface(mRenderer, surf);
    SDL_FreeSurface(surf);
    if (!text)
    {
        SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
        return;
    }
    mTextures.emplace(newName, text);
}

void AssetLoadSystem::LoadTexture(const unsigned char *resource, int size, const std::string &newName)
{
    auto iter = mTextures.find(newName);
    if (iter != mTextures.end())
    {
        SDL_DestroyTexture(iter->second);
        mTextures.erase(iter);
    }

    SDL_Surface *surf = IMG_LoadPNG_RW(SDL_RWFromMem((void *)resource, size));
    if (!surf)
    {
        SDL_Log("Failed to load texture %s", newName.c_str());
        return;
    }

    SDL_Texture *text = SDL_CreateTextureFromSurface(mRenderer, surf);
    SDL_FreeSurface(surf);
    if (!text)
    {
        SDL_Log("Failed to convert surface to texture for %s", newName.c_str());
        return;
    }
    mTextures.emplace(newName, text);
}

void AssetLoadSystem::LoadChunk(const unsigned char *resource, int size, const std::string &newname)
{
    Mix_Chunk *sound;
    sound = Mix_LoadWAV_RW(SDL_RWFromMem((void *)resource, size), 1);
    if (!sound)
    {
        SDL_Log("Failed to load music file %s", newname.c_str());
    }
    mChunks.emplace(newname.c_str(), sound);
}

void AssetLoadSystem::LoadMusic(const unsigned char *resource, int size, const std::string &newname)
{
    Mix_Music *music;
    music = Mix_LoadMUS_RW(SDL_RWFromMem((void *)resource, size), 1);
    if (!music)
    {
        SDL_Log("Failed to load music file %s", newname.c_str());
    }
    mMusics.emplace(newname.c_str(), music);
}

Mix_Chunk *AssetLoadSystem::GetChunk(const std::string &soundName) const
{
    Mix_Chunk *chunk = nullptr;
    auto iter = mChunks.find(soundName);
    if (iter != mChunks.end())
    {
        chunk = iter->second;
    }
    return chunk;
}

Mix_Music *AssetLoadSystem::GetMusic(const std::string &musicName) const
{
    Mix_Music *music = nullptr;
    auto iter = mMusics.find(musicName);
    if (iter != mMusics.end())
    {
        music = iter->second;
    }
    return music;
}
