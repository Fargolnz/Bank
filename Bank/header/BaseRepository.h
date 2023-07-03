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
    
    
    void init() // Loads objects from hard drive to memory.
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

    
    void add(T& entity) // Adds the new object to loaded entities.
    {
        entities.push_back(&entity);
    }

    
    void remove(int entityId)   // Delets the intended object from loaded entities.
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

    
    T get(int entityId) // Returns the address of the object.
    {
        for (T* entity : entities)
        {
            if (entity->getId() == entityId)
            {
                return *entity;
            }
        }
    }

    
    vector<T*> getAll() // Returns the loaded entities.
    {
        return entities;
    }

    
    void save() // Saves the loaded entities and their changes to the file.
    {
        database.save(entities);
    }

    
    void reloadEntities()   // Reloads entities from the file.
    {
        entities = database.reload();
    }
};