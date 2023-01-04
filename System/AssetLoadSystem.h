#pragma once
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>
#include "System.h"

class AssetLoadSystem : public System
{
public:
    AssetLoadSystem(class Game* game, int updateOrder, SDL_Renderer* renderer);
    ~AssetLoadSystem();

    void Initialize();
    SDL_Texture* GetTexture(const std::string& fileName) const;

private:
    void LoadTexture (const std::string& filename, const std::string& newName);
    void LoadTexture (const unsigned char* resource, int size, const std::string& newName);

    SDL_Renderer* mRenderer;
    std::unordered_map<std::string, SDL_Texture*> mTextures;
    SDL_Cursor* mCursor;
};
