#ifndef TRANSACTION_CPP_
#define TRANSACTION_CPP_
#include "Transaction.h"

Transaction::Transaction()
{

}





// For O
Transaction::Transaction(char letter, string firstName, string lastName, int account)
{
    initial_ = letter;
    firstName_ = firstName;
    lastName_ = lastName;
    account_ = account;
}

// For W and D
Transaction::Transaction(char letter, int account, int amount, int fundID, bool result)
{
    initial_ = letter;
    account_ = account;
    amount_ = amount; 
    fundID_ = fundID;
    if(!result)
    {
        result_ = " (Failed)";
    }
}

// For T
Transaction::Transaction(char letter, int from, int fromFundID, int amount, int to, int toFundID, bool result)
{
    initial_ = letter;
    account_ = from;
    fundID_ = fromFundID;
    toAccount_ = to;
    toFundID_ = toFundID;
    amount_ = amount;
    if(!result)
    {
        result_ = " (Failed)";
    }
}

// For H
Transaction::Transaction(char initial, int account)
{
    initial_ = initial;
    account_ = account;
}

Transaction::Transaction(char initial, int account, int fundID)
{
    initial_ = initial;
    account_ = account;
    fundID_ = fundID;
}






// Accessors
string Transaction::getFirstName() const
{
    return firstName_;
}

string Transaction::getLastName() const
{
    return lastName_;
}

int Transaction::getAccountNum() const
{
    return account_;
}

int Transaction::getAmount() const
{
    return amount_;
}

char Transaction::getInitial() const
{
    return initial_;
}

int Transaction::getFundID() const
{
    return fundID_;
}

void Transaction::setResult(bool result)
{
    if(!result)
    {
        result_ = "(Failed)";
    }
}

int Transaction::getToFundID() const
{
    return toFundID_;
}

int Transaction::getToAccount() const
{
    return toAccount_;
}



ostream& operator<<(ostream& stream, const Transaction& trans)
{
    if(trans.result_.empty())
    {
        if(trans.initial_ == 'W' || trans.initial_ == 'D')
        {
            stream << trans.initial_ << " " << trans.account_ << trans.fundID_ <<" " << trans.amount_ << endl;
        }
        else if(trans.initial_ == 'T')
        {
            stream << trans.initial_ << " " << trans.account_ << trans.fundID_ << " " << trans.amount_ << " " << trans.toAccount_ << trans.toFundID_ << endl;
        }
    }
    else
    {
        
        if(trans.initial_ == 'W' || trans.initial_ == 'D')
        {
            stream << trans.initial_ << " " << trans.account_ << trans.fundID_ << " " << trans.amount_ << " " << trans.result_ << endl;
        }
        else if(trans.initial_ == 'T')
        {
            stream << trans.initial_ << " " << trans.account_ << trans.fundID_ <<" " << trans.amount_ << " " << trans.toAccount_ << trans.toFundID_ << " " << trans.result_ << endl;
        }
        
    }    
    return stream;
}


#endif