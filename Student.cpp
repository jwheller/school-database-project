// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

#include "Student.h"

Student::Student(){ //Default initializes the three variables unique to Student (that Person.h
//doesnt have)
    major;
    gpa;
    advisorID;
}

Student::Student(int st_id, string st_name, string st_level, string st_major, double st_gpa, int st_advisor){
    idNum = st_id;
    name = st_name;
    level = st_level;
    major = st_major;
    gpa = st_gpa;
    advisorID = st_advisor;
}

Student::~Student(){

}

//"Set" functions:
void Student::setMajor(string studentMajor){
    major = studentMajor;
}

void Student::setGPA(double studentGrade){
    gpa = studentGrade;
}

void Student::setAdvisor(int studentAdvisorID){
    advisorID = studentAdvisorID;
}

//"Get" functions:
string Student::getMajor(){
    return major;
}

double Student::getGPA(){
    return gpa;
}

int Student::getStudentsAdvisor(){
    return advisorID;
}

void Student::printInfo(){
    cout << "ID Number: " << getID() << endl;
    cout << "Name: " << getName() << endl;
    cout << "Level: " << getLevel() << endl;
    cout << "Major: " << major << endl;
    cout << "GPA: " << gpa << endl;
    cout << "Advisor's ID: " << advisorID << endl;
}