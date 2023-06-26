#pragma once
#include "BaseRepository.h"
#include "AccountDatabase.h"
#include "Account.h"

class AccountRepository : public BaseRepository<Account>
{
public:
	AccountRepository(AccountDatabase& database);
	bool SearchAccountId(int accountId);
	bool CheckAmount(int senderAccountId, int amount);
	void Withdraw(int senderAccountId, int amount);
	void Deposit(int receiverAccountId, int amount);
};