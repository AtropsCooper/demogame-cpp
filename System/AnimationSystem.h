#pragma once
#include "System.h"
#include "AnimComponent.h"
#include <vector>

class AnimationSystem : public System
{
public:
    AnimationSystem(class Game* game, int updateOrder);

    void FetchComponents() override;
    void Update(float deltaTime) override;
private:
    std::vector<AnimComponent *> mAnimComponents;
};