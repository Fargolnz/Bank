#pragma once
#include "BaseEntity.h"
#include <ctime>

class Loan : public BaseEntity
{
public:
	Loan();
	Loan(int id, int accountId, double totalAmount, double leftAmount, double rate, std::time_t createDate);
	Loan(int accountId, double totalAmount, double leftAmount, double rate, std::time_t createDate);

	int getAccountId() const;
	double getTotalAmount() const;
	double getLeftAmount() const;
	double getRate() const;
	std::time_t getCreateDate() const;

	static void setNextId(int nextId);

	Loan* fromString(std::vector<std::string> entityFields) const override;
	std::string toString() const override;

private:
	int accountId;
	double totalAmount;
	double leftAmount;
	double rate;
	std::time_t createDate;
	static int nextId;
};

