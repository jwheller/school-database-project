// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

//Class used to create student objects in the database
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

#include "Person.h"

using namespace std;

class Student : public Person{
    public:
    Student();
    Student(int st_id, string st_name, string st_level, string st_major, double st_gpa, int st_advisor);
    ~Student();
    //sets:
    void setMajor(string studentMajor);
    void setGPA(double studentGrade);
    void setAdvisor(int studentAdvisorID);
    //gets:
    string getMajor();
    double getGPA();
    int getStudentsAdvisor();
    void printInfo();

    private:
    string major;
    double gpa;
    int advisorID;
};
#endif