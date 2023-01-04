#pragma once
#include "MovablePrefab.h"

class BossPrefab : public MovablePrefab
{
public:
    explicit BossPrefab(class Game *game, Vector2 position);
};
