// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

#include "bst.h"
#include "Person.h"

//Abstracts bst.h and presents only the functions that will be
//needed for a person-Table (holds either students or faculty).
template<class T>
class GenDatabase{
    public:
    GenDatabase();
    ~GenDatabase();
    BST<T> *bst = new BST<T>;
    void add(T person);
    bool remove(int ID);
    bool contains(int ID);
    bool isEmpty();
    void printAll();
    void printInfo(int ID);
    void printInOrder();

    void printAdvisingInfo(int ID);
    T* returnPerson(int ID);
    T getSucessor(T person);
    T getRoot();
};

template<class T>
GenDatabase<T>::GenDatabase(){
}

template<class T>
GenDatabase<T>::~GenDatabase(){
    delete bst;
}

template<class T>
void GenDatabase<T>::add(T person){
    bst->insert(person);
}

template<class T>
bool GenDatabase<T>::remove(int ID){
    return bst->deleteFromID(ID);
}

template<class T>
bool GenDatabase<T>::contains(int ID){
    return bst->containsID(ID);
}

template<class T>
bool GenDatabase<T>::isEmpty(){
    return bst->isEmpty();
}

template<class T>
void GenDatabase<T>::printAll(){
    bst->printNodes();
}

template<class T>
void GenDatabase<T>::printInfo(int ID){
    bst->printFromID(ID);
}

template<class T>
T* GenDatabase<T>::returnPerson(int ID){
    return bst->returnKey(ID);    
}

template<class T>
T GenDatabase<T>::getSucessor(T person){
    T successor = bst->returnSucessor(person);
    if (successor == person){ //If person has no successor (aka are their own successor)
        successor = bst->getRoot(); //Then set the successor to be the person who is the root
    }
    return successor;
}

template<class T>
T GenDatabase<T>::getRoot(){
    return bst->getRoot();
}

template<class T>
void GenDatabase<T>::printInOrder(){
    bst->printInOrder();
}