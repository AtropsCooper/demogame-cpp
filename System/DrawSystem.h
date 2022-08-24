#pragma once
#include "System.h"
#include <vector>
#include "Game.h"
#include "Vector2.h"

class DrawSystem : public System
{
public:
    DrawSystem(class Game *game, int updateOrder, SDL_Renderer *renderer);

    Vector2 WorldToScreen(const Vector2 &v) const;
    Vector2 ScreenToWorld(const Vector2 &v) const;

    void FetchComponents() override;
    void Update(float deltaTime) override;
    void Draw() const;
    void SetPlayer(class Entity *player);

private:
    SDL_Renderer *mRenderer;
    std::vector<class SpriteComponent *> mSprites;

    int mWindowWidth;
    int mWindowHeight;
    Vector2 mCameraPos;
    float mPixelsPerGrid;

    class Entity *mPlayer;
    class TileMapSystem *mTileMap;
};