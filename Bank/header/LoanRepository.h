#pragma once
#include "BaseRepository.h"
#include "Loan.h"
#include "LoanDatabase.h"

class LoanRepository : public BaseRepository<Loan>
{
public:
	/*Constructors*/
	LoanRepository(LoanDatabase& database);

	Loan* getById(int loanId); //Searchs and returns the given loan id if it exists
};

