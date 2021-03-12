#ifndef FUND_CPP_
#define FUND_CPP_
#include <string>
#include <vector>
#include "Fund.h"


Fund::Fund()
{

}

Fund::Fund(string fund_name, int fundID)
{
    fund_name_ = fund_name;
    fund_id_ = fundID;
    balance_ = 0;
}

void Fund::RecordsOnFund(Transaction trans)
{
    transaction_records_.push_back(trans);
}




bool Fund::AddBalance(int amount)
{
    balance_+= amount;
    return true;
}

bool Fund::DeductBalance(int amount)
{    
    if(balance_ - amount >= 0)
    {
        balance_ -= amount;
        return true;
    }
    else
    {
        return false;
    }    
}



void Fund::ShowHistory()
{
    if(!transaction_records_.empty())
    {
        for(int i=0; i < transaction_records_.size(); i++)
        {
            cout << "  " << transaction_records_[i];
        }
        
    }    
}

void Fund::FinalBalanceHistory()
{
    if(!transaction_records_.empty())
    {
        cout << fund_name_ << ": $" << balance_ << endl;
    }
}



int Fund::getBalance() const
{
    return balance_;
}

string Fund::getFundName() const
{
    return fund_name_;
}

#endif