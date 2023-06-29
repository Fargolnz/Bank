#pragma once
#include <ctime>
#include "BaseEntity.h"
#include "LoanStatusEnum.h"

class Loan : public BaseEntity
{
public:
	Loan();
	Loan(int id, int accountId, double totalAmount, double leftAmount, double rate, LoanStatusEnum status, std::time_t createDate);
	Loan(int accountId, double totalAmount, double leftAmount, double rate, LoanStatusEnum status, std::time_t createDate);

	int getAccountId() const;
	double getTotalAmount() const;
	double getLeftAmount() const;
	double getRate() const;
	LoanStatusEnum getStatus() const;
	std::time_t getCreateDate() const;
	void setStatus(LoanStatusEnum status);

	static void setNextId(int nextId);

	Loan* fromString(std::vector<std::string> entityFields) const override;
	Loan* fromString_reload(std::vector<std::string> entityFields) const override;

	std::string toString() const override;

private:
	int accountId;
	double totalAmount;
	double leftAmount;
	double rate;
	LoanStatusEnum status;
	std::time_t createDate;
	static int nextId;
};

