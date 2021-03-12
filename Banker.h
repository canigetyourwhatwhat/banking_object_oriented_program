#ifndef BANKER_H_
#define BANKER_H_

#include "Transaction.h"
#include "BSTree.h"
#include <queue>

class Banker
{
    public:
        Banker();

        void ReadFile();
        void executeTransactions();
        void FinalBalance();

    private:
        queue <Transaction> records;
        BSTree tree;
};

#endif