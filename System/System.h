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

protected:
    int mUpdateOrder;
private:
    class Game* mGame;
};