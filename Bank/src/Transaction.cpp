#include "Transaction.h"

using namespace std;

int Transaction::nextId = 1;

void Transaction::setNextId(int nextId)
{
	Transaction::nextId = nextId;
}

Transaction::Transaction() {}

Transaction::Transaction(int id, int senderAccountId, int receiverAccountId, double amount, time_t date)
	: BaseEntity(id), senderAccountId(senderAccountId), receiverAccountId(receiverAccountId), amount(amount), date(date)
{
}

Transaction::Transaction(int senderAccountId, int receiverAccountId, double amount, time_t date)
	: senderAccountId(senderAccountId), receiverAccountId(receiverAccountId), amount(amount), date(date)
{
	setId(nextId++);
}

int Transaction::getSenderAccountId() const
{
	return senderAccountId;
}

int Transaction::getReceiverAccountId() const
{
	return receiverAccountId;
}

double Transaction::getAmount() const
{
	return amount;
}

time_t Transaction::getDate() const
{
	return date;
}

string Transaction::toString() const
{
	string transactionStr = "";

	transactionStr += to_string(getId());

	transactionStr += ",";
	transactionStr += to_string(senderAccountId);
	transactionStr += ",";
	transactionStr += to_string(receiverAccountId);
	transactionStr += ",";
	transactionStr += to_string(amount);
	transactionStr += ",";
	transactionStr += to_string(date);

	return transactionStr;
}

Transaction* Transaction::fromString(vector<string> entityStr) const
{
	int id = stoi(entityStr[0]);
	int sender = stoi(entityStr[1]);
	int reciever = stoi(entityStr[2]);
	double amount = stod(entityStr[3]);

	time_t transactionDate = static_cast<time_t>(stol(entityStr[4]));

	Transaction* transaction = new Transaction(sender, reciever, amount, transactionDate);

	return transaction;
}