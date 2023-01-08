#include "CollisionBoxComponent.h"
#include "Entity.h"

CollisionBoxComponent::CollisionBoxComponent(class Entity *owner, int updateOrder)
    : Component(owner, updateOrder), mWidth(0.0f), mHeight(0.0f), mOffset(0, 0)
{
}

Vector2 CollisionBoxComponent::GetPosition()
{
    Vector2 pos(mOwner->mPosition.x + mOffset.x - mWidth * 0.5f, mOwner->mPosition.y + mOffset.y + mHeight * 0.5f);
    return pos;
}

float CollisionBoxComponent::GetLeft()
{
    float res = GetPosition().x - mWidth * 0.5f;
    return res;
}

float CollisionBoxComponent::GetRight()
{
    float res = GetPosition().x + mWidth * 0.5f;
    return res;
}

float CollisionBoxComponent::GetTop()
{
    float res = GetPosition().y + mHeight * 0.5f;
    return res;
}

float CollisionBoxComponent::GetBottom()
{
    float res = GetPosition().y - mHeight * 0.5f;
    return res;
}