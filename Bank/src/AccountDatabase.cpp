#include "../header/AccountDatabase.h"

using namespace std;

AccountDatabase::AccountDatabase(string accountFilename) : BaseDatabase<Account>(accountFilename) {}