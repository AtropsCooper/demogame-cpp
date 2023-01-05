#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include <algorithm>
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
#include "AISystem.h"
#include "PlayerPrefab.h"
#include "TileMapManager.h"
#include "UIScreen.h"
#include "HUD.h"
#include "Font.h"
#include "Menu.h"
#include "TitleScreen.h"
#include "EndScreen.h"

// font
#include "dungeonfont.h"


Game::Game()
    : mPlayer(nullptr),
      mBoss(nullptr),
      mWindow(nullptr),
      mRenderer(nullptr),
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

Mix_Chunk* Game::GetChunk(const std::string& soundName) const
{
    return mAssetLoadSystem->GetChunk(soundName);
}

Mix_Music* Game::GetMusic(const std::string& musicName) const
{
    return mAssetLoadSystem->GetMusic(musicName);
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
        30,
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
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		SDL_Log("Failed to initialize SDL_mixer");
		return false;
	}
    // LoadFont
    Font* font = new Font(this);
	if (font->LoadFont(FONT, FONT_length))
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
    mAISystem = new AISystem(this, 180);
    new MoveSystem(this, 185);
    mPlayerControllerSystem = new PlayerControllerSystem(this, 170);
    new TransientSystem(this, 101);
    mEnemySpawnSystem = new EnemySpawnSystem(this, 100);
    new CollisionSystem(this, 181);
    new DamageSystem(this, 179);
    mTileMapManager = new TileMapManager(this);
    mHUD =  new HUD(this);
    new TitleScreen(this);

    srand((unsigned)clock());
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
    mAISystem->SetPlayer(mPlayer);
    mEnemySpawnSystem->SetPlayer(mPlayer);
    mEnemySpawnSystem->SpawnEnemies(20);
    mBoss = mEnemySpawnSystem->SpawnBoss();
    mPlayerControllerSystem->SetPlayer(mPlayer);
    mHUD->SetPlayer(mPlayer);
    Mix_PlayMusic(GetMusic("bgm"), -1);
	Mix_VolumeMusic(60);
}

void Game::Replay()
{
    Mix_PlayChannel(-1, GetChunk("button"), 0);
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

    while (!mSystems.empty())
    {
        delete mSystems.back();
    }
    ClearEntities();

    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    Mix_CloseAudio();

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
    if (mPlayer != nullptr && mPlayer->GetState() == Entity::EDead)
    {
        Mix_PlayChannel(-1, GetChunk("death"), 0);
        new EndScreen(this, false);
    }
    // If Boss is Dead
    if (mBoss != nullptr && mBoss->GetState() == Entity::EDead)
    {
        Mix_PlayMusic(GetMusic("victory"), -1);
        new EndScreen(this, true);
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
