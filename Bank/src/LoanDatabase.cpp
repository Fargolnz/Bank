#include "../Header/LoanDatabase.h"

using namespace std;

LoanDatabase::LoanDatabase() : BaseDatabase<Loan>("../x64/Debug/Loans.txt") {}