#include "TransientComponent.h"
#include "AnimComponent.h"

class HittedComponent : public TransientComponent
{
public:
    HittedComponent(Entity *owner, int order, float life) : TransientComponent(owner, order, life), mAnimComponent(nullptr)
    {
        mAnimComponent = mOwner->GetComponent<AnimComponent>();
        if (mAnimComponent != nullptr)
        {
            mAnimComponent->SetState(AnimComponent::EHit);
        }
    }
    virtual void Bury() override
    {
        if (mAnimComponent != nullptr)
        {
            mAnimComponent->SetState(AnimComponent::EIdle);
        }
        mOwner->RemoveComponent(this);
    }

private:
    class AnimComponent *mAnimComponent;
};
