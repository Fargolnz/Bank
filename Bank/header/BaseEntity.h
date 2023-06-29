#pragma once
#include <string>
#include <vector>
class BaseEntity
{
public:
	BaseEntity();
	BaseEntity(int id);

	int getId() const;

	// Read object from file.
	virtual BaseEntity* fromString(std::vector<std::string> entityFields) const = 0;
	virtual BaseEntity* fromString_reload(std::vector<std::string> entityFields) const = 0;
	// Write object to file.
	virtual std::string toString() const = 0;

protected:
	int id;

	void setId(int id)
	{
		this->id = id;
	}
};