# CPSC350_FA21_ASSIGNMENT6_HELLER
Jaden Heller
2328279
jaheller@chapman.edu
CPSC-350-01
Assignment 6


Student Database using trees


Classes:

SchoolDatabase: Implements GenDatabase to create a Student-Table and Faculty-Table and handles the functions that require an interaction between the two
GenDatabase: Abstracts bst.h and presents only the functions that will be needed for a person-Table (holds either students or faculty)
Person:  Parent class for Student and Faculty
Faculty: Class used to create Faculty objects in the database
Student: Class used to create student objects in the database
ListInterface: Abstract Interface for the doubleLinkedList class
DoubleLinkedList: List used to keep track of students without an advisor
ListNode: Nodes for double-linked list
bst: Template class for both the BST and their nodes
FileProcessor: Handles file opening, input, and output
RollbackStack: "Undo" function -> not used in final version
main 


Known Problems:

No Rollback function


Tools/Resources:

User response showed how to use some fstream rdbuf() methods so that std::cout prints to the file (Used in SchoolDatabase.cpp): https://stackoverflow.com/questions/10150468/how-to-redirect-cin-and-cout-to-files



