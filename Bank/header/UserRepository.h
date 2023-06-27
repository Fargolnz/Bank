#pragma once
#include "BaseRepository.h"
#include "UserDatabase.h"
#include "User.h"

class UserRepository : public BaseRepository<User>
{
public:
	UserRepository(UserDatabase& database);
	User* getByNationalCode(std::string nationalcode);
	User* getById(int id);
};

