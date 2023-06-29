#include "../Header/AccountRepository.h"

AccountRepository::AccountRepository(AccountDatabase& database) : BaseRepository<Account>(database) {}

Account* AccountRepository::getById(int id)
{
	for (auto account : entities)
	{
		if (account->getId() == id)
			return account;
	}
	return nullptr;
}

bool AccountRepository::SearchAccountId(int accountId)
{
	for (auto account : entities)
	{
		if (account->getId() == accountId)
			return true;
	}
	return false;
}

bool AccountRepository::CheckAmount(int senderAccountId, double amount)
{
	Account* account = this->getById(senderAccountId);
	if (account->getBalance() >= amount)
	{
		return true;
	}
	return false;
}

bool AccountRepository::CheckStatus(int accountId)
{
	Account* account = this->getById(accountId);
	if (account->getStatus() == Active)
	{
		return true;
	}
	return false;
}

void AccountRepository::Withdraw(int senderAccountId, double amount)
{
	Account* account = this->getById(senderAccountId);
	account->setBalance(account->getBalance() - amount);
	this->save();
	this->reloadEntities();
}

void AccountRepository::Deposit(int receiverAccountId, double amount)
{
	Account* account = this->getById(receiverAccountId);
	account->setBalance(account->getBalance() + amount);
	this->save();
	this->reloadEntities();
}
