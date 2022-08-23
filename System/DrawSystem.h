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
    void Update(float deltaTime) override;
    void Draw() const;
    void SetPlayer(class Entity* player);

private:
    class Game* mGame;
    SDL_Renderer* mRenderer;
    std::vector<class SpriteComponent*> mSprites;

    int mWindowWidth;
    int mWindowHeight;
    Vector2 mCameraPos;
    float mPixelsPerGrid;

    class Entity* mPlayer;
};