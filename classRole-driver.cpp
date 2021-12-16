#include "student.h"
#include <string>
#include <iomanip>
#include <fstream>

//These are all the capabilites that the admin has
void printOptions(){
    cout << endl << "========================================================================================="<< endl << endl;
    cout << "1: Add student" << endl;
    cout << "2: Remove student" << endl;
    cout << "3: Update exsisting student records" << endl;
    cout << "4: Retrive exsisting student records" << endl;
    cout << "5: Update all students" << endl;
    cout << "6: View sample student record" << endl;
    cout << "7: QUIT" << "\nYour choice: ";
}


//this function will check if file already exist or not
bool openFile(string fileName){
    ifstream file;
    file.open(fileName);
    if(file)//file exist so, append or remove to/from existing file
        return 1;
    else//file does not already exisit so it will be created later
        return 0;

}

//this function will be used to update a feild for a given student(line)
string updateFeild(int feild, string victimLine, string update, bool &flag) {
    int count = 0;
    string word;//will be used to reconstruct line with updated feild
    istringstream iss(victimLine);//victim is the line in the file to be manipulated
    ostringstream oss;
    while(iss >> word){
        if(count != feild)//if we are not at desired feild copy data that already exist
            oss << word << " ";
        else if (count == feild) {//if at given field, do not input current dataa, instead put update
            oss << update << " ";
            flag = true;
        }
        count++;
    }
    oss << endl;
    return oss.str();
}

//this fucntion will find the desired information in the the given feild
string fetchFeild(int feild, string line){
    int count = 0;
    string word, target;
    istringstream iss(line);// eaach line is a differnt student so this is the target student
    while(iss >> word){    
        if(count == feild)//once at the feild, store what is there in target to later be returned to calling function
            target = word;
        count++;
    }
    return target;
}

/*cout << "0: USF ID, 1: First Name, 2: Last Name 3: Email, 4: Essay Grade, 5: Presentation Grade, 6: Project Grade: "; cin >> feild;
                cout << "Enter updated information: "; cin >> update;
*/
void validateUpdateField(string& input, int& field) {
    //check ID
    if (field == 0) {
        Student::IDValidate(input);
    }
    //check first name
    else if (field == 1 || field == 2){
        std::regex pattern("^[a-zA-Z][a-zA-Z]+$");
        bool validate = regex_match(input, pattern);
        //ignore input after space
        cin.ignore(100, '\n');
        cin.clear();
        if (validate == false) {
            cout << "Invalid Name! Try again: ";
            cin >> input;
            validateUpdateField(input, field);
        }
    }
    //check lastname
    else if (field == 2) {
        string first_name_temp = "temp";
        Student::nameValidate(input, first_name_temp);
    }
    //check email
    else if (field == 3) {
        Student::emailValidate(input);
    }
    //check grade
    else if (field == 4 || field == 5 || field == 6) {
        while (true) {
            if (input == "A" || input == "B" || input == "C" || input == "D" || input == "F") {
                break;
            }
            else {
                cout << "\nInvalid Grade Input! Try Again: ";
                cin >> input;
            }
        }
    }
    else {
        cout << "\nInvalid input\n";
        cout << "0: USF ID, 1: First Name, 2: Last Name 3: Email, 4: Essay Grade, 5: Presentation Grade, 6: Project Grade: "; cin >> field;
        cout << "Enter updated information: "; cin >> input;
        validateUpdateField(input, field);
    }
    
}

