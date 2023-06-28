#include "LoanRepository.h"

LoanRepository::LoanRepository(LoanDatabase& database) : BaseRepository<Loan>(database) {}

Loan* LoanRepository::getById(int loanId)
{
	for (auto loan : entities)
	{
		if (loan->getId() == loanId)
			return loan;
	}
	return nullptr;
}
