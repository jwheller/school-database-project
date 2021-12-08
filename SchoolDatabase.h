// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

#ifndef SCHOOLDATABASE_H
#define SCHOOLDATABASE_H

#include "GenDatabase.h"
#include "Student.h"
#include "Faculty.h"
#include <cstdlib> //This and ctime for Rand() function
#include <ctime> 
//Implements GenDatabase to create a Student-Table and Faculty-Table,
//handles the functions that require an interaction between the two
//(changing and removing advisors/advisees), and defines the functions
//that will be present to the user.
class SchoolDatabase{

    public:
    SchoolDatabase();
    ~SchoolDatabase();

    void PrintStudentTable();//Print every student and their info
    void PrintFacultyTable();//Print every faculty and their info
    void PrintStudentInfo(int studentID);//Print a student's info given their ID
    void PrintFacultyInfo(int facultyID);//Print a faculty member's info given their ID
    int GetAdvisorOfStud(int studentID);
    void PrintAdviseesOfFac(int facultyID);
 
    void AddNewStudent(Student* student);
    void AddNewFaculty(Faculty* facMember);
    void RemoveStudent(int studentID);
    void RemoveFaculty(int facultyID);
    void ChangeAdvisorOfStudent(int studentID, int newfacultyID);
    void RemoveAdviseeOfFac(int facultyID, int removeStudID);//Deletes a student from a fac's advisee List
    void RollBack(); //Undo function

    void AddAdviseeOfFac(int facultyID, int addStudentID);//Add advisee to Fac's list
    int GenRandomID(bool isStudent);
    int IDfromString(string idString); //Safely convert IDs entered as strings to ints
    void ExportDatabase(string tableType); //Saves the info into a txt file
    void ImportDatabase(string inputArray[], int arraySize); //Imports data from file when opening

    private:
    GenDatabase<Faculty*> *facultyTable;
    GenDatabase<Student*> *studentTable;
    myList<int> *unAdvisedStudents; //Students who dont have an advisor at the moment
    void PrintidNotFoundErr(int missingID, string idType); 
    int nullID; //Garbage ID number
    int getDefaultAdvisor();
    bool DatabaseIsEmpty(); 
};
#endif