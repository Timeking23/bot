/*
Daniel Getahun
*/

#ifndef LIST_H
#define LIST_H
using namespace std;
#include <iostream>

template <typename T>
class List
{
    private:
    struct listNode
    {
        T value;
        listNode *next;
        listNode *previous;

    };
    listNode *head;
    listNode *tail;

    void print(listNode*);
    listNode* mergesort(listNode*, listNode*);
    listNode* merge(listNode*, listNode*);
    listNode* split(listNode*, listNode*);

    public:

    List();
    ~List();
    void print();
    void append(T);
    void mergesort();
};


template <typename T>
// List Constructor 

List<T>::List()
{
    head = NULL;
    tail = NULL;

}

// List Destructor

template <typename T>
List<T>::~List()
{
    listNode *current, *next;
    current = head;
    while(current != NULL)
    {
        next = current -> next;
        delete current;
        current = next;
    }

}

// Public Print
template <typename T>
void List<T>::print()
{
    print(head);
}

// Private Print
template <typename T>
void List<T>::print(listNode* nodePtr)
{
    listNode* current = nodePtr;
    while(current != NULL)
    {
        cout << *(current->value) << endl;
        current = current->next;
    }
}

// Append new value
template <typename T>
void List<T>::append(T value)
{
    listNode* newNode = new listNode;
    newNode -> value = value;
    newNode -> next = NULL;
    newNode -> previous = tail;
    if(!head)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail -> next = newNode;
        tail = newNode;
    }
}

template <typename T>
typename List<T>::listNode* List<T>::merge(listNode* firstPartOne, listNode* firstPartTwo)
{
    if(!firstPartOne)

        return firstPartTwo;
        
    if(!firstPartTwo)

        return firstPartOne;

    if(*(firstPartOne -> value) > *(firstPartTwo -> value))
    {
        firstPartOne -> next = merge(firstPartOne -> next, firstPartTwo);
        firstPartOne -> next -> previous = firstPartOne;
        firstPartOne -> previous = NULL;
        return firstPartOne;
    }
    else
    {
        firstPartTwo -> next = merge(firstPartOne, firstPartTwo -> next);
        firstPartTwo -> next -> previous = firstPartTwo;
        firstPartTwo -> previous = NULL;
        return firstPartTwo;
    }
}


template <typename T>
void List<T>::mergesort()
{
    // Call private mergesort head/tail
    head = mergesort(head, tail);
    listNode* mover = head;
    while(mover -> next)
    {
        mover = mover -> next;
    }
    tail = mover;

    // Set new to head and tail
}

template <typename T>
typename List<T>::listNode* List<T>::mergesort(listNode* first, listNode* last)
{
    if(!first || !first -> next)
    {
        return first;
    }

    

    listNode* left = first;
    listNode* right = split(first, last);

    left = mergesort(left, right->previous);
    right = mergesort(right, last);

    return merge(left, right);
}

template <typename T>
typename List<T>::listNode* List<T>::split(listNode* first, listNode* last)
{
    listNode* middle;
    while(first != last && first -> next != last)
    {
        first = first -> next;
        last = last -> previous;
    }
    
    middle = first -> next;
    first -> next = NULL;
    return middle;

}



#endif