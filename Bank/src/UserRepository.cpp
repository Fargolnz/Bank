#include "../Header/UserRepository.h"

using namespace std;

UserRepository::UserRepository(UserDatabase& database) : BaseRepository<User>(database) {}

User* UserRepository::getByNationalCode(string nationalcode)
{
	for (auto user : entities)
	{
		if (user->getNationalCode() == nationalcode)
			return user;
	}
	return nullptr;
}

User* UserRepository::getById(int id)
{
	for (auto user : entities)
	{
		if (user->getId() == id)
			return user;
	}
	return nullptr;
}