#include "System.h"
#include "Game.h"
#include <vector>
#include "SpriteComponent.h"
#include "AnimComponent.h"
#include "MoveComponent.h"
#include "AttackComponent.h"
#include "TransientComponent.h"
#include "CollisionBoxComponent.h"
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

#define tDetect(type) template void System::DetectComponent<class type>(std::vector<class type*> *container)

tDetect(SpriteComponent);
tDetect(AnimComponent);
tDetect(MoveComponent);
tDetect(AttackComponent);
tDetect(TransientComponent);
tDetect(CollisionBoxComponent);