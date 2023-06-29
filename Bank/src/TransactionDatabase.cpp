#include "../Header/TransactionDatabase.h"

using namespace std;

TransactionDatabase::TransactionDatabase() : BaseDatabase<Transaction>("../x64/Debug/Transactions.txt") {}