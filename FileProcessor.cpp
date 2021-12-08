// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

#include "FileProcessor.h"


FileProcessor::FileProcessor(){
    fileOpenErr = "Error! Could not open file: ";
}

FileProcessor::FileProcessor(string fileName){
    fileOpenErr = "Error! Could not open file: ";
    
    readFile.open(fileName, ios::in); //Try opening an exiting file
    //with the fileName
    if (readFile.is_open()){
        readFile.close();
    }
    else{ //If it didn't open/it doesnt exist, create a file with the fileName
        readWriteFile.open(fileName);
        if (readWriteFile.is_open()){
            readWriteFile.close();
        }
    }
}
FileProcessor::~FileProcessor(){
    delete linesArray;
}

bool FileProcessor::isTxtFile(string name){
    int nameSize = name.size();
    string fileExtension;//String that holds the last 4 chars of the entered file name,
    //which will be compared against the expected .txt extension
    if(nameSize > 4){ //Will always be longer than the 4 characters used in ".txt"
        for(int i = nameSize-4; i < nameSize; i++){
            fileExtension.push_back(name[i]);
        }
    }

    if (fileExtension == ".txt"){
        return true;
    }
    else
        return false;
}

string FileProcessor::getLinesFromFile(string readFileName){

    readFile.open(readFileName);

    if(readFile.is_open()){
        while(getline(readFile, fileAsString)){
            return fileAsString;       
        }
        return fileAsString;
        readFile.close();
    }
    else{
        cerr << fileOpenErr << readFileName << endl; //If it cant open or can't find the
        //specified file, print the error message then exit/don't return any string
        exit(1);
    }
}

string* FileProcessor::makeArrayFromFile(string readFileName){ //Reurns each line as an
//element in an array

    linesArray = new string[getLengthOfFile(readFileName)];

    readFile.open(readFileName, ios::in);
    if(readFile.is_open()){
        while(getline(readFile, fileAsString)){
            linesArray[lineCounter] = fileAsString;
            lineCounter++; //Increments with each line that's read from the file   
        }
        readFile.close();
    }
    return linesArray;
}


int FileProcessor::getLengthOfFile(string readFileName){
    
    readFile.open(readFileName, ios::in);

    numLines = 0;
    if(readFile.is_open()){
        while(getline(readFile, fileAsString)){
            numLines++; //Increments with each line that's read from the file 
        }
        readFile.close();
    }

    return numLines;
}

void FileProcessor::writeToFile(string writeFileName, string input1, string input2){

    writeFile.open(writeFileName, ios:: out); 

    if(writeFile.is_open()){
        writeFile << input1 << endl;
        writeFile << input2 << endl;
        writeFile.close();
    }
    else{
        cout << fileOpenErr << writeFileName << endl;
    }
}