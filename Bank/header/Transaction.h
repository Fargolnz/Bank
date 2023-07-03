#pragma once
#include <vector>
#include "BaseEntity.h"
#include <ctime>

class Transaction :public BaseEntity
{

public:
	/*Constructors*/
	Transaction();
	Transaction(int id, int senderAccountId, int receiverAccountId, double amount, std::time_t date);
	Transaction(int senderAccountId, int receiverAccountId, double amount, std::time_t date);
	/*Getters*/
	int getSenderAccountId() const;
	int getReceiverAccountId() const;
	double getAmount() const;
	std::time_t getDate() const;
	/*Setter*/
	static void setNextId(int nextId);

	Transaction* fromString(std::vector<std::string> entityFields) const override;	// Reads Transaction object from the file.
	Transaction* fromString_reload(std::vector<std::string> entityFields) const override; 	// Reads object from the file(except id).
	
	std::string toString() const override;	// Writes Transaction object to the file.

private:
	int senderAccountId;
	int receiverAccountId;
	double amount;
	std::time_t date;
	static int nextId;
};

