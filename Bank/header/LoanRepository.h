#pragma once
#include "BaseRepository.h"
#include "Loan.h"
#include "LoanDatabase.h"

class LoanRepository : public BaseRepository<Loan>
{
public:
	LoanRepository(LoanDatabase& database);
	Loan* getById(int loanId);
};

