#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


 // .\program.exe
/*
struct Student == mag define sa simple structure nga naga hold sa students ID, full name, and section.
readStudents == read the entire students.txt file, splits each line by commas, creates Student objects, and returns them in a vector.
saveStudents == overwrites students.txt with the updated list of students by writing each student's data line-by-line.
addStudent == prompts the user for student details and appends a new record to students.txt.
viewStudents == reads and prints every line in students.txt, showing all registered students.
searchStudent == asks for an ID and searches the file for a line that starts with that ID, displaying the matching record.
editStudent == loads all students, finds the one with the matching ID, updates the name and section, then saves the modified list back to the file.
deleteStudent == loads all students, removes the one with the specified ID, and overwrites the file with the remaining students.
    */

struct Student {
    string id, name, section;
};

vector<Student> readStudents() {
    vector<Student> students;
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Student s;
        getline(ss, s.id, ',');
        getline(ss, s.name, ',');
        getline(ss, s.section, ',');
        if (!s.id.empty()) students.push_back(s);
    }
    return students;
}

void saveStudents(const vector<Student>& students) {
    ofstream file("students.txt", ios::trunc);
    for (const auto& s : students)
        file << s.id << "," << s.name << "," << s.section << "\n";
}

void addStudent() {
    Student s;
    cout << "\nEnter Student ID: ";
    cin >> s.id;
    cin.ignore();
    cout << "Enter Full Name: ";
    getline(cin, s.name);
    cout << "Enter Section: ";
    getline(cin, s.section);

    ofstream file("students.txt", ios::app);
    if (!file) { cout << "\nError opening file.\n"; return; }

    file << s.id << "," << s.name << "," << s.section << "\n";
    cout << "\nStudent added successfully!\n";
}

void viewStudents() {
    ifstream file("students.txt");
    if (!file) { cout << "\nNo records found.\n"; return; }

    string line;
    bool found = false;
    cout << "\nSTUDENT LIST:\n";
    while (getline(file, line)) {
        cout << line << endl;
        found = true;
    }
    if (!found) cout << "(No students found)\n";
}

void searchStudent() {
    string id;
    cout << "\nEnter Student ID to search: ";
    cin >> id;

    ifstream file("students.txt");
    if (!file) { cout << "\nNo records found.\n"; return; }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.find(id + ",") == 0) {
            cout << "\nFound: " << line << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "\nStudent not found.\n";
}

void editStudent() {
    vector<Student> students = readStudents();
    string id;
    cout << "\nEnter Student ID to edit: ";
    cin >> id;
    cin.ignore();

    bool found = false;
    for (auto& s : students) {
        if (s.id == id) {
            found = true;
            cout << "\nEditing student: " << s.name << endl;
            cout << "Enter new Full Name: ";
            getline(cin, s.name);
            cout << "Enter new Section: ";
            getline(cin, s.section);
            break;
        }
    }

    if (found) {
        saveStudents(students);
        cout << "\nStudent updated successfully!\n";
    } else {
        cout << "\nStudent not found.\n";
    }
}

void deleteStudent() {
    vector<Student> students = readStudents();
    string id;
    cout << "\nEnter Student ID to delete: ";
    cin >> id;

    bool found = false;
    vector<Student> updated;
    for (auto& s : students) {
        if (s.id != id) {
            updated.push_back(s);
        } else {
            found = true;
        }
    }

    if (found) {
        saveStudents(updated);
        cout << "\nStudent deleted successfully!\n";
    } else {
        cout << "\nStudent not found.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\nSTUDENT INFORMATION SYSTEM";
        cout << "\n1. Add Student";
        cout << "\n2. View All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Edit Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\nChoose option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: editStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "\nGoodbye!\n"; break;
            default: cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
