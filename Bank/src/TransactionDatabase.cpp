#include "../header/TransactionDatabase.h"

using namespace std;

TransactionDatabase::TransactionDatabase(string transactionFilename) : BaseDatabase<Transaction>(transactionFilename) {}