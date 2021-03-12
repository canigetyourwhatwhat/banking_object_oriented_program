#ifndef TRANSACTION_H_
#define TRANSACTION_H_


#include <string>
#include <iostream>
using namespace std;

class Transaction
{
    friend ostream& operator<<(ostream& stream, const Transaction& transaction);

    public:
        Transaction();        
        
        Transaction(char initial, string firstName, string lastName, int num);
        Transaction(char initial, int account, int amount, int fundID, bool result);
        Transaction(char initial, int from, int fromID, int amount, int to, int toID, bool result);
        Transaction(char initial, int account, int fundID);
        Transaction(char initial, int account);

        // Accesssors
        char getInitial() const;
        string getFirstName() const;
        string getLastName() const;
        int getAccountNum() const;
        int getAmount() const;
        int getFundID() const;
        void setResult(bool result);
        int getToFundID() const;
        int getToAccount() const;
        


    private:
        char initial_;
        string lastName_, firstName_;
        string result_;
        int account_, fundID_, toFundID_, toAccount_, amount_;
};

#endif