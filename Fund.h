#ifndef FUND_H_
#define FUND_H_
#include <string>
#include <vector>
#include "Transaction.h"
using namespace std;

class Fund
{
    public:
        Fund();
        Fund(string fund_name, int fundID);

        bool AddBalance(int amount);
        bool DeductBalance(int amount);

        void RecordsOnFund(Transaction trans);
        void ShowHistory();
        void FinalBalanceHistory();

        int getBalance() const;
        string getFundName() const;


        

    private:
        string fund_name_;
        int fund_id_;
        int balance_;
        vector <Transaction> transaction_records_;
};

#endif