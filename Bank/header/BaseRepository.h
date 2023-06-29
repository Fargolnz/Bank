#pragma once
#include <type_traits>
#include <vector>
#include "BaseDatabase.h"
#include "BaseEntityTemplateCheck.h"

using std::vector;

template<typename T>
class BaseRepository
{
    static_assert(BaseEntityTemplateCheck<T>::value, "T must be derived from BaseEntity");

private:
    bool isInitialized;

protected:
    BaseDatabase<T>& database;
    vector<T*> entities;

public:
    BaseRepository(BaseDatabase<T>& database) : database(database), isInitialized(false) {};
    
    void init()
    {
        if (!isInitialized)
        {
            vector<T*> loadedEntities = database.load();

            for (auto entity : loadedEntities)
            {
                entities.push_back(entity);
            }

            isInitialized = true;
        }
    }

    void add(T& entity)
    {
        entities.push_back(&entity);
    }

    void remove(int entityId)
    {
        for (auto it = entities.begin(); it != entities.end(); ++it)
        {
            if ((*it)->getId() == entityId)
            {
                entities.erase(it);
                break;
            }
        }
    }

    T get(int entityId)
    {
        for (T* entity : entities)
        {
            if (entity->getId() == entityId)
            {
                return *entity;
            }
        }
    }

    vector<T*> getAll()
    {
        return entities;
    }

    void save()
    {
        database.save(entities);
    }

    void reloadEntities()
    {
        entities = database.reload();
    }
};