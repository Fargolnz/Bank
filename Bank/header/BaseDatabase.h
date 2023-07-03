#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <fstream>
#include <sstream>
#include "BaseEntityTemplateCheck.h"

template<typename T>
class BaseDatabase
{
	// Checks whether T is valid or not.
	static_assert(BaseEntityTemplateCheck<T>::value, "T must be derived from BaseEntity");
private:
	std::string filename;  // CSV file name

	// This function splits the given string according to its delimiter.
	std::vector<std::string> splitString(const std::string& str, char delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(str);

		while (getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}

		return tokens;
	}

public:
	BaseDatabase(std::string filename) : filename(filename) {}

	
	std::vector<T*> load()	// Load objects from the file.
	{
		std::vector<T*> entities;
		std::ifstream file(filename);
		std::string line;

		if (file.is_open())
			while (getline(file, line))
			{
				if (line.empty())
					continue;
				std::vector<std::string> fields = splitString(line, ',');

				T entity;
				T* createdEntity = entity.fromString(fields);		// Creates object from given tokens

				entities.push_back(createdEntity);
			}

		file.close();

		return entities;
	}

	
	void save(std::vector<T*> entities)	// Saves objects to the file.
	{
		std::ofstream file(filename);

		for (const T* entity : entities)
		{
			std::string csvLine = entity->toString();

			file << csvLine << std::endl;
		}

		file.close();
	}

	
	std::vector<T*> reload()	// Reloads objects from the file.
	{
		std::vector<T*> entities;
		std::ifstream file(filename);
		std::string line;

		if (file.is_open())
			while (getline(file, line))
			{
				if (line.empty())
					continue;
				std::vector<std::string> fields = splitString(line, ',');

				T entity;
				T* createdEntity = entity.fromString_reload(fields);		// Creates object from given tokens

				entities.push_back(createdEntity);
			}

		file.close();

		return entities;
	}
};