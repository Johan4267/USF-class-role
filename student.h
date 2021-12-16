#ifndef __STUDENT_H
#define __STUDENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

class Student{
    private:
        string usfID;
        string firstName;
        string lastName;
        string email;
        string presentationGrade;
        string essayGrade;
        string projectGrade;
        bool validInput;
    public:
        //constructor
        Student(string&, string&, string&, string&, string&, string&, string&);
        //input checkers
        void setName(string, string);
        void setID(string);
        void setEmail(string);        
        //add object to file
        string appendTofile();

        static string gradeChecker(string, string);
        static bool check_ID(string&);
        static void IDValidate(string& id);
        static void nameValidate(string& first, string& last);
        static void emailValidate(string& e);
        
};

#endif