#pragma once
#include "MovablePrefab.h"

class ArrowPrefab : public MovablePrefab
{
public:
    explicit ArrowPrefab(class Game *game, Vector2 position, float life);
};
