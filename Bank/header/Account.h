#pragma once
#include <ctime>
#include "BaseEntity.h"
#include "AccountTypeEnum.h"
#include "AccountStatusEnum.h"

class Account : public BaseEntity
{
public:
	/*Constructors*/
	Account();
	Account(int id, int userId, double balance, AccountTypeEnum type, AccountStatusEnum status, std::time_t createDate);
	Account(int userId, double balance, AccountTypeEnum type, AccountStatusEnum status, std::time_t createDate);
	/*Getters*/
	int getUserId() const;
	double getBalance() const;
	AccountTypeEnum getType() const;
	AccountStatusEnum getStatus() const;
	std::time_t getCreateDate() const;
	/*Setters*/
	void setBalance(double balance);
	void setStatus(AccountStatusEnum status);
	static void setNextId(int nextId);

	
	Account* fromString(std::vector<std::string> entityFields) const override; //Reads Account object from the file.
	Account* fromString_reload(std::vector<std::string> entityFields) const override;	//Reads Account object from the file(except id).

	std::string toString() const override; 	//Writes Account object from the file.

private:
	int userId;
	double balance;
	AccountTypeEnum type;
	std::time_t createDate;
	static int nextId;
	AccountStatusEnum status;
};

