// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

// #include "RollbackStack.h"
#include "FileProcessor.h"
#include <fstream>
#include "SchoolDatabase.h"
// #include <iostream>
int main(int argc, char **argv){

    const string facultyFile = "facultyTable.txt";
    const string studentFile = "studentTable.txt";

    FileProcessor *facFileProc = new FileProcessor(facultyFile);
    FileProcessor *studFileProc = new FileProcessor(studentFile);
    // RollbackStack *r = new RollbackStack(5);
    // SchoolDatabase *DataBase = r->Peek();
    SchoolDatabase *DataBase = new SchoolDatabase();
    string *fileArray = facFileProc->makeArrayFromFile(facultyFile); //An array where each element is 
    //a line a read/write file
    DataBase->ImportDatabase(fileArray, facFileProc->getLengthOfFile(facultyFile)); //Import dataBase stored
    //in the files specified above

    string *studFileArray = studFileProc->makeArrayFromFile(studentFile);
    DataBase->ImportDatabase(studFileArray, studFileProc->getLengthOfFile(studentFile));
    string userInput;
    const int nullID = 0; //A garbage ID num used for unassigned or removed ID's
    int userInputNum;
    bool isInputInt = false;
    bool exit = false;
    const int numOptions = 15;
    const int OptionMenuNum = 14; //Option number that prints out the option Menu bellow
    string optionsMenu[numOptions + 1] = {
    "1. Print all students and their information (sorted by ascending ID #)", 
    "2. Print all faculty and their information (sorted by ascending ID #)",
    "3. Find and display student's information given their ID #",
    "4. Find and display faculty member's information given their ID #",
    "5. Given a student’s ID #, print all the info of their faculty advisor",
    "6. Given a faculty memeber's ID #, print all the info of all their advisees",
    "7. Add a new student",
    "8. Delete a student given their ID #",
    "9. Add a new faculty member",
    "10. Delete a faculty member given their ID #",
    "11. Change a student’s advisor given the student's and new faculty's ID #'s",
    "12. Remove an advisee from a faculty member given both their ID #'s",
    "13. Rollback",
    "14. Re-print this menu",
    "15. Exit",
    "Pick the number of the command you would like to execute (1-15)"
    };
    
    //Print out the options menu:
    cout << endl;
    for (int i = 0; i <= numOptions; i++){
        cout << optionsMenu[i] << endl;
    }

    while(!exit){
        cin >> userInput;
        while (!isInputInt){ //Make sure the user's selection in 1.) a number and 2.) between 1 and 15
            try{
                userInputNum = stoi(userInput);
                if (userInputNum < 1 || userInputNum > 15){
                    throw(userInput);
                }
                isInputInt = true;
            }
            catch(...){
                cout << userInput << " is not an option listed above. " << endl;
                cout << "Please enter a number between 1 and " << numOptions << endl;
                cin >> userInput;
            }       
        }
        isInputInt = false; //Reset for the next loop

        if (userInputNum == 1){
            DataBase->PrintStudentTable();
        }

        else if (userInputNum == 2){
            DataBase->PrintFacultyTable();
        }

        else if (userInputNum == 3){ //Student info from ID
            string studentID; //Number inputs taken as strings incase the user enters a character
            int intStudentID; //Holds the converted int version of input
            cout << "Enter the Student's ID Number: ";
            cin >> studentID;
            intStudentID = DataBase->IDfromString(studentID); //prompts the user for new input if not a number
            DataBase->PrintStudentInfo(intStudentID);
        }

        else if (userInputNum == 4){ //print Fac info from ID
            string facID;
            cout << "Enter the Faculty member's ID Number: ";
            cin >> facID;  
            DataBase->PrintFacultyInfo(DataBase->IDfromString(facID));
        }

        else if (userInputNum == 5){ //Print advisor's info from Student's ID
            string studID;
            cout << "Enter the Student's ID Number: ";
            cin >> studID;
            int intStudID = DataBase->IDfromString(studID);
            int facID = DataBase->GetAdvisorOfStud(intStudID);
            if(facID != nullID){
                DataBase->PrintFacultyInfo(facID);
            }
        }

        else if (userInputNum == 6){ //Print all advisees of fac given facID
            string facID;
            cout << "Enter the Faculty member's ID Number: ";
            cin >> facID;
            int intFacID = DataBase->IDfromString(facID);
            DataBase->PrintAdviseesOfFac(intFacID);
        }

        else if (userInputNum == 7){ //new student
            int studID = DataBase->GenRandomID(true); //'true' for boolean parameter "isStudent"
            string studName;
            string studLevel;
            string major;
            bool validGPA = false;
            string gpaInput;
            double gpa;
            string advisorID;
            cout << "Enter new student's Name: ";
            cin >> studName;
            cout << "Enter new student's Level: ";
            cin >> studLevel;
            cout << "Enter new student's Major: ";
            cin >> major;
            cout << "Enter new student's GPA: ";
            cin >> gpaInput;
            while(!validGPA){
                try{
                    gpa = stod(gpaInput);
                    validGPA = true;
                }
                catch(...){
                    cout << "Please enter only numbers: ";
                    cin >> gpaInput;
                }
            }
            cout << "Enter new student's Advisor (advisor's ID Number): ";
            cin >> advisorID;
            int intAdvisID = DataBase->IDfromString(advisorID); //Err handling for bad advisorID inputs is done inside AddNewStudent()
            Student *s = new Student(studID, studName, studLevel, major, gpa, intAdvisID);
            DataBase->AddNewStudent(s);
        }
  
        else if (userInputNum == 8){ //delete student with ID
            string studID;
            cout << "Enter the ID Number of the Student to remove them: ";
            cin >> studID;
            int intStudID = DataBase->IDfromString(studID);
            DataBase->RemoveStudent(intStudID);
        }

        else if (userInputNum == 9){ //Add faculty
            int facID = DataBase->GenRandomID(false);
            string facName;
            string facLevel;
            string department;
            cout << "Enter the new faculty member's Name: ";
            cin >> facName;
            cout << "Enter the new faculty member's Level: ";
            cin >> facLevel;
            cout << "Enter the new faculty member's Department: ";
            cin >> department;
            Faculty *f = new Faculty(facID, facName, facLevel, department);
            DataBase->AddNewFaculty(f);
        }

        else if(userInputNum == 10){ //Remove fac from ID
            string facID;
            cout << "Enter the ID Number of the Faculty to remove them: ";
            cin >> facID;
            int intFacID = DataBase->IDfromString(facID);
            DataBase->RemoveFaculty(intFacID);
        }

        else if (userInputNum == 11){ //Change student's advisor
            string studentID;
            string facultyID;
            cout << "Enter the Student's ID Number: ";
            cin >> studentID;
            int intStudentID = DataBase->IDfromString(studentID);
            cout << "Enter the new advisor's Faculty ID Number: ";
            cin >> facultyID;
            int intFacultyID = DataBase->IDfromString(facultyID);
            DataBase->ChangeAdvisorOfStudent(intStudentID, intFacultyID);
        }

        else if (userInputNum == 12){//Remove advisee from advisor
            string facID;
            string studID;
            cout << "Enter the Faculty member's ID Number: ";
            cin >> facID;
            int intFacID = DataBase->IDfromString(facID);
            cout << "Enter the ID Number of the advisee: ";
            cin >> studID;
            int intStudID = DataBase->IDfromString(studID);
            DataBase->RemoveAdviseeOfFac(intFacID, intStudID);
        }

        else if (userInputNum == 13){ //Rollback

            cout << "I wish lol" << endl;
        }

        else if (userInputNum == 14){
            cout << endl;
            for (int i = 0; i <= numOptions; i++){
                cout << optionsMenu[i] << endl;
            }
            continue;
        }

        else if (userInputNum == 15){ //Exit 
            ofstream facExport(facultyFile); //Make it so that std::cout prints to the
            //file, rather than the console
            streambuf *coutbuf = cout.rdbuf();
            cout.rdbuf(facExport.rdbuf());
            DataBase->ExportDatabase("Faculty");
            cout.rdbuf(facExport.rdbuf());
            cout.rdbuf(coutbuf);

            ofstream stuExport(studentFile);
            streambuf *coutbuffer = cout.rdbuf();
            cout.rdbuf(stuExport.rdbuf());
            DataBase->ExportDatabase("Student");
            cout.rdbuf(stuExport.rdbuf());
            cout.rdbuf(coutbuffer); //Set back to regular console printing


            cout << "Exiting program..." << endl;
            exit = true;
            continue; //Skip the helper message bellow
        }
        cout << endl;
        cout << "Enter another command 1-" << numOptions << " (Reminder: " << OptionMenuNum << " prints the ";
        cout << "options menu, " << numOptions << " exits the program): " << endl;
    }
    
    delete DataBase, studFileArray, fileArray, studFileProc, facFileProc;
    return 0;
}