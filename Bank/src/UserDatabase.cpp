#include "../header/UserDatabase.h"

using namespace std;

UserDatabase::UserDatabase(string usersFilename) : BaseDatabase<User>(usersFilename) {}