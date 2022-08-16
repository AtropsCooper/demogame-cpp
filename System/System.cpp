#include "System.h"
#include "Game.h"

System::System(Game* game, int updateOrder)
    : mUpdateOrder(updateOrder)
    , mGame(game)
{
    mGame->AddSystem(this);
}

System::~System()
{
    mGame->RemoveSystem(this);
}

void System::Update(float deltaTime)
{
    return;
}