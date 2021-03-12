#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <string>
#include "Fund.h"
using namespace std;


class Account
{
    friend ostream& operator<<(ostream& stream, const Account& account);

    public:
        Account();
        ~Account();
        Account(const Account &acct);
        Account(int id, string firstName, string lastName);

        //void Open();
        bool Deposit(int fundID, int amount);
        bool Transfer();
        bool Withdraw(int fundID, int amount, Transaction trans);
        bool WithdrawFromLinkedFunds(int accountNum, int amount);
        void ErrorMessege(int amount, int fundID, Transaction trans);

        void RecordTransaction(Transaction trans, int fundID);

        // Accessors
        string getFirstName() const;
        string getLastName() const;
        int getAccountID() const;


        void DisplayFundHistory(int acctNum);
        void DisplayAllFundsHistory();


    private:
        string lastName_;
        string firstName_;
        int account_id_;    
        int fundID_;    
        Fund fund [10];                
};

#endif