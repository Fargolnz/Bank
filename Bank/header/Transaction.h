#pragma once
#include <vector>
#include "BaseEntity.h"
#include <ctime>

class Transaction :public BaseEntity
{
private:
	int senderAccountId;
	int receiverAccountId;
	double amount;
	std::time_t date;
	static int nextId;

public:
	Transaction();
	Transaction(int id, int senderAccountId, int receiverAccountId, double amount, std::time_t date);
	Transaction(int senderAccountId, int receiverAccountId, double amount, std::time_t date);

	int getSenderAccountId() const;
	int getReceiverAccountId() const;
	double getAmount() const;
	std::time_t getDate() const;

	static void setNextId(int nextId);

	Transaction* fromString(std::vector<std::string> entityFields) const override;
	std::string toString() const override;
};

