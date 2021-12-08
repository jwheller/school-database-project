// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

#ifndef ROLLBACKSTACK_H
#define ROLLBACKSTACK_H

#include "ListInterface.h"
#include "SchoolDatabase.h"


//Stack used to undo actions that modify the database in any way. Not implimented in final program
//but here's what I have of my attempt
class RollbackStack{
    
    public:
    RollbackStack();
    RollbackStack(int maxSize);
    ~RollbackStack();

    myList<SchoolDatabase*> *stack;
    SchoolDatabase* Pop();
    SchoolDatabase* Peek();
    void Push(SchoolDatabase *newDatabase);
    bool isEmpty();
    bool isFull();
    int getSize();

    private:
    SchoolDatabase *database; //might end up being **
    int mSize;
    SchoolDatabase *top;
};

RollbackStack::RollbackStack(){
    stack = new myList<SchoolDatabase*>();
    mSize = 3;
    
}

RollbackStack::RollbackStack(int maxSize){
    stack = new myList<SchoolDatabase*>();
    mSize = maxSize;

}

RollbackStack::~RollbackStack(){
    delete top, database, stack;
}

void RollbackStack::Push(SchoolDatabase *newDatabase){
    stack->Prepend(newDatabase);
    if(stack->GetLength() > mSize){
        stack->RemoveBack();
    }
}
SchoolDatabase* RollbackStack::Peek(){
    return stack->ReturnFront();
}

SchoolDatabase* RollbackStack::Pop(){
    SchoolDatabase* oldTop = Peek();
    stack->RemoveFront();
    return oldTop;
}
#endif