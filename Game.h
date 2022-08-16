#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include "MyMath.h"

class Game
{
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddEntity(class Entity *entity);
    void RemoveEntity(class Entity *entity);
    void AddSystem(class System *system);
    void RemoveSystem(class System *system);

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    bool mIsRunning;
    Uint32 mTicksCount;

    std::vector<class Entity *> mEntities;
    std::vector<class System *> mSystems;

    class AssetLoadSystem *mAssetLoadSystem;
    class DrawSystem *mDrawSystem;
};