// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

#include "ListNode.h"

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

using namespace std;

template<class T>
class DoubleLinkedList{
    
    private:
        ListNode<T> *front;
        ListNode<T> *back;
        unsigned int size; //the size of a list would never be negative, so this int can be unsigned

    public:
        DoubleLinkedList();
        ~DoubleLinkedList();

        void insertFront(T d);
        void insertBack(T d); 
        void removeFront();
        T returnFront(); 
        void removeBack(); 
        T returnBack();
        void remove(T d);
        bool find(T d);
        void insertAfter(T existingData, T newData);
        void print();
        void printReverse();
        T returnEachNode();
        void sort();
        bool isEmpty();
        unsigned int getSize();
};



template<class T>
DoubleLinkedList<T>::DoubleLinkedList(){
    size = 0;
    front = NULL;
    back = NULL;
}

template<class T>
DoubleLinkedList<T>::~DoubleLinkedList(){
    delete front;
    delete back;
    
}

template<class T>
void DoubleLinkedList<T>::insertFront(T d){
    ListNode<T> *node = new ListNode<T>(d);

    if(front == NULL){
        front = node;
        back = node;
    }
    else{
        node->next = front;
        front->prev = node;
        front = node;
    }
    ++size;
}

template<class T>
void DoubleLinkedList<T>::insertBack(T d){
    ListNode<T> *node = new ListNode<T>(d);
 
    if(front == NULL){
        front = node;
        back = node;
           
    }
    else{
        node->prev = back;
        back->next = node;
        back = node;
    }
    ++size;
}

template<class T>
void DoubleLinkedList<T>::removeFront(){
    ListNode<T>* oldfront = front;

    if (front == NULL){
        cout << "List is empty" << endl;
    }

    else if (front == back){
        front = NULL;
        back = NULL;
        --size;
    }

    else{
        front = oldfront->next;
        --size;
    }
    delete oldfront;
}

template<class T>
T DoubleLinkedList<T>::returnFront(){
    return front->data;
}

template<class T>
void DoubleLinkedList<T>::removeBack(){
    ListNode<T> *oldback = back; //Create a pointer to the current node in the back
    back = back->prev; //Set the back pointer to the node before back
    delete oldback; //delete the pointer
    --size; //decrement the size
}

template<class T>
T DoubleLinkedList<T>::returnBack(){
    return front->data;
}

template<class T>
bool DoubleLinkedList<T>::find(T d){
    if(front == NULL){
        return false;
    }
    else{
        ListNode<T> *searchNode = front;
        while(searchNode != NULL){
            if(searchNode->data == d){
                return true;
                break;
            }
            else{
                searchNode = searchNode->next;
            }
        }
        if (searchNode == NULL){
            return false;
        }
        delete searchNode;
    }
}

template<class T>
void DoubleLinkedList<T>::remove(T d){
    
    if(front == NULL){
        cout << "List is already empty" << endl;
    }
    else{
        ListNode<T> *searchNode = front;
        while(searchNode != NULL){
            if(searchNode->data == d){
                ListNode<T> *sucNode = searchNode->next;
                ListNode<T> *predNode = searchNode->prev;
                
                if (sucNode != NULL){
                    sucNode->prev = predNode;
                }

                if (predNode != NULL){
                    predNode->next = sucNode;
                }

                if (searchNode == front){
                    front = sucNode;
                }

                if (searchNode == back){
                    back = predNode;
                }

                break;
            }
            else{
                searchNode = searchNode->next;
            }
        }
        if (searchNode == NULL){
            cout << "This node is not in the list!" << endl;
        }

        delete searchNode;
    }
}

template<class T>
void DoubleLinkedList<T>::insertAfter(T existingData, T newData){
    if (front != NULL){
        ListNode<T> *searchNode = front;
        while(searchNode != NULL){
            if(searchNode->data == existingData){
                ListNode<T> *newNode = new ListNode<T>(newData);
                if (searchNode == back){
                    newNode->prev = back;
                    back->next = newNode;
                    back = newNode;
                }
                else{
                    ListNode<T> *sucNode = searchNode->next;
                    newNode->next = sucNode;
                    newNode->prev = searchNode;
                    searchNode->next = newNode;
                    sucNode->prev = newNode;
                }
                break;
            }
            else{
                searchNode = searchNode->next;
            }
        }
        if (searchNode == NULL){
            cout << "Search Node not found" << endl;
        }
    }  
}

template<class T>
void DoubleLinkedList<T>::print(){
    ListNode<T>* currNode = front;
    if(front == NULL){
        cout << "List is empty" << endl;
    }
    else{
        while(currNode != NULL){
            cout << currNode->data << ", "; //Seperate objects by comma when printing their info
            currNode = currNode->next;
        }
        cout << endl;
    }
    delete currNode;
}

template<class T>
void DoubleLinkedList<T>::printReverse(){
    ListNode<T>* currNode = back;
    if(front == NULL){
        cout << "List is empty" << endl;
    }
    else{
        while(currNode != NULL){
            cout << currNode->data << ", ";
            currNode = currNode->prev;
        }
        cout << endl;
    }
    delete currNode;
}

template<class T>
T DoubleLinkedList<T>::returnEachNode(){
    ListNode<T>* currNode = front;
    while(currNode != NULL){
        return currNode->data;
        currNode = currNode->next;
    }
    delete currNode;
}

template<class T>
bool DoubleLinkedList<T>::isEmpty(){
    if (front == NULL){ //If the front is NULL, by definition the tail must be too
        return true;
    }
    else{
        return false;
    }
}

template<class T>
unsigned int DoubleLinkedList<T>::getSize(){
    return size;
}

template<class T>
void DoubleLinkedList<T>::sort(){ //Method from Zybooks (fixed this time hehe)
    if (front != NULL && front->next != NULL){

        ListNode<T> *currNode = front -> next;
        ListNode<T> *nextNode;
        ListNode<T> *searchNode;
        T reinsertVal;
        while (currNode != NULL){
            nextNode = currNode -> next;
            searchNode = currNode -> prev;
            while (searchNode != NULL && searchNode->data > currNode -> data){
                searchNode = searchNode -> prev;
            }
            ///////////
            reinsertVal = currNode->data;
            remove(currNode->data);

            if (searchNode == NULL){
                insertFront(reinsertVal);
            }
            else{
                insertAfter(searchNode->data, reinsertVal);
            }
            currNode = nextNode;
        }
        delete currNode, nextNode, searchNode;
    }
}

#endif