#include "../Header/Account.h"

using namespace std;

int Account::nextId = 1;

void Account::setNextId(int nextId)
{
	Account::nextId = nextId;
}

Account::Account() {}

Account::Account(int id, int userId, double balance, AccountTypeEnum type, AccountStatusEnum status, time_t createDate)
	: BaseEntity(id), userId(userId), balance(balance), type(type), status(status), createDate(createDate)
{}

Account::Account(int userId, double balance, AccountTypeEnum type, AccountStatusEnum status, time_t createDate)
	: userId(userId), balance(balance), type(type), status(status), createDate(createDate)
{
	setId(nextId++);
}

int Account::getUserId() const
{
	return userId;
}

double Account::getBalance() const
{
	return balance;
}

AccountTypeEnum Account::getType() const
{
	return type;
}

AccountStatusEnum Account::getStatus() const
{
	return status;
}

time_t Account::getCreateDate() const
{
	return createDate;
}

void Account::setBalance(double balance)
{
	this->balance = balance;
}

void Account::setStatus(AccountStatusEnum status)
{
	this->status = status;
}

string Account::toString() const
{
	string accountToString = "";
	accountToString += to_string(getId());
	accountToString += ",";
	accountToString += to_string(userId);
	accountToString += ",";
	accountToString += to_string(balance);
	accountToString += ",";
	
	switch (type)
	{
		case LongTerm: {accountToString += "LongTerm"; break; }
		case ShortTerm: {accountToString += "ShortTerm"; break; }
		case Current: {accountToString += "Current"; break; }
	}

	accountToString += ",";

	switch (status)
	{
		case Active: {accountToString += "Active"; break; }
		case Pending: {accountToString += "Pending"; break; }
		case Deactive: {accountToString += "Deactive"; break; }
	}

	accountToString += ",";
	long double ld = createDate;
	accountToString += to_string(ld); 
	
	return accountToString;
}

Account* Account::fromString(vector<string> entityFields) const
{
	int id = stoi(entityFields[0]);
	int userId = stoi(entityFields[1]);
	double balance = stod(entityFields[2]);
	AccountTypeEnum type;
	AccountStatusEnum status;

	if (entityFields[3] == "Current")
		type = Current;
	else if (entityFields[3] == "LongTerm")
		type = LongTerm;
	else if (entityFields[3] == "ShortTerm")
		type = ShortTerm;

	if (entityFields[4] == "Active")
		status = Active;
	else if (entityFields[4] == "Pending")
		status = Pending;
	else if (entityFields[4] == "Deactive")
		status = Deactive;

	long long ld = stoll(entityFields[5]);
	std::time_t createDate = ld;

	Account* account = new Account(userId, balance, type, status, createDate);

	return account;
}

Account* Account::fromString_reload(std::vector<std::string> entityFields) const
{
	int id = stoi(entityFields[0]);
	int userId = stoi(entityFields[1]);
	double balance = stod(entityFields[2]);
	AccountTypeEnum type;
	AccountStatusEnum status;

	if (entityFields[3] == "Current")
		type = Current;
	else if (entityFields[3] == "LongTerm")
		type = LongTerm;
	else if (entityFields[3] == "ShortTerm")
		type = ShortTerm;

	if (entityFields[4] == "Active")
		status = Active;
	else if (entityFields[4] == "Pending")
		status = Pending;
	else if (entityFields[4] == "Deactive")
		status = Deactive;

	long long ld = stoll(entityFields[5]);
	std::time_t createDate = ld;

	Account* account = new Account(id,userId, balance, type, status, createDate);

	return account;
}