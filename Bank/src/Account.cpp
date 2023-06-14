#include "Account.h"

using namespace std;

int Account::nextId = 1;

void Account::setNextId(int nextId)
{
	Account::nextId = nextId;
}

Account::Account() {}

Account::Account(int id, int userId, double balance, AccountTypeEnum type, time_t createDate)
	: BaseEntity(id), userId(userId), balance(balance), type(type), createDate(createDate)
{}

Account::Account(int userId, double balance, AccountTypeEnum type, time_t createDate)
	: userId(userId), balance(balance), type(type), createDate(createDate)
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

time_t Account::getCreateDate() const
{
	return createDate;
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
		case ShortTerm: {accountToString += "ShorTerm"; break;}
		case Current: {accountToString += "Current"; break; }
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

	if (entityFields[3] == "Current")
		type = Current;
	else if (entityFields[3] == "LongTerm")
		type = LongTerm;
	else if (entityFields[3] == "ShortTerm")
		type = ShortTerm;

	long long ld = stoll(entityFields[4]);
	std::time_t createDate = ld;

	Account* account = new Account(userId, balance, type, createDate);


	return account;
}
