#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

// student data structure
struct Student {
    string id, name, section;
};

// read all students from file and return as vector
vector<Student> readStudents(string filename) {
    vector<Student> students;
    ifstream file(filename);
    string line;
    
    // loop through each line in file
    while (getline(file, line)) {
        stringstream ss(line);
        Student s;
        
        // parse csv: id, name, section separated by commas
        getline(ss, s.id, ',');
        getline(ss, s.name, ',');
        getline(ss, s. section, ',');
        
        // add student to vector if id is not empty
        if (s.id != "") students.push_back(s);
    }
    
    return students;
}

// save all students to file
void saveStudents(string filename, vector<Student> students) {
    // open file in truncate mode (clear old content)
    ofstream file(filename, ios::trunc);
    
    // write each student as: id,name,section
    for (int i = 0; i < students.size(); i++)
        file << students[i]. id << "," << students[i].name << "," << students[i].section << "\n";
}

// display students in table format with headers
void displayStudents(vector<Student> students) {
    // print table header with fixed width columns
    cout << "\n";
    cout << left << setw(15) << "ID" << setw(25) << "NAME" << setw(15) << "SECTION" << "\n";
    cout << "==================================================\n";
    
    // print each student in table row with fixed width columns
    for (int i = 0; i < students. size(); i++)
        cout << left << setw(15) << students[i]. id << setw(25) << students[i].name << setw(15) << students[i]. section << "\n";
    
    // print table footer
    cout << "==================================================\n";
}

// add new student to file
void addStudent(string filename) {
    Student s;
    
    // get student input from user
    cout << "\nEnter Student ID: ";
    cin >> s.id;
    cin.ignore();  // clear newline from input buffer
    
    cout << "Enter Full Name: ";
    getline(cin, s.name);
    
    cout << "Enter Section: ";
    getline(cin, s.section);
    
    // open file in append mode (add to end of file)
    ofstream file(filename, ios::app);
    
    // check if file opened successfully
    if (!file) {
        cout << "\nError opening file.\n";
        return;
    }
    
    // write new student to file
    file << s.id << "," << s. name << "," << s.section << "\n";
    cout << "\nStudent added successfully!\n";
}

// display all students from file
void viewStudents(string filename) {
    // read all students from file
    vector<Student> students = readStudents(filename);
    
    // check if vector is empty
    if (students. size() == 0) {
        cout << "\nNo records found.\n";
        return;
    }
    
    // display all students in table format
    cout << "\nSTUDENT LIST:\n";
    displayStudents(students);
}

// search student by id
void searchStudent(string filename) {
    string searchId;
    cout << "\nEnter Student ID to search: ";
    cin >> searchId;
    
    // read all students from file
    vector<Student> students = readStudents(filename);
    
    // loop through students to find matching id
    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == searchId) {
            cout << "\nFound:\n";
            
            // create vector with only one student (the found one)
            vector<Student> result;
            result.push_back(students[i]);
            
            // display the found student
            displayStudents(result);
            return;  // exit function
        }
    }
    
    // if loop ends without finding student, print not found
    cout << "\nStudent not found.\n";
}

// edit existing student by id
void editStudent(string filename) {
    string id;
    cout << "\nEnter Student ID to edit: ";
    cin >> id;
    cin.ignore();  // clear newline from input buffer
    
    // read all students from file
    vector<Student> students = readStudents(filename);
    
    // loop through students to find matching id
    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            // display current student name
            cout << "\nEditing student: " << students[i].name << "\n";
            
            // get new information from user
            cout << "Enter new Full Name: ";
            getline(cin, students[i].name);
            
            cout << "Enter new Section: ";
            getline(cin, students[i].section);
            
            // save updated students back to file
            saveStudents(filename, students);
            cout << "\nStudent updated successfully!\n";
            return;  // exit function
        }
    }
    
    // if loop ends without finding student, print not found
    cout << "\nStudent not found.\n";
}

// delete student by id
void deleteStudent(string filename) {
    string id;
    cout << "\nEnter Student ID to delete: ";
    cin >> id;
    
    // read all students from file
    vector<Student> students = readStudents(filename);
    vector<Student> updated;  // vector to store students except the deleted one
    
    // loop through students
    for (int i = 0; i < students.size(); i++) {
        // if student id doesn't match, add to updated vector
        if (students[i].id != id)
            updated.push_back(students[i]);
        else {
            // if id matches, don't add (delete it)
            // save updated students without the deleted one
            saveStudents(filename, updated);
            cout << "\nStudent deleted successfully!\n";
            return;  // exit function
        }
    }
    
    // if loop ends without finding student, print not found
    cout << "\nStudent not found.\n";
}

// main program
int main() {
    string filename = "students.txt";  // file to store student data
    int choice;
    
    // infinite loop until user chooses exit (option 6)
    do {
        // display menu options
        cout << "\n====== STUDENT INFORMATION SYSTEM ======\n";
        cout << "1. Add Student\n";
        cout << "2.  View All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Edit Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "========================================\nChoose option: ";
        
        // check if input is valid number
        if (!(cin >> choice)) {
            cin.clear();  // clear error flag
            cin.ignore(1000, '\n');  // clear input buffer
            cout << "\nInvalid input. Please enter a number.\n";
            continue;  // skip to next loop iteration
        }
        
        // execute function based on user choice
        switch (choice) {
            case 1: addStudent(filename); break;
            case 2: viewStudents(filename); break;
            case 3: searchStudent(filename); break;
            case 4: editStudent(filename); break;
            case 5: deleteStudent(filename); break;
            case 6: cout << "\nGoodbye!\n"; break;
            default: cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 6);  // stop loop when user chooses exit
    
    return 0;
}
