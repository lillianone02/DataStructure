#include <iostream>
#include <string>
using namespace std;

struct Node
{
    char data;
    Node *next;
    Node *prev;
    Node(char da, Node *pre=nullptr, Node *nex=nullptr){
        data=da;
        prev=pre;
        next=nex;
    }
};

Node *head = nullptr;
Node *cursor = nullptr;

void TypeFun(string str)
{
    for (char c : str)
    {
        Node *newNode = new Node(c);
        if (head == nullptr) // no node in link list
        {
            head = newNode;
            cursor = newNode; // newNode->next
        }
        else // at least one node in link list
        {
            if (cursor)
            {
                newNode->next = cursor->next;
                newNode->prev = cursor;
                if (cursor->next != nullptr)
                {
                    cursor->next->prev = newNode;
                }
                cursor->next = newNode;
                cursor = newNode;
            }
            else // cursor is at the most front cursor==nullptr
            {
                head->prev = newNode;
                newNode->next = head;
                cursor = newNode;
                head = newNode;
            }
        }
    }
}

void MoveFun(long long n)
{
    if (n > 0)
    {
        long long i = 0;
        if (cursor == nullptr)
        { // cursor is at the most front
            cursor = head;
            ++i;
        }
        if (cursor)
        {
            for (; i < n && cursor->next != nullptr; ++i)
            {
                
                cursor = cursor->next;
            }
        }
    }
    else
    {
        for (long long i = 0; i > n && (cursor != nullptr); --i)
        {
            cursor = cursor->prev;
        }
    }
}

void BackspaceFun()
{
    if ((cursor != nullptr) && (cursor == head)) // cursor and head point to same node(first node)
    {
        Node *temp = cursor;
        if (head->next == nullptr) // only one node in the list
        {
            cursor = nullptr;
            head = nullptr;
        }
        else // after deletion cursor is at the most front
        {
            head = head->next;
            head ->prev = nullptr;
            cursor = nullptr;
        }
        delete temp;
    }
    else if (cursor != nullptr && cursor != head) // cursor is at the middle of somewhere of the list
    {
        Node *temp = cursor;
        cursor = cursor->prev;
        cursor->next = temp->next;
        if (temp->next != nullptr)
        {
            temp->next->prev = cursor;
        }
        delete temp;
    }
}

void print()
{
    Node *current = head;
    while (current != nullptr)
    {
        cout << current->data;
        current = current->next;
    }
    cout << endl;
}

int main()
{
    string operation;
    long long dataN = 0;
    string dataS;
    while (cin >> operation)
    {
       
        if (operation == "Type")
        {
            cin >> dataS;
            TypeFun(dataS);
        }
        else if (operation == "Move")
        {
            cin >> dataN;
            MoveFun(dataN);
        }
        else if (operation == "Backspace")
        {
            BackspaceFun();
        }
        else if (operation == "Print")
        {
            print();
        }
    }
    return 0;
}