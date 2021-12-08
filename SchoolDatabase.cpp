// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

#include "SchoolDatabase.h"

SchoolDatabase::SchoolDatabase(){
    facultyTable = new GenDatabase<Faculty*>();
    studentTable = new GenDatabase<Student*>();
    unAdvisedStudents = new myList<int>();
    nullID = 0; //0 is not a valid Student or Fac ID#, and is used to
    //show that an ID is either undefined or not found
}

SchoolDatabase::~SchoolDatabase(){
    delete studentTable, facultyTable;
}

void SchoolDatabase::PrintStudentTable(){
    studentTable->printAll();
}

void SchoolDatabase::PrintFacultyTable(){
    facultyTable->printAll();
}

void SchoolDatabase::PrintStudentInfo(int studentID){
    if (studentTable->contains(studentID)){
        studentTable->printInfo(studentID);
    }
    else{
        PrintidNotFoundErr(studentID, "Student");
    }
}

void SchoolDatabase::PrintFacultyInfo(int facultyID){
    if (facultyTable->contains(facultyID)){
        facultyTable->printInfo(facultyID);
    }
    else{
        PrintidNotFoundErr(facultyID, "Faculty");
    }
    
}

int SchoolDatabase::GetAdvisorOfStud(int studentID){
    if (studentTable->contains(studentID)){
        Student *s = *studentTable->returnPerson(studentID);
        if (s != NULL){
            return s->getStudentsAdvisor();
        }
    }
    else{
        PrintidNotFoundErr(studentID, "Student");
        return nullID;
    }
}

void SchoolDatabase::PrintAdviseesOfFac(int facultyID){
    if (facultyTable->contains(facultyID)){
        Faculty *f = *facultyTable->returnPerson(facultyID);
        if (f != NULL){
            PrintStudentInfo(f->getAdviseeIDs());
        }

    }
    else{
        PrintidNotFoundErr(facultyID, "Faculty");
    } 
}

void SchoolDatabase::AddNewStudent(Student* student){
    int idNum = student->getID();
    //If there's already a student with the ID number of this new student,
    //Iterate until it unique (an restart at 1000 if it surpasses 3000)
    while (studentTable->contains(idNum)){
        if (idNum <= 3000){
            idNum++;
            student->setID(idNum);
        }
        else{
            idNum = 1000;
        }
    }
    //If the student was defined with an advisor ID that doesn't exist in
    //the facultyTable, give them the defaultAdvisor
    int advisorsID = student->getStudentsAdvisor();
    if (!facultyTable->contains(advisorsID)){
        student->setAdvisor(getDefaultAdvisor());
        if (student->getStudentsAdvisor() == nullID){
            unAdvisedStudents->Append(idNum);
        }
        else{
            advisorsID = student->getStudentsAdvisor();
            Faculty *f = *facultyTable->returnPerson(advisorsID); //Add student to their advisor's
            //adviseeList
            f->addAdvisee(idNum);
        }
    }
    //Finally, add the student to the studentTable
    studentTable->add(student);
    cout << "Student: " << student->getName() << " (ID#: " << idNum << ")"; 
    cout << " added to Database." << endl;
}

void SchoolDatabase::AddNewFaculty(Faculty* facMember){
    int idNum = facMember->getID();

    while (facultyTable->contains(idNum)){
        if (idNum <= 12000){
            idNum++;
            facMember->setID(idNum);
        }
        else{
            idNum = 10000;
        }
    }

    facultyTable->add(facMember);
    cout << "Faculty: " << facMember->getName() << " (ID#: " << idNum << ")"; 
    cout << " added to Database." << endl;

    if (facMember->getID() == getDefaultAdvisor()){ //If this faculty member is the root of the Table:
        while (!unAdvisedStudents->IsEmpty()){ //Remove all the students from the lsit of 
        //unAdvisedStudents and assign them to this faculty member
            int unAdvisedStudID = unAdvisedStudents->PopFront();
            Student *unAdvisedStudent = *studentTable->returnPerson(unAdvisedStudID);
            unAdvisedStudent->setAdvisor(facMember->getID());
            facMember->addAdvisee(unAdvisedStudID);
        }
    }
}

void SchoolDatabase::RemoveStudent(int studentID){

    //Find who their advisor is (their facultyID #)
    int advisorsID = GetAdvisorOfStud(studentID);

    if (studentTable->contains(studentID)){
        
        if(advisorsID != nullID){ //if advisorsID is a valid ID:
            //Remove this students from their advisee lsit
            RemoveAdviseeOfFac(advisorsID, studentID);
        }
        //Finally, remove the student from the studentTable
        studentTable->remove(studentID);
    }
    else if (advisorsID == nullID){ //If they don't have an advisor, just remove them
        unAdvisedStudents->Remove(studentID);
    }

    else{
        PrintidNotFoundErr(studentID, "Student");
    }
}

