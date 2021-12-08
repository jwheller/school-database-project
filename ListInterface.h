// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

//Abstract Interface for the doubleLinkedList class
#ifndef LISTINTERFACE_H
#define LISTINTERFACE_H

#include "DoubleLinkedList.h"


template <class T>
class ListInterface{

    public:
    virtual void Append(T data) = 0;
    virtual void Prepend(T data) = 0;
    virtual void InsertAfter(T existingData,T insertData) = 0;
    virtual void Remove(T data) = 0;
    virtual bool Search(T data) = 0; 
    virtual void Print() = 0;
    virtual void PrintReverse() = 0;
    virtual void Sort() = 0; //!
    virtual bool IsEmpty() = 0;
    virtual int GetLength() = 0;
};


//implementation of ListInterface 
template <class T>
class myList : public ListInterface<T>{

    public:
    myList();
    ~myList();
    DoubleLinkedList<T> *doubleList;
    void Append(T data);
    void Prepend(T data);
    void InsertAfter(T existingData,T insertData);
    void Remove(T data);
    void RemoveFront();
    void RemoveBack();
    bool Search(T data);
    void Print();
    T ReturnAll();
    T ReturnFront();
    T ReturnBack();
    T PopFront();
    void PrintReverse();
    void Sort();
    bool IsEmpty();
    int GetLength();
};

template<class T>
myList<T>::myList(){
    doubleList = new DoubleLinkedList<T>();
}

template<class T>
myList<T>::~myList(){
    delete doubleList;
}

template<class T>
void myList<T>::Append(T data){
    doubleList->insertBack(data);
}

template<class T>
void myList<T>::Prepend(T data){
    doubleList->insertFront(data);
}

template<class T>
void myList<T>::RemoveFront(){
    doubleList->removeFront();
}

template<class T>
void myList<T>::RemoveBack(){
    doubleList->removeBack();
}

template<class T>
T myList<T>::ReturnFront(){
    return doubleList->returnFront();
}

template<class T>
T myList<T>::ReturnBack(){
    return doubleList->returnBack();
}

template<class T>
T myList<T>::PopFront(){
    T frontNode = ReturnFront();
    RemoveFront();
    return frontNode;
}

template<class T>
bool myList<T>::IsEmpty(){
    return doubleList->isEmpty();
}

template<class T>
int myList<T>::GetLength(){
    return doubleList->getSize();
}

template<class T>
void myList<T>::Print(){
    doubleList->print();
}

template<class T>
T myList<T>::ReturnAll(){
    doubleList->returnEachNode();
}

template<class T>
void myList<T>::InsertAfter(T existingData, T insertData){
    doubleList->insertAfter(existingData, insertData);
}

template<class T>
void myList<T>::Remove(T data){
    doubleList->remove(data);
}

template<class T>
bool myList<T>::Search(T data){
    return doubleList->find(data);
}

template<class T>
void myList<T>::PrintReverse(){
    doubleList->printReverse();
}

template<class T>
void myList<T>::Sort(){
    doubleList->sort();
}

#endif