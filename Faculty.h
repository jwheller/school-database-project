// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include <string>

#include "Person.h"
#include "ListInterface.h"

using namespace std;

class Faculty : public Person{
    public:
    Faculty();
    Faculty(int fac_id, string fac_name, string fac_level, string fac_department);
    ~Faculty();
    //Sets:
    void setFacDepartment(string facDepartment);
    //Gets:
    string getFacDepartment();
    void addAdvisee(int ID);
    void removeAdvisee(int ID);
    int getAdviseeIDs();
    void printInfo();
    myList<int>* getAdviseeList();

    private:
    string department;
    myList<int> *adviseeList;
};

#endif