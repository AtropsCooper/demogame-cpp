#pragma once

namespace Helper
{
    template<typename T>
    inline static bool IsComponent(class Component const* c)
    {
        if (dynamic_cast<const T*>(c) != nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}