
// This header checks whether T is valid or not.

#pragma once
#include "BaseEntity.h"

template <typename T>
struct BaseEntityTemplateCheck 
{
    static constexpr bool value = std::is_base_of<BaseEntity, T>::value;
};