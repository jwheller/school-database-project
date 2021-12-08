// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

#include "Faculty.h"

Faculty::Faculty(){
    department;
    adviseeList = new myList<int>();
}

Faculty::Faculty(int fac_id, string fac_name, string fac_level, string fac_department){
    idNum = fac_id;
    name = fac_name;
    level = fac_level;
    department = fac_department;
    adviseeList = new myList<int>();
}

Faculty::~Faculty(){
    delete adviseeList;
}


void Faculty::setFacDepartment(string facDepartment){
    department = facDepartment;
}

string Faculty::getFacDepartment(){
    return department;
}

//adviseeList functions:
void Faculty::addAdvisee(int ID){
    adviseeList->Append(ID);
}

void Faculty::removeAdvisee(int ID){
    adviseeList->Remove(ID);
}

int Faculty::getAdviseeIDs(){ //Return student ID number of all advisees
    return adviseeList->ReturnAll();
}

myList<int>* Faculty::getAdviseeList(){ //Return a pointer to the adviseeList
    return adviseeList;
}
void Faculty::printInfo(){
    cout << "ID Number: " << getID() << endl;
    cout << "Name: " << getName() << endl;
    cout << "Level: " << getLevel() << endl;
    cout << "Department: " << department << endl;
    cout << "Advisees: "; 
    adviseeList->Print();
    cout << endl;
}
