// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

//Template class of a list node for the double linked list
#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream>

using namespace std;

template<class T>
class ListNode{

    public:
        ListNode();
        ListNode(T d);
        ~ListNode();
        T data;
        ListNode *next;
        ListNode *prev;
};


template<class T>
ListNode<T>::ListNode(){
    data;
    next = NULL;
    prev = NULL;
}

template<class T>
ListNode<T>::ListNode(T d){
    data = d;
    next = NULL;
    prev = NULL;
}

template<class T>
ListNode<T>::~ListNode(){
    next = NULL;
    prev = NULL;
}
#endif