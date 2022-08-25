#pragma once
#include "System.h"

class PlayerControllerSystem : System
{
public:
    explicit PlayerControllerSystem(Game* game, int updateorder) : System(game, updateorder), mPlayer(nullptr), mWeapon(nullptr), mPMC(nullptr) {}
    ~PlayerControllerSystem();
    void SetPlayer(class Entity* player);
    void SetupWeapon(int playerJob);
    void DestroyWeapon();
    void Update(float deltaTime) override;

private:
    class Entity* mPlayer;
    class Entity* mWeapon;
    class MoveComponent* mPMC;
    class MoveComponent* mWMC;
};