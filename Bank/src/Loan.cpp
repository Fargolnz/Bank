#include "../Header/Loan.h"

using namespace std;

int Loan::nextId = 1;

void Loan::setNextId(int nextId)
{
	Loan::nextId = nextId;
}

Loan::Loan() {}

Loan::Loan(int id, int accountId, double totalAmount, double leftAmount, double rate, LoanStatusEnum status, std::time_t createDate)
	: BaseEntity(id), accountId(accountId), totalAmount(totalAmount), leftAmount(leftAmount), rate(rate), status(status), createDate(createDate)
{}

Loan::Loan(int accountId, double totalAmount, double leftAmount, double rate = 20, LoanStatusEnum status = Awaitence, std::time_t createDate = time(nullptr))
	: accountId(accountId), totalAmount(totalAmount), leftAmount(leftAmount), rate(rate), status(status), createDate(createDate)
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

LoanStatusEnum Loan::getStatus() const
{
	return status;
}

time_t Loan::getCreateDate() const
{
	return createDate;
}

void Loan::setStatus(LoanStatusEnum status)
{
	this->status = status;
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

	switch (status)
	{
		case Accepted: {loanToString += "Accepted"; break; }
		case Awaitence: {loanToString += "Awaitence"; break; }
		case Declined: {loanToString += "Declined"; break; }
	}

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
	LoanStatusEnum status;

	if (entityFields[5] == "Accepted")
		status = Accepted;
	else if (entityFields[5] == "Awaitence")
		status = Awaitence;
	else if (entityFields[5] == "Declined")
		status = Declined;

	long long longDate = stoll(entityFields[6]);
	std::time_t createDate = longDate;

	Loan* loan = new Loan(accountId, totalAmount, leftAmount, rate, status, createDate);

	return loan;
}