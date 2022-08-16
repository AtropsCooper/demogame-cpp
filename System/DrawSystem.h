# pragma once
# include "System.h"
# include <vector>
# include "Game.h"

class DrawSystem
{
public:
    DrawSystem(class Game* game, SDL_Renderer* renderer);
    ~DrawSystem();

    void Draw() const;
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);

private:
    class Game* mGame;
    SDL_Renderer* mRenderer;
    std::vector<class SpriteComponent*> mSprites;
};