#include <SDL_image.h>
#include <SDL_ttf.h>
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
#include "TransientSystem.h"
#include "PlayerControllerSystem.h"
#include "EnemySpawnSystem.h"
#include "CollisionSystem.h"
#include "DamageSystem.h"
#include "PlayerPrefab.h"
#include "TileMapManager.h"
#include "UIScreen.h"
#include "HUD.h"
#include "Font.h"
#include "Menu.h"
#include "TitleScreen.h"
#include "EndScreen.h"


Game::Game()
    : mWindow(nullptr),
      mRenderer(nullptr),
      mPlayer(nullptr),
      mGameState(EGameplay),
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

SDL_Texture* Game::GetTexture(const std::string &fileName) const
{
    return mAssetLoadSystem->GetTexture(fileName);
}


void Game::ComponentMessage(class Component *component, bool isAdd)
{
    mComponentMessages.emplace_back(std::make_pair(component, isAdd));
}

const std::vector<std::pair<class Component *, bool>> *Game::GetComponentMessages() const
{
    return &mComponentMessages;
}

void Game::CollisionMessage(class Entity *first, class Entity *second)
{
    mCollisionMessages.emplace_back(std::make_pair(first, second));
}

const std::vector<std::pair<class Entity*, class Entity*>> *Game::GetCollisionMessages() const
{
    return &mCollisionMessages;
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
        "Dino Dungeon",
        100,
        100,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
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

    if (TTF_Init())
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}
    // LoadFont
    Font* font = new Font(this);
	if (font->LoadFont("./Assets/DungeonFont.ttf"))
	{
		mFont = font;
	}
    
    mInputSystem = new InputSystem(this, 0);
    mInputSystem->Initialize();
    mInputState = &(mInputSystem->GetState());
    mAssetLoadSystem = new AssetLoadSystem(this, 10, mRenderer);
    mAssetLoadSystem->Initialize();
    mDrawSystem = new DrawSystem(this, 200, mRenderer);
    new AnimationSystem(this, 190);
    new MoveSystem(this, 182);
    mPlayerControllerSystem = new PlayerControllerSystem(this, 170);
    new TransientSystem(this, 101);
    mEnemySpawnSystem = new EnemySpawnSystem(this, 100);
    new CollisionSystem(this, 181);
    new DamageSystem(this, 179);
    mTileMapManager = new TileMapManager(this);
    mHUD =  new HUD(this);
    new TitleScreen(this);

    MakeLevel();

    return true;
}

void Game::ClearEntities()
{
    while (!mEntities.empty())
    {
        delete mEntities.back();
        mEntities.pop_back();
    }    
}

void Game::MakeLevel()
{
    mComponentMessages.clear();
    mCollisionMessages.clear();
    mTileMapManager->Initialize();
    mTileMapManager->GenerateMap();
    mTileMapManager->Instanciate();
    mPlayer = new PlayerPrefab(this, mTileMapManager->GetSpawnPoint());
    mDrawSystem->SetPlayer(mPlayer);
    mEnemySpawnSystem->SetPlayer(mPlayer);
    mPlayerControllerSystem->SetPlayer(mPlayer);
    mHUD->SetPlayer(mPlayer);
}

void Game::Replay()
{
    // Clean Up
    for (auto sys : mSystems)
    {
        sys->CleanUp();
    }
    mTileMapManager->CleanUp();
    ClearEntities();
    mCollisionMessages.clear();
    mComponentMessages.clear();
    MakeLevel();
}

void Game::Shutdown()
{
    delete mTileMapManager;

    while (!mUIStack.empty())
    {
        delete mUIStack.back();
    }
    while (!mSystems.empty())
    {
        delete mSystems.back();
    }
    ClearEntities();

    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);

    SDL_Quit();
}

void Game::RunLoop()
{
    while (mGameState != EQuit)
    {
        ProcessInput();
        if (mGameState == EGameplay)
        {
            UpdateGame();
        }
        UpdateUI();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    mInputSystem->PreProcess();
    mInputSystem->ProcessInput();
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
    // Refresh Messages 

    for (auto system : mSystems)
    {
        system->FetchComponents();
    }
    mComponentMessages.clear();
    mCollisionMessages.clear();

    // If Player is Dead
    if (mPlayer->GetState() == Entity::EDead)
    {
        new EndScreen(this, false);
    }

    // Delete Dead Entities
    for (auto entity = mEntities.begin(); entity != mEntities.end();)
    {
        if ((*entity)->GetState() == Entity::EDead && (*entity) != mPlayer)
        {
            delete *entity;
            entity = mEntities.erase(entity);
        }
        else
        {
            entity++;
        }
    }

    // Update systems
    for (auto system : mSystems)
    {
        system->Update(deltaTime);
    }
    
}

void Game::UpdateUI()
{
    if (!mUIStack.empty())
    {
        mUIStack.back()->Update();
    }
	// Free all dead UIs
	for (auto iter = mUIStack.begin(); iter != mUIStack.end(); iter++)
	{
		if ((*iter)->GetState() == UIScreen::UIState::EDead)
		{
			delete *iter;
			iter = mUIStack.erase(iter);
			iter--;
		}
	}
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(
        mRenderer,
        34, 34, 34, 255);

    SDL_RenderClear(mRenderer);

    mDrawSystem->Draw();

    	for (auto ui : mUIStack)
	{
		ui->Draw(mRenderer);
	}

    SDL_RenderPresent(mRenderer);
}
