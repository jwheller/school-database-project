// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

//Parent class for Student and Faculty
#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

using namespace std;

class Person{
    public:
    Person();
    ~Person();

    //Sets:
    void setID(int id);
    void setName(string n);
    void setLevel(string lev);
    //Gets:
    int getID();
    string getName();
    string getLevel();

    //Helper funcs
    bool lessThan(Person* p);
    bool greaterThan(Person* p);
    bool equalTo(Person* p);
    void printInfo();

    protected:
    int idNum;
    string name;
    string level;
};
#endif