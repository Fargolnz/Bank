#pragma once
#include <string>
#include <vector>
class BaseEntity
{
public:
	/*Constructors*/
	BaseEntity();
	BaseEntity(int id);
	/*Getters*/
	int getId() const;

	virtual BaseEntity* fromString(std::vector<std::string> entityFields) const = 0;		// Reads object from the file.
	virtual BaseEntity* fromString_reload(std::vector<std::string> entityFields) const = 0;	// Reads object from the file(except id).

	virtual std::string toString() const = 0;	// Writes object to the file.

protected:
	int id;

	void setId(int id)
	{
		this->id = id;
	}
};