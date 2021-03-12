#ifndef BSTREE_H_
#define BSTREE_H_
#include "Account.h"

struct Node 
{
        Account* pAcct;
        Node* right;
        Node* left;
};

class BSTree
{
    public:
        BSTree();
        ~BSTree();
 
        bool Insert(Account* account);
        bool Retrieve(const int &accountNum, Account *& account) const;
        void Display(Node* current) const; 
        void Empty();
        bool isEmpty() const;

        Node* getRoot() const;        

    private:        
        Node* root;
};

#endif