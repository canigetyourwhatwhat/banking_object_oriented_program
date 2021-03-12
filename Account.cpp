#ifndef ACCOUNT_CPP_
#define ACCOUNT_CPP_
#include <string>
#include "Fund.h"
#include "Account.h"
using namespace std;


Account::Account()
{

}

ostream& operator<<(ostream& stream, const Account& account)
{
    stream << account.firstName_ << " " << account.lastName_ << " Account ID: " << account.account_id_ << endl;
    for(int i=0; i<10; i++)
    {
        stream << "    " << account.fund[i].getFundName() << ": $" << account.fund[i].getBalance();
        cout << endl;
    }
    return stream;
}

// Open method is this constructor
Account::Account(int id, string firstName, string lastName)
{
    firstName_ = firstName;
    lastName_ = lastName;
    account_id_ = id;
    int fundNum;
    string fundName [10] = {"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", "500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "Value Fund", "Value Stock Index"};
    for(int i=0; i<10; i++)
    {
        fundNum = account_id_ * 10 + i; 
        fund[i] = Fund(fundName[i], fundNum);
    }   
}



bool Account::Deposit(int fundID, int amount)
{
    return fund[fundID].AddBalance(amount);
}

bool Account::Withdraw(int fundID, int amount, Transaction trans)
{
    if(fund[fundID].getBalance() > amount)
    {
        fund[fundID].DeductBalance(amount);
        fund[fundID].RecordsOnFund(trans);
        return true;
    }
    else if(fundID < 4)
    {
        if(fundID == 0 || fundID == 1)
        {
            if(fund[0].getBalance() + fund[1].getBalance() >= amount)
            {
                WithdrawFromLinkedFunds(fundID, amount);
                return true;
            }
            else
            {
                ErrorMessege(amount, fundID, trans);
                return false;
            }
        }
        else
        {
            if(fund[2].getBalance() + fund[3].getBalance() >= amount)
            {
                WithdrawFromLinkedFunds(fundID, amount);
                return true;
            }
            else
            {
                ErrorMessege(amount, fundID, trans);
                return false;
            }
        }
    }
    else
    {
        ErrorMessege(amount, fundID, trans);
        return false;
    }
}

bool Account::WithdrawFromLinkedFunds(int fundID, int amount)
{
    int num;
    if(fundID == 0 || fundID == 2)
    {
        num = 1;
    }
    else
    {
        num = -1;
    }
    int originalAmount = fund[fundID].getBalance();
    amount-= fund[fundID].getBalance();
    fund[fundID].DeductBalance(fund[fundID].getBalance());
    fund[fundID+num].DeductBalance(amount);
    
    
    //int leftOver = amount - fund[fundID].getBalance();
    //fund[fundID].DeductBalance(fund[fundID].getBalance());
    //fund[fundID+num].DeductBalance(leftOver);

    Transaction MainTrans('W', getAccountID(), originalAmount, fundID, true);
    fund[fundID].RecordsOnFund(MainTrans);
    //cout << leftOver << endl;
    Transaction LinkedTrans('W', getAccountID(), amount, fundID + num, true);
    fund[fundID + num].RecordsOnFund(LinkedTrans);
    return true;
}

void Account::RecordTransaction(Transaction trans, int fundID)
{
    fund[fundID].RecordsOnFund(trans);
}

void Account::ErrorMessege(int amount, int fundID, Transaction trans)
{
    trans.setResult(false);
    RecordTransaction(trans, fundID);
    if(trans.getInitial() != 'T')
    {
        cout << "ERROR: Not enough funds to withdraw " << amount << " from " << firstName_ << " " << lastName_ << " " << fund[fundID].getFundName() << endl;        
    }
}




string Account::getFirstName() const
{
    return firstName_;
}
string Account::getLastName() const
{
    return lastName_;
}
int Account::getAccountID() const
{
    return account_id_;
}



// AllFund's history
void Account::DisplayAllFundsHistory()
{
    cout << "Transaction History for " << firstName_ << " " << lastName_ << " " << "By Fund."<< endl;
	for (int i = 0; i < 10; i++)
	{
        
        cout << fund[i].getFundName() << ": $" << fund[i].getBalance() << endl;
		fund[i].ShowHistory();
	}
}

// Specific Fund's history
void Account::DisplayFundHistory(int fundID)
{
    cout << "Transaction History for " << firstName_ << " " << lastName_ << " " << fund[fundID].getFundName() << ": $" << fund[fundID].getBalance() <<  endl;
	fund[fundID].ShowHistory();
}


#endif