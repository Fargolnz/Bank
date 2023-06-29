#include "../Header/AccountDatabase.h"

using namespace std;

AccountDatabase::AccountDatabase() : BaseDatabase<Account>("../x64/Debug/Accounts.txt") {}