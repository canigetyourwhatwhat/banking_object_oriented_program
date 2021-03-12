#ifndef BANKER_CPP_
#define BANKER_CPP_

#include <iostream>
#include <fstream>
#include <sstream> 
#include <queue>

#include "Transaction.h"
#include "Banker.h"
#include "Account.h"
#include "BSTree.h"

Banker::Banker()
{

}

void Banker::ReadFile()
{        
    string line;
    ifstream my_file("BankTransIn.txt");
    //ifstream my_file("zzz.txt");
	if (!my_file) 
    {
		cout << "No such file";
	}
	while(!my_file.eof()) 
    {		
        getline(my_file, line);
        istringstream input(line);        
        char transactionInitial;
        input >> transactionInitial;

        if(transactionInitial == 'O')
        {
            string firstName, lastName;
            int accountNumber;
            input >> firstName >> lastName >> accountNumber;
            Transaction newTrans(transactionInitial, firstName, lastName, accountNumber);            
            records.push(newTrans);
        }
        else if(transactionInitial == 'D' || transactionInitial == 'W')
        {
            int fullNum, accountNum, amount, fundID;
            input >> fullNum;
            fundID = fullNum%10;
            accountNum = fullNum/10;
            input >> amount;
            Transaction newTrans(transactionInitial, accountNum, amount, fundID, true);
            records.push(newTrans);
        }
        else if(transactionInitial == 'T')
        {
            int from, fromFundID, amount, to, toFundID;
            input >> from >> amount >> to;
            fromFundID = from%10;
            from = from/10;
            toFundID = to%10;
            to = to/10;
            Transaction newTrans(transactionInitial, from, fromFundID, amount, to, toFundID, true);
            records.push(newTrans);

        }
        else if(transactionInitial == 'H')
        {
            int accountNum;
            input >> accountNum;
            Transaction newTrans(transactionInitial, accountNum);
            records.push(newTrans);
        }
        else
        {
            cout << "This initial is invalid" << endl;
        }                
	}	
}

void Banker::executeTransactions()
{
    while(!records.empty())
    {
        Transaction trans = records.front();

        if(trans.getInitial() == 'O')
        {
            int acctNum = trans.getAccountNum();
            Account *temp;
            if(tree.Retrieve(acctNum, temp))
            {
                cerr << "ERROR: Account " << acctNum << " is already open. Transaction refused." << endl;
            }            
            else
            {
                Account *acct = new Account(acctNum, trans.getFirstName(), trans.getLastName());
                tree.Insert(acct);
            }                        
        }
        else if(trans.getInitial() == 'D')
        {
            int acctNum = trans.getAccountNum();
            int amount = trans.getAmount();
            if(amount < 0)
            {
                cerr << "ERROR: You cannot deposit negative amount. Deposit refused." << endl;
            }
            else
            {
                int fundID = trans.getFundID();
                Account *temp;
                if(tree.Retrieve(acctNum, temp))
                {
                    temp->Deposit(fundID, amount);
                    temp->RecordTransaction(trans, fundID);
                }
                else
                {
                    cerr << "ERROR: Account " << acctNum << " not found. Deposit refused." << endl;
                }   
            }
        }
        else if(trans.getInitial() == 'W')
        {
            int acctNum = trans.getAccountNum();
            int amount = trans.getAmount();
            if(amount < 0)
            {
                cerr << "ERROR: You cannot deposit negative amount. Deposit refused." << endl;
            }
            else
            {
                int fundID = trans.getFundID();
                Account *temp;
                
                if(tree.Retrieve(acctNum, temp))
                {
                    temp->Withdraw(fundID, amount, trans);
                }
                else
                {
                    cerr << "ERROR: Account " << acctNum << fundID << " not found. Withdraw refused." << endl;
                }
            }
        }
        else if(trans.getInitial() == 'T')
        {
            int amount = trans.getAmount();
            if(amount < 0)
            {
                cerr << "ERROR: You cannot deposit negative amount. Deposit refused." << endl;
            }
            else
            {
                int from = trans.getAccountNum();
                int fromFundID = trans.getFundID();
                int to = trans.getToAccount();
                int toFundID = trans.getToFundID();
                Account *toAcct, *fromAcct;            
                
                if(!tree.Retrieve(from, fromAcct))
                {
                    cerr << "ERROR: Account " << from << fromFundID << " not found. Transfer refused." << endl;
                }
                else if(!tree.Retrieve(to, toAcct))
                {
                    cerr << "ERROR: Account " << to << toFundID << " not found. Transfer refused." << endl;
                }
                else if(tree.Retrieve(from, fromAcct) && tree.Retrieve(to, toAcct))
                {
                    if(fromAcct->Withdraw(fromFundID, amount, trans))
                    {
                        toAcct->Deposit(toFundID, amount);
                        toAcct->RecordTransaction(trans, toFundID);
                    }
                    else
                    {
                        cerr << "ERROR: Not Enought Funds to Transfer " << amount << " " << "from " << fromAcct->getAccountID() << fromFundID << " to " << toAcct->getAccountID() << toFundID << endl;
                        trans.setResult("false");
                    }
                    
                }
            }
            
        }
        else if(trans.getInitial() == 'H')
        {
            if(trans.getAccountNum() >= 10000 && trans.getAccountNum() < 100000 )
            {
                int acctNum = trans.getAccountNum() / 10;
                int fundID = trans.getAccountNum() % 10;
                Account *temp;
                if(tree.Retrieve(acctNum, temp))
                {
                    temp->DisplayFundHistory(fundID);
                }
            }
            else if(trans.getAccountNum() >= 1000 && trans.getAccountNum() < 10000 )
            {
                Account *temp;
                if(tree.Retrieve(trans.getAccountNum(), temp))
                {
                    temp->DisplayAllFundsHistory();                    
                }
            }
        }
        else
        {
            cout << "This object has an issue" << endl;
        }
        records.pop();
    }
}

void Banker::FinalBalance()
{
    if(tree.isEmpty())
    {
        cout << "No account is added" << endl;        
    }
    else
    {
        tree.Display(tree.getRoot());   
    }
}

#endif