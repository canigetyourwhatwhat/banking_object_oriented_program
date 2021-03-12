#ifndef BSTREE_CPP_
#define BSTREE_CPP_
#include "BSTree.h"
#include "Account.h"

BSTree::BSTree()
{

}
BSTree::~BSTree()
{
    Empty();
}

bool BSTree::Insert(Account* account)
{
    if(isEmpty())
    {
        root = new Node;
        root->pAcct = account;
        root->left = nullptr;
        root->right = nullptr;
        return true;
    }

    Node *current = root;
    bool flag = true;
    while(flag)
    {
        if(account->getAccountID() > current->pAcct->getAccountID())
        {
            if(current->right == nullptr)
            {
                Node* newNode = new Node;
                newNode->pAcct = account;
                newNode->left = nullptr;
                newNode->right = nullptr;
                current->right = newNode;
                flag = false;
                return true;
            }
            else
            {
                current = current->right;
            }
        }
        else
        {
            if(current->left == nullptr)
            {
                Node* newNode = new Node;
                newNode->pAcct = account;
                newNode->left = nullptr;
                newNode->right = nullptr;
                current->left = newNode;
                flag = false;
                return true;
            }
            else
            {
                current = current->left;
            }
        }
        
    }
    return false;
    
}

bool BSTree::Retrieve(const int &accountNum, Account *& account) const
{
    if(isEmpty())
    {
        return false;
    }
    Node *current = root;
    while(current != nullptr)
    {
        if(current->pAcct->getAccountID() == accountNum)
        {
            //cout << current->pAcct->getAccountID() << endl;
            account = current->pAcct;
            return true;
        }
        else if(current->pAcct->getAccountID() < accountNum)
        {
            //cout << current->pAcct->getAccountID() << endl;
            current = current->right;
        }
        else if(current->pAcct->getAccountID() > accountNum)
        {
            //cout << current->pAcct->getAccountID() << endl;
            current = current->left;
        }
    }
    return false;
}

void BSTree::Display(Node* current) const
{
    if (current->right != NULL && current->left != NULL)
	{
		Display(current->right);
		cout << *(current->pAcct) << endl;
		Display(current->left);
	}
	else if (current->left != NULL)
	{
		cout << *(current->pAcct) << endl;
		Display(current->left);
	}
	else if (current->right != NULL)
	{
		cout << *(current->pAcct) << endl;
		Display(current->right);
	}
	else
	{
		cout << *(current->pAcct) << endl;
	}
}

void BSTree::Empty()
{
    delete root;
    root = nullptr;
}

bool BSTree::isEmpty() const
{
    if(root->pAcct == nullptr)
    {
        return true;
    }
    return false;
}

Node* BSTree::getRoot() const
{
    return root;
}


#endif