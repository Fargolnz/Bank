#pragma once
#include <string>
#include "BaseDatabase.h"
#include "User.h"

class UserDatabase : public BaseDatabase<User>
{
public:
	UserDatabase(std::string usersFilename);
};

