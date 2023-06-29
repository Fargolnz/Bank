#include "../Header/UserDatabase.h"

using namespace std;

UserDatabase::UserDatabase() : BaseDatabase<User>("../x64/Debug/Users.txt") {}