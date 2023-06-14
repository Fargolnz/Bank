#pragma once
#include <ctime>
#include "BaseEntity.h"
#include "AccountTypeEnum.h"

class Account : public BaseEntity
{
public:
	Account();
	Account(int id, int userId, double balance, AccountTypeEnum type, std::time_t createDate);
	Account(int userId, double balance, AccountTypeEnum type, std::time_t createDate);

	int getUserId() const;
	double getBalance() const;
	AccountTypeEnum getType() const;
	std::time_t getCreateDate() const;

	static void setNextId(int nextId);

	Account* fromString(std::vector<std::string> entityFields) const override;
	std::string toString() const override;

private:
	int userId;
	double balance;
	AccountTypeEnum type;
	std::time_t createDate;
	static int nextId;
};

