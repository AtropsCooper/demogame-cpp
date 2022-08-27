#pragma once
#include "MovablePrefab.h"

class PlayerPrefab : public MovablePrefab
{
public:
    explicit PlayerPrefab(class Game *game, Vector2 position);
};