void SchoolDatabase::RemoveFaculty(int facultyID){
    if (facultyTable->contains(facultyID)){
        Faculty *fm = *facultyTable->returnPerson(facultyID);
        if (fm != NULL){
            //Find the successor to this faculty member:
            Faculty *newAdvisor = facultyTable->getSucessor(fm);
            int newAdvisorID = newAdvisor->getID();
            //Get the current faculty member's list of advisees:
            myList<int> *adviseeList = fm->getAdviseeList();
            while (!adviseeList->IsEmpty()){

                int frontStudID = adviseeList->PopFront(); //Return and remove the front student from the adviseeList
                Student *frontStudent = *studentTable->returnPerson(frontStudID);

                //Check if the successor isn't the same advisor as the current one (as getSuccessor returns
                //the same advisor if they are they only faculty (aka  they are the root))
                if (newAdvisor != NULL && newAdvisorID != facultyID){
                    //For each student in their adviseeList,
                    //Change their advisor to be the sucessor found above
                    frontStudent->setAdvisor(newAdvisorID);
                    //And now add that student to the sucessor's adviseeList:
                    newAdvisor->addAdvisee(frontStudID);

                }
                else{
                    //If there is no faculty successor, set the student's advisor to a null ID number
                    frontStudent->setAdvisor(nullID);
                    unAdvisedStudents->Append(frontStudID);
                }
            }
        }
        //Lastly,remove the faculty member from the facultyTable
        facultyTable->remove(facultyID);
    }
    else{
        PrintidNotFoundErr(facultyID, "Faculty");
    }

}

void SchoolDatabase::ChangeAdvisorOfStudent(int studentID, int newfacultyID){
    if (studentTable->contains(studentID)){
        if (facultyTable->contains(newfacultyID)){
            Student *s = *studentTable->returnPerson(studentID);
            int oldAdvisorsID = s->getStudentsAdvisor();
            if (newfacultyID != oldAdvisorsID){ //Skip if the "new faculty" is already the student's advisor
                s->setAdvisor(newfacultyID);
                unAdvisedStudents->Remove(studentID);
                //Remove student from old faculty-member's AdviseeList
                RemoveAdviseeOfFac(oldAdvisorsID, studentID);
            }
        }
        else{
            PrintidNotFoundErr(newfacultyID, "Faculty");
        }
    }
    else{
        PrintidNotFoundErr(studentID, "Student");
    }
}

void SchoolDatabase::AddAdviseeOfFac(int facultyID, int addStudentID){
    Faculty *fm = *facultyTable->returnPerson(facultyID);
    fm->addAdvisee(addStudentID);
}

void SchoolDatabase::RemoveAdviseeOfFac(int facultyID, int removeStudID){
    
    if (facultyTable->contains(facultyID)){
        if (studentTable->contains(removeStudID)){
            Faculty *fm = *facultyTable->returnPerson(facultyID);
            if (fm != NULL){
                fm->removeAdvisee(removeStudID);
                //Change that removed student's advisor to this current faculty's successor
                Student *s = *studentTable->returnPerson(removeStudID);
                if (s != NULL){
                    Faculty *sucFac = facultyTable->getSucessor(fm);
                    if (sucFac != fm){
                        s->setAdvisor(sucFac->getID());
                        sucFac->addAdvisee(removeStudID);
                    }
                    else{
                        s->setAdvisor(nullID);
                        unAdvisedStudents->Append(removeStudID);
                    }
                }
            }
        }
        else{
            PrintidNotFoundErr(removeStudID, "Student");
        }
    }
    else{
        PrintidNotFoundErr(facultyID, "Faculty");
    }
}

void SchoolDatabase::PrintidNotFoundErr(int missingID, string idType){
    cout << missingID << " is not an existing " << idType << "-ID Number" << endl;
}

int SchoolDatabase::getDefaultAdvisor(){
    if (facultyTable->isEmpty()){
        return nullID;
    }
    else{
        return (facultyTable->getRoot())->getID();
    }
}

int SchoolDatabase::GenRandomID(bool isStudent){
    int randID;
    srand(time(0)); //Seed for rand() to use based on time
    randID = rand() % 2000; //Set randID equal to a random number between 0 and 2,000
    

    if(isStudent){
        randID += 1000; //All student ID's will be between 1,000 and 3,000
    }
    else{
        randID += 10000; //All faculty ID's will between 10,000 and 12,000
    }
    return randID;
}

int SchoolDatabase::IDfromString(string idString){
    int idNum;
    bool isIDNumInt = false;
    while(!isIDNumInt){
        try{
            idNum = stoi(idString);
            isIDNumInt = true;
        }
        catch(...){
            cout << "Please enter only numbers: ";
            cin >> idString;
        }
    }
    return idNum;
}

