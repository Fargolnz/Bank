#include "LoanRepository.h"

LoanRepository::LoanRepository(LoanDatabase& database) : BaseRepository<Loan>(database) {}