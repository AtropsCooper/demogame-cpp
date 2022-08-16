#include <SDL_image.h>
#include "Game.h"
#include "System.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "AssetLoadSystem.h"
#include "DrawSystem.h"

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
void Game::RemoveEntity(class Entity* entity){
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
    
    mAssetLoadSystem = new AssetLoadSystem(this, mRenderer);
    mAssetLoadSystem->Initialize();
    mDrawSystem = new DrawSystem(this, mRenderer);

    //  TEST CODE

    Entity* senpai = new Entity(this);
    SpriteComponent* sp = new SpriteComponent(senpai, 100);
    sp->SetTexture(mAssetLoadSystem->GetTexture("senpai"));
    senpai->mPosition = Vector2(512, 384);
    senpai->mScale = 2.0f;
    senpai->mRotation = MyMath::PiOver2;
    mDrawSystem->AddSprite(sp);

    //  TEST CODE

    return true;
}

void Game::Shutdown()
{


    delete mDrawSystem;
    delete mAssetLoadSystem;

    while (!mSystems.empty())
    {
        delete mSystems.back();
    }
    while (!mEntities.empty())
    {
        delete mEntities.back();
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
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            mIsRunning = false;
            break;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
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
