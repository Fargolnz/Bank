#pragma once
#include "BaseRepository.h"
#include "Transaction.h"
#include "TransactionDatabase.h"

class TransactionRepository : public BaseRepository<Transaction>
{
public:
	TransactionRepository(TransactionDatabase& database);
};

