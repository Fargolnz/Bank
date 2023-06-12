#include "../header/BaseEntity.h"

BaseEntity::BaseEntity() {}
BaseEntity::BaseEntity(int id) : id(id) {}

int BaseEntity::getId() const 
{
    return id;
}