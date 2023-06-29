#pragma once
#include "BaseRepository.h"
#include "AccountDatabase.h"
#include "Account.h"

class AccountRepository : public BaseRepository<Account>
{
public:
	AccountRepository(AccountDatabase& database);
	Account* getById(int id);
	bool SearchAccountId(int accountId);
	bool CheckAmount(int senderAccountId, double amount);
	bool CheckStatus(int accountId);
	void Withdraw(int senderAccountId, double amount);
	void Deposit(int receiverAccountId, double amount);
};