#pragma once
#include <SDL_image.h>
#include <unordered_map>
#include <string>

class AssetLoadSystem
{
public:
    AssetLoadSystem(class Game* game, SDL_Renderer* renderer);
    ~AssetLoadSystem();

    void Initialize();
    SDL_Texture* GetTexture(const std::string& fileName) const;

private:
    void LoadTexture (const std::string& filename, const std::string& newName);
    
    class Game* mGame;
    SDL_Renderer* mRenderer;
    std::unordered_map<std::string, SDL_Texture*> mTextures;
    
};
