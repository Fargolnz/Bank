#pragma once
#include "BaseRepository.h"
#include "AccountDatabase.h"
#include "Account.h"

class AccountRepository : public BaseRepository<Account>
{
public:
	/*Constructor*/
	AccountRepository(AccountDatabase& database);
	/*Getter*/
	Account* getById(int id);

	bool SearchAccountId(int accountId);	//Searches an account id if its find or not.
	bool CheckAmount(int senderAccountId, double amount);	//Checks if the given amount is more than the current balance of the given id or not.
	bool CheckStatus(int accountId);	//Checks if the given account (by id) status is active or not.
	void Withdraw(int senderAccountId, double amount);	//Withdraws the given amount from the given account (by id).
	void Deposit(int receiverAccountId, double amount); //Deposits the given amount to the given account (by id).
};