#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <type_traits>
#include "BaseEntityTemplateCheck.h"
#include <fstream>
#include <sstream>

template<typename T>
class BaseDatabase
{
	static_assert(BaseEntityTemplateCheck<T>::value, "T must be derived from BaseEntity");
private:
	std::string filename;  // CSV file name

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

	std::vector<T*> load()
	{
		std::vector<T*> entities;
		std::ifstream file(filename);
		std::string line;

		while (getline(file, line))
		{
			std::vector<std::string> fields = splitString(line, ',');

			T entity;
			T* createdEntity = entity.fromString(fields);

			entities.push_back(createdEntity);
		}

		file.close();

		return entities;
	}

	void save(std::vector<T>& entities)
	{
		std::ofstream file(filename);

		for (const T& entity : entities)
		{
			std::string csvLine = entity.toString();

			file << csvLine << std::endl;
		}

		file.close();
	}
};