// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

//Template class for both the BST and their nodes
#ifndef BST_H
#define BST_H

#include <iostream>

using namespace std;

template<class T>
class TreeNode{
    public:
    TreeNode();
    TreeNode(T k);
    virtual ~TreeNode();

    int idKey = 0;
    T key; //Data
    TreeNode<T> *left;
    TreeNode<T> *right;
};

template<class T>
TreeNode<T>::TreeNode(){
    left = NULL;
    right = NULL;
    idKey = 0;
    key = NULL;
}

template<class T>
TreeNode<T>::TreeNode(T k){
    left = NULL;
    right = NULL;
    idKey = k->getID();
    key = k;
}

template<class T>
TreeNode<T>::~TreeNode(){
    left =NULL;
    right=NULL;
}

template<class T>
class BST{
    public:
    BST();
    virtual ~BST();
    void insert(T value);
    bool deleteNode(T k);
    bool contains(T value); //Search
    bool isEmpty();

    bool containsID(int ID);
    bool deleteFromID(int ID);

    T* getMin();
    T* getMax();
    
    void printNodes();
    void recPrint(TreeNode<T> *node);
    void printFromID(int ID);
    void recInOrder(TreeNode<T> *currNode);
    void printInOrder();
    T* returnKey(int ID);
    T returnSucessor(T value);
    T getRoot();
    

    protected:
    TreeNode<T> *getSuccessor(TreeNode<T> *d);
    TreeNode<T> *root;
};

template<class T>
BST<T>::BST(){
    root = NULL;
}

template<class T>
BST<T>::~BST(){
    delete root;
}

template<class T>
void BST<T>::recPrint(TreeNode<T> *node){
    if(node != NULL){
        (node->key)->printInfo();
        cout << endl; //Add space before next Students
        recPrint(node->left);
        recPrint(node->right);
    } 
}

template<class T>
void BST<T>::printNodes(){
    if(root == NULL){
        cout << "Table is empty" << endl;
    }
    else{
        recPrint(root); //Prints the entire tree
    }  
}

template<class T>
bool BST<T>::isEmpty(){
    return (root == NULL);
}

template<class T>
T* BST<T>::getMin(){
    TreeNode<T> *current = root; //start at root

    if(root == NULL){
        //tree is empty
        return NULL;
    }

    while(current->left != NULL){
        current = current->left;
    }

    return &(current->key);
}

template<class T>
T* BST<T>::getMax(){
    TreeNode<T> *current = root; //start at root

    if(root == NULL){
        return NULL;
    }

    while(current->right != NULL){
        current = current->right;
    }

    return &(current->key);
}

template<class T>
void BST<T>::insert(T value){
    TreeNode<T> *node = new TreeNode<T>(value);

    if(isEmpty()){
        //tree was empty
        root = node;
    }
    else{
        //tree was not tempty
        TreeNode<T> *current = root;
        TreeNode<T> *parent = NULL;

        while(current != NULL){
            parent = current;

            if(value->lessThan(current->key)){
                //go left
                current = current->left;
                
                if(current == NULL){
                    //we found the insertion point
                    parent->left = node;
                    break;
                }
            }

            else{ //else we go right
                current = current->right;
                if(current == NULL){
                    parent->right = node;
                    break;
                }
            }
        }
    }
}

template<class T>
bool BST<T>::contains(T value){
    if(isEmpty()){
        return false;
    }
    else{
        //tree is not empty, lets look for our value
        TreeNode<T> *current = root;
        while(!(current->key).equalTo(value)){
            if(value->lessThan(current->key)){
                current = current->left;
            }
            else{
                current = current->right;
            }

            if(current == NULL){
                return false;
            }
        }

        if((current->key).equalTo(value)){
            return true;
        }
    }
}

template<class T>
bool BST<T>::deleteNode(T k){
    if(isEmpty()){
        return false;
    }
    if(!contains(k)){
        return false;
    }

    TreeNode<T> *current = root;
    TreeNode<T> *parent = root;
    bool isLeft = true;

    while(!(current->key).equalTo(k)){
        parent = current;

        if(k.lessThan(current->key)){
            isLeft = true;
            current = current->left;
        }
        else{
            isLeft = false;
            current = current->right;
        }

        if(current == NULL){
            return false; //value doesnt exist in tree
        }
    }

    //if we make it here, then we found the node to be deleted
    /*no children, leaf node )*/
    if (current->left == NULL && current->right == NULL){
        if(current == root){
            root = NULL;
        }
        else if (isLeft){
            parent->left = NULL;
        }
        else{
            parent->right = NULL;
        }

    }

    else if (current->right == NULL){
        //node to be deleted has a left child (no right)
        if(current == root){
            root = current->left;
        }
        else if(isLeft){
            parent->right = current->left;
        }
        else{
            parent->right = current->left;
        }
    }
    else if (current->left == NULL){
        //node to be deleted has a right child (no left)
        if(current == root){
            root = current->right;
        }
        else if(isLeft){
            parent->right = current->right;
        }
        else{
            parent->right = current->right;
        }
    }
    else{
        //Node to be delted has two children
        TreeNode<T> *successor = getSuccessor(current);

        if (current == root){
            root = successor;
        }
        else if (isLeft){
            parent->left = successor;
        }
        else{
            parent->right = successor;
        }

        successor->left = current->left;
        current->left = NULL;
        current->right = NULL;
    }

    return true;
}


