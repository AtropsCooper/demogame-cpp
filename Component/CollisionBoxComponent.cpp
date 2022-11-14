#include "CollisionBoxComponent.h"

CollisionBoxComponent::CollisionBoxComponent(class Entity* owner, int updateOrder)
    : Component(owner, updateOrder)
    , mWidth(0.0f)
    , mHeight(0.0f)
    , mOffset(0, 0)
{

}