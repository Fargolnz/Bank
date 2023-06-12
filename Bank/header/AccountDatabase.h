#pragma once
#include <string>
#include "BaseDatabase.h"
#include "Account.h"

class AccountDatabase : public BaseDatabase<Account>
{
public:
	AccountDatabase(std::string accountFileName);
};

