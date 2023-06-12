#include "../header/LoanDatabase.h"

using namespace std;

LoanDatabase::LoanDatabase(string loanFilename) : BaseDatabase<Loan>(loanFilename) {}