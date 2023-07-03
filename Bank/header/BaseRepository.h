#pragma once
#include <type_traits>
#include <vector>
#include "BaseDatabase.h"
#include "BaseEntityTemplateCheck.h"

using std::vector;

template<typename T>
class BaseRepository
{
    // Checks whether T is valid or not.
    static_assert(BaseEntityTemplateCheck<T>::value, "T must be derived from BaseEntity");

private:
    bool isInitialized;

protected:
    BaseDatabase<T>& database;
    vector<T*> entities;

public:
    BaseRepository(BaseDatabase<T>& database) : database(database), isInitialized(false) {};
    
    // Loads objects from hard drive to ram.
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

    // Adds the new object to loaded entities.
    void add(T& entity)
    {
        entities.push_back(&entity);
    }

    // Delets the intended object from loaded entities.
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

    // Returns the address of the object.
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

    // Returns the loaded entities.
    vector<T*> getAll()
    {
        return entities;
    }

    // Saves the loaded entities and their changes to the file.
    void save()
    {
        database.save(entities);
    }

    // Reloads entities from the file.
    void reloadEntities()
    {
        entities = database.reload();
    }
};