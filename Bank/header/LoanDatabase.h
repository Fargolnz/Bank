#pragma once
#include <string>
#include "BaseDatabase.h"
#include "Loan.h"

class LoanDatabase : public BaseDatabase<Loan>
{
public:
	LoanDatabase();
};

