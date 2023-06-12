#pragma once
#include <string>
#include "BaseDatabase.h"
#include "Transaction.h"

class TransactionDatabase : public BaseDatabase<Transaction>
{
public:
	TransactionDatabase(std::string transactionFilename);
};

