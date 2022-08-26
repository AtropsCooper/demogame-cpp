#include <SDL_image.h>
#include "Game.h"
#include "System.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "AnimComponent.h"
#include "MoveComponent.h"
#include "AnimationSystem.h"
#include "AssetLoadSystem.h"
#include "DrawSystem.h"
#include "InputSystem.h"
#include "MoveSystem.h"
#include "BattleSystem.h"
#include "TransientSystem.h"
#include "PlayerControllerSystem.h"

#include "TileMapManager.h"


Game::Game()
    : mWindow(nullptr),
      mRenderer(nullptr),
      mIsRunning(true),
      mTicksCount(0)
{
}

void Game::AddEntity(class Entity* entity)
{
    mEntities.insert(mEntities.begin(), entity);
}
void Game::RemoveEntity(class Entity* entity)
{
    auto iter = std::find(mEntities.begin(), mEntities.end(), entity);
    if (iter != mEntities.end())
    {
        mEntities.erase(iter);
    }
}
void Game::AddSystem(class System* system)
{
    int myOrder = system->GetUpdateOrder();
    auto iter = mSystems.begin();
    for (; iter != mSystems.end(); iter++)
    {
        if (myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }
    mSystems.insert(iter, system);
}
void Game::RemoveSystem(class System* system)
{
    auto iter = std::find(mSystems.begin(), mSystems.end(), system);
    if (iter != mSystems.end())
    {
        mSystems.erase(iter);
    }
}
void Game::SetIsRunning(bool isRunning)
{
    mIsRunning = isRunning;
}
SDL_Texture* Game::GetTexture(const std::string &fileName) const
{
    return mAssetLoadSystem->GetTexture(fileName);
}


void Game::ComponentMessage(class Component *component, bool isAdd)
{
    mMessages.emplace_back(std::make_pair(component, isAdd));
}

const std::vector<std::pair<class Component *, bool>> *Game::GetComponentMessages() const
{
    return &mMessages;
}

bool Game::Initialize()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
        "Awesome Title",
        100,
        100,
        1024,
        768,
        0);
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(
        mWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }
    
    mInputSystem = new InputSystem(this, 0);
    mInputSystem->Initialize();
    mInputState = &(mInputSystem->GetState());
    mAssetLoadSystem = new AssetLoadSystem(this, 10, mRenderer);
    mAssetLoadSystem->Initialize();
    mDrawSystem = new DrawSystem(this, 200, mRenderer);
    new AnimationSystem(this, 190);
    new MoveSystem(this, 180);
    PlayerControllerSystem *pcs = new PlayerControllerSystem(this, 170);
    new TransientSystem(this, 199);
    //new BattleSystem(this, 17);

    //  TEST CODE
    mTMM = new TileMapManager(this);
    mTMM->Initialize();
    mTMM->GenerateMap();
    mTMM->Instanciate();

    mPlayer = new Entity(this);

    mDrawSystem->SetPlayer(mPlayer);
    AnimComponent* hero = new AnimComponent(mPlayer, 200);
    new MoveComponent(mPlayer, 100);
    mPlayer->mScale = 1.0f;
    hero->mOffset.y = 0.8f;
    mPlayer->mPosition = Vector2(0, 0);
    SDL_Rect idle = {128, 196, 16, 28}; //4
    SDL_Rect run = {192, 196, 16, 28}; //4
    SDL_Rect hit = {256, 196, 16, 28}; //1
    // Need fix: SetTexture every time
    hero->SetState(AnimComponent::EMoving);
    hero->SetTexture(mAssetLoadSystem->GetTexture("dungeon"), &idle);
    hero->SetAnimSprites(AnimComponent::EIdle, &idle, 4, 0.15f);
    hero->SetAnimSprites(AnimComponent::EMoving, &run, 4, 0.15f);
    hero->SetAnimSprites(AnimComponent::EHit, &hit, 1, 0.15f);

    pcs->SetPlayer(mPlayer);
    //  TEST CODE

    return true;
}

void Game::Shutdown()
{
    delete mTMM;

    while (!mSystems.empty())
    {
        delete mSystems.back();
    }
    while (!mEntities.empty())
    {
        delete mEntities.back();
        mEntities.pop_back();
    }

    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);

    SDL_Quit();
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    // Do Nothing    
}

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    mTicksCount = SDL_GetTicks();

    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    // Update 
    for (auto system : mSystems)
    {
        system->FetchComponents();
    }
    mMessages.clear();
    // Delete Dead Entities
    for (auto entity = mEntities.begin(); entity != mEntities.end();)
    {
        if ((*entity)->GetState() == Entity::EDead)
        {
            delete *entity;
            entity = mEntities.erase(entity);
        }
        else
        {
            entity++;
        }
    }

    for (auto system : mSystems)
    {
        system->Update(deltaTime);
    }

}

void Game::GenerateOutput()
{
    // Temperary processes
    SDL_SetRenderDrawColor(
        mRenderer,
        0, 0, 255, 255);

    SDL_RenderClear(mRenderer);

    mDrawSystem->Draw();

    SDL_RenderPresent(mRenderer);
}
