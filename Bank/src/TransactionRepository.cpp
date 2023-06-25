#include "TransactionRepository.h"

TransactionRepository::TransactionRepository(TransactionDatabase& database) : BaseRepository<Transaction>(database) {}