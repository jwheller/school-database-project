// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

#include "Person.h"

//Class that defines the generic traits that both students and faculty have in common
Person::Person(){
    idNum;
    name;
    level;
}

Person::~Person(){

}

//"Set" functions:
void Person::setID(int id){
    idNum = id;
}

void Person::setName(string n){
    name = n;
}

void Person::setLevel(string lev){
    level = lev;
}

//"Get" functions:
int Person::getID(){
    return idNum;
}

string Person::getName(){
    return name;
}

string Person::getLevel(){
    return level;
}

bool Person::lessThan(Person* p){
    if(idNum < p->getID()){
        return true;
    }
    else{
        return false;
    }
}

bool Person::greaterThan(Person* p){
    if(idNum > p->getID()){
        return true;
    }
    else{
        return false;
    }
}

bool Person::equalTo(Person* p){
    if(idNum == p->getID()){
        return true;
    }
    else{
        return false;
    }
}

void Person::printInfo(){
    cout << "ID Number: " << idNum << endl;
    cout << "Name: " << name << endl;
    cout << "Level: " << level << endl;
}