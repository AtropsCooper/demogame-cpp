#include "System.h"
#include "Game.h"
#include <vector>
#include "SpriteComponent.h"
#include "Component.h"
#include "Helper.h"

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

template <typename T>
void System::DetectComponent(std::vector<T *> *container)
{
    auto messages = *(GetGame()->GetComponentMessages());
    for (auto c : messages)
    {
        Component *component = c.first;
        if (Helper::IsComponent<T>(component))
        {
            if(c.second)
            {
                int myOrder = component->GetUpdateOrder();
                auto iter = container->begin();
                for (; iter != container->end(); iter++)
                {
                    if (myOrder < (*iter)->GetUpdateOrder())
                    {
                        break;
                    }
                }
                container->insert(iter, dynamic_cast<T *>(component));
            }
            else
            {
                auto iter = std::find(container->begin(), container->end(), dynamic_cast<T *>(component));
                if (iter != container->end())
                {
                    container->erase(iter);
                }
            }
        }
    }
}

template void System::DetectComponent<class SpriteComponent>(std::vector<class SpriteComponent*> *container);