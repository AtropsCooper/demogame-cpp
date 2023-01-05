#pragma once
#include <vector>
#include <utility>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "MyMath.h"
#include "InputSystem.h"

class Game
{
public:

    enum GameState
    {
        EGameplay,
        EPause,
        EQuit
    };

    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void ClearEntities();
    void MakeLevel();
    void Replay();
    void AddEntity(class Entity *entity);
    void RemoveEntity(class Entity *entity);
    void AddSystem(class System *system);
    void RemoveSystem(class System *system);
    void PushUI(class UIScreen *screen) { mUIStack.emplace_back(screen); };
    bool HasUI() { return !mUIStack.empty(); }
    GameState GetGameState() const { return mGameState; }
	void SetGameState(GameState state) { mGameState = state; }
    const class PlayerControllerSystem *GetPlayerControllerSystem() const { return mPlayerControllerSystem; }
    const class DrawSystem *GetDrawSystem() const { return mDrawSystem; }
    const InputState *GetInputState() const { return mInputState; }
    class Font* GetFont() const { return mFont; }
	class HUD* GetHUD() const { return mHUD; }
    SDL_Texture *GetTexture(const std::string &fileName) const;
    SDL_Renderer *GetRenderer() const { return mRenderer; }
    Mix_Chunk* GetChunk(const std::string& soundName) const;
    Mix_Music* GetMusic(const std::string& musicName) const;
    void ComponentMessage(class Component *component, bool isAdd);
    const std::vector<std::pair<class Component *, bool>> *GetComponentMessages() const;
    void CollisionMessage(class Entity *first, class Entity *second);
    const std::vector<std::pair<class Entity*, class Entity*>> *GetCollisionMessages() const;

    class Entity *mPlayer;
    class Entity *mBoss;
    class TileMapManager *mTileMapManager;
private:
    void ProcessInput();
    void UpdateGame();
    void UpdateUI();
    void GenerateOutput();

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    GameState mGameState;
    Uint32 mTicksCount;

    std::vector<class Entity *> mEntities;
    std::vector<class System *> mSystems;
    std::vector<class UIScreen*> mUIStack;
    std::vector<std::pair<class Component *, bool>> mComponentMessages;
    std::vector<std::pair<class Entity*, class Entity*>> mCollisionMessages;

    class PlayerControllerSystem *mPlayerControllerSystem;
    class AssetLoadSystem *mAssetLoadSystem;
    class DrawSystem *mDrawSystem;
    class InputSystem *mInputSystem;
    class EnemySpawnSystem *mEnemySpawnSystem;
    class AISystem *mAISystem;
    class Font* mFont;
	class HUD* mHUD;

    const InputState *mInputState;
 
};