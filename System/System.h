#pragma once
#include <vector>

class System
{
public:
    System(class Game* game, int updateOrder);
    virtual ~System();
    virtual void FetchComponents() {};
    virtual void Update(float deltaTime) {};
    int GetUpdateOrder() const { return mUpdateOrder; }
    Game* GetGame() const { return mGame; }

    template <typename T>
    void DetectComponent(std::vector<T *> *container);
    virtual void CleanUp() {}

protected:
    int mUpdateOrder;
    class Game* mGame;
};