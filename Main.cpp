#ifndef MAIN_CPP_
#define MAIN_CPP_


#include <iostream>
#include <fstream>

#include "Banker.h"
using namespace std;

int main()
{   
    Banker Jolly;
    Jolly.ReadFile(); 

    Jolly.executeTransactions();
    
    cout << "Processing Done. Final Balances" << endl;
    Jolly.FinalBalance();
    
    return 0;
}

#endif