#pragma once
#include "System.h"

class TransientSystem : System
{
public:
    TransientSystem(Game *game, int order) : System(game, order) {}
    void FetchComponents() override;
    void Update(float deltaTime) override;

private:
    std::vector<class TransientComponent *> mTransientComponents;
};