int main(){
    int userSelction;
    bool firstItr = true;
    string fName, lName, usfID, email, className, fileName;
    string essay, presentation, project;

    cout<<"What class would you like to update/view (e.g. CEN4072)?: ";
    cin >> className;
    fileName = className + ".txt";

    cout << "Hello Admin, make a selection:" << endl;
    printOptions();
    cin >> userSelction;

    while(userSelction != 7){
            if(userSelction == 1){ //add student
                cout << endl << "========================================================================================="<< endl << endl;
                cout << "What is the students usfID(Format: U1234-5678)?: "; cin >> usfID;       
                cout << "What is the students name (First Last)(max 40 characters)?: "; cin >> fName >> lName;
                cout << "What is the USF students Email(max 40 characters)?: "; cin >> email;
                cout << "What grade did the student attain on the essay(A-F)?: "; cin >> essay;
                cout << "What grade did the student attain on the presentation(A-F)?: "; cin >> presentation;
                cout << "What grade did the student attain on the project(A-F)?: "; cin >> project;
                Student* newStudent = new Student(usfID, fName, lName, email, essay, presentation, project);
                if(openFile(fileName)){//calls opnfile to see if class(file) already exist
                    ofstream fileToAppend;
                    fileToAppend.open(fileName,std::ios_base::app);
                    fileToAppend << newStudent->appendTofile();
                }
                else{
                    ofstream newFile(fileName);
                    newFile << newStudent->appendTofile();
                    newFile.close();
                }
                cout << "\nAdd Student Successfully!\n";
            }

            else if(userSelction == 2){//remove student
                cout << endl << "========================================================================================="<< endl << endl;
                string findLine;
                cout << "what is the students USF_ID?: ";
                cin >> usfID;
                //validate input
                Student::IDValidate(usfID);

                ifstream scanFile;
                scanFile.open(fileName);//if we are removing, we can assume the file already exist
                ofstream temp;
                temp.open("temp.txt");
                int count = 0;
                while (getline(scanFile, findLine)){
                  
                    if (findLine.substr(0, usfID.size()) != usfID){//if not at victiom student, put in temp file so everythiing but removed student is in the new temp file
                        temp << findLine << endl;
            
                    }
                    else
                        ++count;
                }
                if (count != 0) {
                    cout << "Remove Successfully!";
                }
                else
                    cout << "\nFailed! StudentID NOT in the record!\n";
                //copies all value but victim to new file and renames file
                scanFile.close();
                temp.close();
                remove(fileName.c_str());
                rename("temp.txt", fileName.c_str());
                
            }
            //update field for one student
            else if(userSelction == 3){
                string findLine, update;
                int field;
                cout << endl << "========================================================================================="<< endl << endl;
                cout << "What is the students USF_ID that you would like to update?: "; cin >> usfID;
                //validate ID
                Student::IDValidate(usfID);

                cout << "What feild would you like to update?: " << endl;
                cout << "0: USF ID, 1: First Name, 2: Last Name 3: Email, 4: Essay Grade, 5: Presentation Grade, 6: Project Grade: "; cin >> field;
                cout << "Enter updated information: "; cin >> update;
                //validate inputs
                validateUpdateField(update, field);

                ifstream scanFile;
                scanFile.open(fileName);
                ofstream temp;
                bool flag = false;
                temp.open("temp.txt");//wrtie everrthing into temp and when we find target student pass it to updateFeild() with updated info and which feild
                while (getline(scanFile, findLine)){
                    if (findLine.substr(0, usfID.size()) != usfID)
                        temp << findLine << endl;
                    else
                        temp << updateFeild(field, findLine, update, flag);
                } 
                if (flag == true) {
                    cout << "\nUpdated Successfully!\n";
                }
                else
                    cout << "\nUpdate Failed! The USF ID NOT in the Record!\n";
                scanFile.close();
                temp.close();
                remove(fileName.c_str());
                rename("temp.txt", fileName.c_str());
            }

            //look up student info
            else if(userSelction == 4){
                string findLine;
                int fetch, choice;
                cout << endl << "========================================================================================="<< endl << endl;
                cout << "Search by: 0: USF_ID 1: Name 2: Email: "; cin >> choice;
                cout << "What information would you like?" << endl;
                cout << "0: USF_ID, 1: First Name, 2: Last Name 3: Email, 4: Essay Grade, 5: Presentation Grade, 6: Project Grade, 7: All" << endl; cin >> fetch;
                    if(choice == 0){
                        cout << "Enter the students UID that you would like to review: "; cin >> usfID;
                        //validate ID
                        Student::IDValidate(usfID);

                        ifstream scanFile;
                        scanFile.open(fileName);
                        while (getline(scanFile, findLine)){
                            if (findLine.substr(0, usfID.size()) == usfID){
                                if(fetch == 7)
                                    cout << "Requested Information: " << findLine << endl; 
                                else
                                    cout << "Requested Information: " << fetchFeild(fetch, findLine) << endl;
                            }
                        }
                    }
                    else if(choice == 1){
                        cout << "Enter the students first and last name that you would like to review: "; cin >> fName >> lName;
                        //validate name
                        Student::nameValidate(fName, lName);

                        string fullName = fName + " " + lName;
                        ifstream scanFile;
                        scanFile.open(fileName);
                        while (getline(scanFile, findLine)){
                            int pos = findLine.find(" ") + 1;//find the first space in line. From data format we can assume after first space is the name
                            if (findLine.substr(pos, fullName.length()) == fullName){
                                if(fetch == 7)
                                    cout << "Requested Information: " << findLine << endl; 
                                else
                                    cout << "Requested Information: " << fetchFeild(fetch, findLine) << endl;
                            }
                        }
                    }

                    else if(choice == 2){
                        cout << "Enter the students email that you would like to review: "; cin >> email;

                        //check email
                        Student::emailValidate(email);

                        ifstream scanFile;
                        scanFile.open(fileName);
                        while (getline(scanFile, findLine)){ 
                            int pos = 0, occur = 0;
                            bool found = false;                           
                            for (unsigned int i = 0; i < findLine.length(); i++) {//we need to find the 3rd space to get to the email
                                if (findLine[i] == ' ') 
                                    occur++;
                                if (occur == 3 && found == false){
                                    pos = i;
                                    found = true;
                                }
                            }

                            if (findLine.substr(pos + 1, email.length()) == email){
                                if(fetch == 7)
                                    cout << "Requested Information: " << findLine << endl; 
                                else
                                    cout << "Requested Information: " << fetchFeild(fetch, findLine) << endl << endl;
                            }
                        }
                    }
            }
            //update specific feild for all students
            else if(userSelction == 5){
                string update, findLine;
                int fieldToUpdate;
                cout << endl << "========================================================================================="<< endl << endl;
                cout << "What field would you like to update for all students?" << endl;
                cout << "0: USF ID, 1: First Name, 2: Last Name 3: Email, 4: Essay Grade, 5: Presentation Grade, 6: Project Grade: "; cin >> fieldToUpdate;
                cout << "Enter updated information: "; cin >> update;
                validateUpdateField(update, fieldToUpdate);

                ifstream updateFile;
                updateFile.open(fileName);
                ofstream temp;
                temp.open("temp.txt");
                bool flag = false;
                while (getline(updateFile, findLine)){
                    temp << updateFeild(fieldToUpdate, findLine, update, flag);
                }
                //display the message
                if (flag == true) {
                    cout << "\nUpdated Successfully!\n";
                }
                else
                    cout << "\nUpdate Failed! The USF ID NOT in the Record!\n";

                updateFile.close();
                temp.close();
                remove(fileName.c_str());
                rename("temp.txt", fileName.c_str());
            }
            //shows example text file input
            else if(userSelction ==6){
                cout << endl << "========================================================================================="<< endl << endl;
                cout << endl << "Example student record: U####-#### FirstName LastName Email(@usf.edu) Essay Presentation Project" << endl;
            }

        

        //while loop will repeat until the user is finished
        firstItr = false;
        if(firstItr == false)
            printOptions();
        cin >> userSelction;
        
    }
    
    cout << "\nBye\n";
    return 0;
}

