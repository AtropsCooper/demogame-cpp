#pragma once
#include <vector>
#include <utility>
#include <string>
#include <SDL2/SDL.h>
#include "MyMath.h"
#include "InputSystem.h"

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
    void SetIsRunning(bool isRunning);
    const class PlayerControllerSystem *GetPlayerControllerSystem() const { return mPlayerControllerSystem; }
    const class DrawSystem *GetDrawSystem() const { return mDrawSystem; }
    const InputState *GetInputState() const { return mInputState; }
    SDL_Texture *GetTexture(const std::string &fileName) const;
    void ComponentMessage(class Component *component, bool isAdd);
    const std::vector<std::pair<class Component *, bool>> *GetComponentMessages() const;
    void CollisionMessage(class Entity *first, class Entity *second);
    const std::vector<std::pair<class Entity*, class Entity*>> *GetCollisionMessages() const;

    class Entity *mPlayer;
      class TileMapManager *mTMM;
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
    std::vector<std::pair<class Component *, bool>> mComponentMessages;
    std::vector<std::pair<class Entity*, class Entity*>> mCollisionMessages;

    class PlayerControllerSystem *mPlayerControllerSystem;
    class AssetLoadSystem *mAssetLoadSystem;
    class DrawSystem *mDrawSystem;
    class InputSystem *mInputSystem;

    const InputState *mInputState;

 
};