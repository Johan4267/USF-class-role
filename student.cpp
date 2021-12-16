#include "student.h"



Student :: Student(string& id, string& f, string& l, string& e, string& essay, string& presentation, string& project){
    validInput = false;
    setID(id);
    setName(f, l);
    setEmail(e);
    essayGrade = gradeChecker(essay, "essay");
    presentationGrade = gradeChecker(presentation, "presentation");
    projectGrade = gradeChecker(project, "project");
    
}

//Format: XXXX XX,...
void Student :: setName(string first, string last){
    nameValidate(first, last);
    firstName = first;
    lastName = last;
}

void Student :: setID(string id){
    IDValidate(id);
    usfID = id;
}

void Student :: setEmail(string e){
    emailValidate(e);
    email = e;
}

string Student :: gradeChecker(string letterGrade, string assignment){
    bool validInput = false;
    
    while(validInput != true){
        if(letterGrade.length() != 1){
            cout << "Invalid " << assignment << " grade, enter a grade A-F: ";
            cin >> letterGrade;
        }
        if(letterGrade[0] >= 65 && letterGrade[0] <= 68 || letterGrade[0] == 70)
            validInput = true;
        else{
            cout << "Invalid " << assignment << " grade, enter a grade A-F: ";
            cin >> letterGrade;
        }
    }

    return letterGrade;
}

string Student :: appendTofile(){
    return usfID + " " + firstName + " " + lastName + " " + email + " " + essayGrade + " " + presentationGrade + " " + projectGrade + '\n';
 
}

//function to validate ID
//ID Format: U####-####
void Student::IDValidate(string& id) {
    bool validInput = false; // valid inpt is 9 characters
    while (validInput != true) {
        if (check_ID(id)) {
            validInput = true;
        }
        else {
            cout << "Invalid ID, Correct format: U1111-1111: ";
            cin >> id;
        }
    }
}
bool Student::check_ID(string& input)
{
    //check to see if uid have exact 10 chars
    if (input.length() != 10)
    {
        return false;
    }

    //check the U and '-' sign
    if (input[0] != 'U' || input[5] != '-')
    {
        return false;
    }

    //check the digit
    for (int i = 1; i < 5; i++)
    {
        //return 0 if not a digit
        if (isdigit(input[i]) == 0)
        {
            return false;
        }
    }
    for (std::string::size_type i = 6; i < input.length(); i++)
    {
        if (isdigit(input[i] == 0))
        {
            return false;
        }
    }

    return true;

}

//Function to validate name
void Student::nameValidate(string& first, string& last) {
    bool validInput = false; //valid input is no more than 40 characters
    
    const std::regex condition
    ("[a-zA-Z][a-zA-Z ]+$");
    bool validateFirst = regex_match(first, condition);
    bool validateLast = regex_match(last, condition);
    while (validInput != true) {
        string fullName = first + " " + last;

        if (validateFirst != true || validateLast != true) {
            cout << "First Name and Last name only Alphabet! Try Again: ";
            cin >> first >> last;
            continue;
        }
        if (fullName.length() <= 40) {
            validInput = true;
            break;
        }
        else {
            cout << "Your name must be no more than 40 characters, try again: ";
            cin >> first >> last;
            continue;
        }
    }
}

//function to validate email input
void Student::emailValidate(string& e) {
    bool validInput = false; // valid inpt is 10 characters
    while (validInput != true) {
        const std::regex condition
        ("\\w+@usf.edu");

        bool validate = std::regex_match(e, condition);
        if (validate != true) {
            cout << "The USF email need to end with @usf.edu! Try again!: ";
            cin >> e;
            continue;
        }
        if (e.length() <= 40) {
            validInput = true;

            //std::cout << "email must be in the format: abc1@usf.edu" << std::endl;

        }
        else {
            cout << "Your email must be no more than 40 characters, try again:";
            cin >> e;
        }
    }
}