#pragma once
#include "BaseRepository.h"
#include "UserDatabase.h"
#include "User.h"

class UserRepository : public BaseRepository<User>
{
public:
	/*Constructor*/
	UserRepository(UserDatabase& database);

	User* getByNationalCode(std::string nationalcode);	//Searchs and returns the user (by national code).
	User* getById(int id); //Searchs and returns the user (by id).
};

