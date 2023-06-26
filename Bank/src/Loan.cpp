#include "Loan.h"

using namespace std;

int Loan::nextId = 1;

void Loan::setNextId(int nextId)
{
	Loan::nextId = nextId;
}

Loan::Loan() {}

Loan::Loan(int id, int accountId, double totalAmount, double leftAmount, double rate, std::time_t createDate)
	: BaseEntity(id), accountId(accountId), totalAmount(totalAmount), leftAmount(leftAmount), rate(rate), createDate(createDate)
{}

Loan::Loan(int accountId, double totalAmount, double leftAmount, double rate, std::time_t createDate)
	: accountId(accountId), totalAmount(totalAmount), leftAmount(leftAmount), rate(rate), createDate(createDate)
{
	setId(nextId++);
}

int Loan::getAccountId() const
{
	return accountId;
}

double Loan::getTotalAmount() const
{
	return totalAmount;
}

double Loan::getLeftAmount() const
{
	return leftAmount;
}

double Loan::getRate() const
{
	return rate;
}

time_t Loan::getCreateDate() const
{
	return createDate;
}


string Loan::toString() const
{
	string loanToString = "";
	loanToString += to_string(this->getId());
	loanToString += ",";
	loanToString += to_string(this->accountId);
	loanToString += ",";
	loanToString += to_string(this->totalAmount);
	loanToString += ",";
	loanToString += to_string(this->leftAmount);
	loanToString += ",";
	loanToString += to_string(this->rate);
	loanToString += ",";
	long long longDate = this->createDate;
	loanToString += to_string(longDate);

	return loanToString;
}

Loan* Loan::fromString(vector<string> entityFields) const
{
	int id = stoi(entityFields[0]);
	int accountId = stoi(entityFields[1]);
	double totalAmount = stod(entityFields[2]);
	double leftAmount = stod(entityFields[3]);
	double rate = stod(entityFields[4]);
	long long longDate = stoll(entityFields[5]);
	std::time_t createDate = longDate;

	Loan* loan = new Loan(id, accountId, totalAmount, leftAmount, rate, createDate);

	return loan;
}