void SchoolDatabase::ExportDatabase(string tableType){ //Save data to a file
    if (tableType == "Faculty"){
        cout << "FACULTYTABLE:" << endl;
        PrintFacultyTable();
    }
    else{
        cout << "STUDENTTABLE:" << endl;
        PrintStudentTable();
    }
}

bool SchoolDatabase::DatabaseIsEmpty(){
    if(facultyTable->isEmpty() && studentTable->isEmpty() && unAdvisedStudents->IsEmpty()){
        return true;
    }
    else{
        return false;
    }
}

void SchoolDatabase::ImportDatabase(string inputArray[], int arraySize){
    string idNum;
    int intIdNum;
    string name;
    string level;

    if (arraySize > 0){
        if(inputArray[0] == "FACULTYTABLE:"){ //Header of the save files tell what they hold
            string department;
            for (int i = 1; i < arraySize; i++){
                if(inputArray[i].rfind("ID Number:", 0) == 0){ //rdfind checks in that string is in the
                //inputArray[i] string, starting at index/char 0. == 0 means it didn't have to skip
                //any chars to find it
                    idNum = ""; //Reset the string holder
                    for (int p = 11; p < inputArray[i].size(); p++){
                        idNum += inputArray[i][p]; //add in each char in that line starting from
                        //11 (length of "ID Number:" plus a space)
                    }
                    intIdNum = stoi(idNum); //convert to int
                    continue;
                }

                else if (inputArray[i].rfind("Name:", 0) == 0){
                    name = "";
                    for (int p = 6; p < inputArray[i].size(); p++){
                        name += inputArray[i][p];
                    }
                    continue;
                }

                else if (inputArray[i].rfind("Level:", 0) == 0){
                    level = "";
                    for (int p = 7; p < inputArray[i].size(); p++){
                        level += inputArray[i][p];
                    }
                    continue;
                }

                else if (inputArray[i].rfind("Department:", 0) == 0){
                    department = "";
                    for (int p = 12; p < inputArray[i].size(); p++){
                        department += inputArray[i][p];
                    }
                    Faculty *fm = new Faculty(intIdNum, name, level, department);
                    AddNewFaculty(fm); //Create new fac with these params and then add them to the facTable
                    continue; 
                }

                else if (inputArray[i].rfind("Advisees:", 0) == 0 && !(inputArray[i].rfind("List is empty", 10) == 0)){
                    int startIndex = 10; //len of "Advisees: "
                    string eachAdvisee;
                    int intEachAdvisee;
                    for (int p = 10; p < inputArray[i].size(); p++){
                        if (inputArray[i][p] != ','){
                            eachAdvisee += inputArray[i][p];
                        }
                        else{ //When it hits a comma, add everything before it to the string
                            intEachAdvisee = stoi(eachAdvisee);
                            AddAdviseeOfFac(intIdNum, intEachAdvisee);
                            eachAdvisee = "";
                        }
                    }    
                    continue;
                }
            }
        }
        else if (inputArray[0] == "STUDENTTABLE:"){
            string major;
            string gpa;
            double dubGpa;
            string advisorID;
            int intAdvisorID;

            for (int i = 1; i < arraySize; i++){
                if(inputArray[i].rfind("ID Number:", 0) == 0){
                    idNum = ""; 
                    for (int p = 11; p < inputArray[i].size(); p++){
                        idNum += inputArray[i][p];
                    }
                    intIdNum = stoi(idNum);
                    continue;
                }

                else if (inputArray[i].rfind("Name:", 0) == 0){
                    name = "";
                    for (int p = 6; p < inputArray[i].size(); p++){
                        name += inputArray[i][p];
                    }
                    continue;
                }

                else if (inputArray[i].rfind("Level:", 0) == 0){
                    level = "";
                    for (int p = 7; p < inputArray[i].size(); p++){
                        level += inputArray[i][p];
                    }
                    continue;
                }

                else if (inputArray[i].rfind("Major:", 0) == 0){
                    major = "";
                    for (int p = 7; p < inputArray[i].size(); p++){
                        major += inputArray[i][p];
                    }
                    continue;
                }

                else if (inputArray[i].rfind("GPA:", 0) == 0){
                    gpa = "";
                    for (int p = 5; p < inputArray[i].size(); p++){
                        gpa += inputArray[i][p];
                    }
                    dubGpa = stod(gpa); //stod() casts strings to doubles
                    continue;
                }

                else if (inputArray[i].rfind("Advisor's ID:", 0) == 0){
                    advisorID = "";
                    for (int p = 14; p < inputArray[i].size(); p++){
                        advisorID += inputArray[i][p];
                    }
                    intAdvisorID = stoi(advisorID);

                    Student *st = new Student(intIdNum, name, level, major, dubGpa, intAdvisorID);
                    AddNewStudent(st);
                    continue;
                }
            }
        }
    }  
}
