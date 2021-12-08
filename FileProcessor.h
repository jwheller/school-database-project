// Jaden Heller
// 2328279
// jaheller@chapman.edu
// CPSC-350-01
// Assignment 6

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileProcessor{

    public:
    FileProcessor();
    FileProcessor(string fileName);
    ~FileProcessor();
    string getLinesFromFile(string readFileName);
    string* makeArrayFromFile(string readFileName); //Returns each line from the file as an 
    //element in the array
    int getLengthOfFile(string readFileName);
    void writeToFile(string writeFileName, string input1, string input2);
    bool isTxtFile(string name);
    string untranslatedLine;
    string outputFile;
    string translatedText;
    int lineCounter;

    private:
    string *linesArray; //pointer to an array (as varies depending on the file)
    string fileOpenErr;
    fstream readFile;
    fstream writeFile;
    ofstream readWriteFile;
    string fileAsString;
    string fullLineOfFile;
    int numLines;
    
};
#endif