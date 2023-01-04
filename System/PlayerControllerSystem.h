#pragma once
#include "System.h"

class PlayerControllerSystem : System
{
public:
    explicit PlayerControllerSystem(Game* game, int updateorder) : System(game, updateorder), mPlayer(nullptr), mWeapon(nullptr), mPMC(nullptr) {}
    ~PlayerControllerSystem();
    void SetPlayer(class Entity* player);
    void SetupWeapon(int playerJob);
    const class Entity* GetWeapon() const;
    void DestroyWeapon();
    void Update(float deltaTime) override;
    void CleanUp() override { mWeapon = nullptr; }

private:
    class Entity* mPlayer;
    class Entity* mWeapon;
    class MoveComponent* mPMC;
    class MoveComponent* mWMC;
    class AttackComponent* mAttackComponent;
};