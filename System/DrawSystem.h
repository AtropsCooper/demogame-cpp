# pragma once
# include "System.h"
# include <vector>
# include "Game.h"

class DrawSystem : public System
{
public:
    DrawSystem(class Game* game, int updateOrder, SDL_Renderer* renderer);
    ~DrawSystem();

    void FetchComponents() override;
    void Draw() const;
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);

private:
    class Game* mGame;
    SDL_Renderer* mRenderer;
    std::vector<class SpriteComponent*> mSprites;
};