template<class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d){ //d is node to be deleted
    TreeNode<T> *sp = d; //succesor parent
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right; // we go right

    while(current != NULL){
        sp = successor;
        successor = current;
        current = current->left;
    }
    //if successor is descendant of right child
    if (d->right != NULL){
        if (successor->idKey != (d->right)->idKey){
            sp->left = successor->right;
            successor ->right = d->right;
        }
    }
    return successor;
}

template<class T>
bool BST<T>::containsID(int ID){
    if(isEmpty()){
        return false;
    }
    else{
        //tree is not empty, lets look for our value
        TreeNode<T> *current = root;
        while(current->idKey != ID){
            if(ID < current->idKey){
                current = current->left;
            }
            else{
                current = current->right;
            }

            if(current == NULL){
                return false;
            }
        }

        if(current->idKey == ID){
            return true;
        }
    }
}

template<class T>
bool BST<T>::deleteFromID(int ID){
    if(isEmpty()){
        return false;
    }
    if(!containsID(ID)){
        cout << "value doesn't exist, can't delete()" <<endl;
        return false;
    }

    TreeNode<T> *current = root;
    TreeNode<T> *parent = root;
    bool isLeft = true;

    //let's find the value so that we can set the current and parent

    while(current->idKey != ID){
        parent = current;

        if(ID < current->idKey){
            isLeft = true;
            current = current->left;
        }
        else{
            isLeft = false;
            current = current->right;
        }

        if(current == NULL){
            return false; //value doesnt exist in tree
        }
    }

    if (current->left == NULL && current->right == NULL){
        if(current == root){
            root = NULL;
        }
        else if (isLeft){
            parent->left = NULL;
        }
        else{
            parent->right = NULL;
        }
    }

    else if (current->right == NULL){
        //node to be deleted has a left child (no right)
        if(current == root){
            root = current->left;
        }
        else if(isLeft){
            parent->right = current->left;
        }
        else{
            parent->right = current->left;
        }
    }
    else if (current->left == NULL){
        //node to be deleted has a right child (no left)
        if(current == root){
            root = current->right;
        }
        else if(isLeft){
            parent->right = current->right;
        }
        else{
            parent->right = current->right;
        }
    }
    else{
        //Node to be delted has two children
        TreeNode<T> *successor = getSuccessor(current);

        if (current == root){
            root = successor;
        }
        else if (isLeft){
            parent->left = successor;
        }
        else{
            parent->right = successor;
        }

        successor->left = current->left;
        current->left = NULL;
        current->right = NULL;
    }

    return true;
}

template<class T>
void BST<T>::printFromID(int ID){
    if(isEmpty()){
        cout << "This Database is empty" << endl;
    }
    else{
        //tree is not empty, lets look for our value
        TreeNode<T> *current = root;
        while(current->idKey != ID){
            if(ID < current->idKey){
                current = current->left;
            }
            else{
                current = current->right;
            }
            if(current == NULL){
                cout << "No one with this ID exists!" << endl;
                break;
            }
        }

        if(current->idKey == ID){
            (current->key)->printInfo();
        }
    }
}

template<class T>
void BST<T>::recInOrder(TreeNode<T> *currNode){
    if (currNode == NULL){
        return;
    }

    recInOrder(currNode->left);
    (currNode->key).printInfo();
    cout << endl;
    recInOrder(currNode->right);
}


template<class T>
void BST<T>::printInOrder(){
    recInOrder(root);
}

template<class T>
T* BST<T>::returnKey(int ID){
    if(!isEmpty()){
        //tree is not empty, lets look for our value
        TreeNode<T> *current = root;
        while(current->idKey != ID){
            if(ID < current->idKey){
                current = current->left;
            }
            else{
                current = current->right;
            }

            if(current == NULL){
                cout << "ID not found" << endl;
                break;
            }
        }

        if(current->idKey == ID){
            T *keyInfo = &current->key;
            return keyInfo;
        }
    }
}

template<class T>
T BST<T>::returnSucessor(T value){

    if(!isEmpty()){
        TreeNode<T> *current = root;
        while(!(current->key)->equalTo(value)){
            if(value->lessThan(current->key)){
                current = current->left;
            }
            else{
                current = current->right;
            }

            if(current == NULL){
                break;
            }
        }

        if((current->key)->equalTo(value)){
            return getSuccessor(current)->key;
        }
    }
}

template<class T>
T BST<T>::getRoot(){
    return root->key;
}
    #endif
