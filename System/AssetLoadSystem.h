#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <unordered_map>
#include <string>
#include "System.h"

class AssetLoadSystem : public System
{
public:
    AssetLoadSystem(class Game *game, int updateOrder, SDL_Renderer *renderer);
    ~AssetLoadSystem();

    void Initialize();
    SDL_Texture *GetTexture(const std::string &fileName) const;
    Mix_Chunk *GetChunk(const std::string &soundName) const;
    Mix_Music *GetMusic(const std::string &musicName) const;

private:
    void LoadTexture(const std::string &filename, const std::string &newName);
    void LoadTexture(const unsigned char *resource, int size, const std::string &newName);
    void LoadChunk(const unsigned char *resource, int size, const std::string &newname);
    void LoadMusic(const unsigned char *resource, int size, const std::string &newname);

    SDL_Renderer *mRenderer;
    std::unordered_map<std::string, SDL_Texture *> mTextures;
    std::unordered_map<std::string, Mix_Chunk *> mChunks;
    std::unordered_map<std::string, Mix_Music *> mMusics;
    SDL_Cursor *mCursor;
};
