#include "AccountRepository.h"

AccountRepository::AccountRepository(AccountDatabase& database) : BaseRepository<Account>(database) {}

bool AccountRepository::SearchAccountId(int accountId)
{
	for (auto account : entities)
	{
		if (account->getId() == accountId)
			return true;
	}
	return false;
}

bool AccountRepository::CheckAmount(int senderAccountId, int amount)
{
	Account account = this->get(senderAccountId);
	if (account.getBalance() >= amount)
	{
		return true;
	}
	return false;
}

void AccountRepository::Withdraw(int senderAccountId, int amount)
{
	Account account = this->get(senderAccountId);
	account.setBalance(account.getBalance()-amount);
}

void AccountRepository::Deposit(int receiverAccountId, int amount)
{
	Account account = this->get(receiverAccountId);
	account.setBalance(account.getBalance() + amount);
}
