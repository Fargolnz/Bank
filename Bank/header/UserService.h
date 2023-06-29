#pragma once
#include "AccountRepository.h"
#include "LoanRepository.h"
#include "TransactionRepository.h"
#include "UserRepository.h"
#include "UserSession.h"
#include "StringHasher.h"

class UserService
{
public:
	UserService(UserRepository& userRepository, AccountRepository& accountRepository, TransactionRepository& transactionRepository, LoanRepository& loanRepository);
	UserSession login(std::string nationalcode, std::string password, int role, bool* is_loggedin);
	void logout(bool* is_loggedin);
	static void PasswordManipulator(std::string& password);
	void unixToDatetime(time_t unix);
	void AddUser(RoleEnum);
	void NewAccount(int userId);
	void NewTransaction(UserSession userSession);
	void NewLoan(int accountId);
	void ShowEmployees();
	void ShowCustomers();
	bool ShowAllAccounts(AccountStatusEnum status);
	void ShowAccounts(int userId);
	void ShowTransactions(UserSession userSession, int accountId);
	void ShowAllLoans(LoanStatusEnum status);
	void ShowLoans(int accountId);
	void ChangeAccountStatus();
	void ChangeLoanStatus();
	void Deposit(int accountId);
	void CloseAccount(int userId);
	void ChangeUserPassword(int userId);
	void ChangePhone(int userId);
	void DeleteUser(RoleEnum role);
	void CheckBalance(int accountId);
private:
	UserRepository& userRepository;
	AccountRepository& accountRepository;
	TransactionRepository& transactionRepository;
	LoanRepository& loanRepository;
};

