#pragma once
#include <ctime>
#include <string>
#include <list>
#include "BaseEntity.h"
#include "GenderEnum.h"
#include "RoleEnum.h"

class User : public BaseEntity
{

public:
    /*Constructors*/
    User();
    User(int id, const std::string& nationalCode, const std::string& name, const std::string& phone,
        const std::string& password, std::time_t birthDate, std::time_t joinDate,
        GenderEnum gender, RoleEnum role);
    User(const std::string& nationalCode, const std::string& name, const std::string& phone,
        const std::string& password, std::time_t birthDate, std::time_t joinDate,
        GenderEnum gender, RoleEnum role);
    /*Getters*/
    std::string getNationalCode() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getPassword() const;
    std::time_t getBirthDate() const;
    std::time_t getJoinDate() const;
    GenderEnum getGender() const;
    RoleEnum getRole() const;
    /*Setters*/
    void setPassword(std::string password);
    void setPhone(std::string phone);
    static void setNextId(int nextId);
    
    User* fromString(std::vector<std::string> entityFields) const override;	// Reads User object from the file.
    User* fromString_reload(std::vector<std::string> entityFields) const override;  // Reads User object from the file(except id).
    
    std::string toString() const override;  // Writes User object to the file.

private:
	std::string nationalCode;
	std::string name;
	std::string phone;
	std::string password;
	std::time_t birthDate;
	std::time_t joinDate;
	GenderEnum gender;
	RoleEnum role;
    static int nextId;
};

