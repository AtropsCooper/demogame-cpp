#pragma once

class System
{
public:
    System(class Game* game, int updateOrder);
    virtual ~System();
    virtual void Update(float deltaTime);
    int GetUpdateOrder() const { return mUpdateOrder; }
    Game* GetGame() const { return mGame; }
protected:
    int mUpdateOrder;
private:
    class Game* mGame;
};