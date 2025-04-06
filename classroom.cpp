#include <iostream>
#include <string>
using namespace std;

// User structure
struct User {
    string username;
    string password;
    string role; // teacher or student
};

// Classroom structure
struct Classroom {
    string className;
    string teacher;
    string students[10];
    string assignments[10];
    int studentCount = 0;
    int assignmentCount = 0;
};

// Global variables
User users[10];
Classroom classrooms[10];
int userCount = 0;
int classCount = 0;

// Function declarations
void registerUser();
void loginUser();
void teacherMenu(const string& username);
void studentMenu(const string& username);
void createClass(const string& teacher);
void joinClass(const string& student);
void postAssignment(const string& teacher);
void viewAssignments(const string& student);

// Main function
int main() {
    int choice;

    while (true) {
        cout << "\n===== Virtual Classroom =====" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice." << endl;
        }
    }
}

// Register a new user
void registerUser() {
    cout << "Enter username: ";
    cin >> users[userCount].username;
    cout << "Enter password: ";
    cin >> users[userCount].password;
    cout << "Enter role (teacher/student): ";
    cin >> users[userCount].role;

    if (users[userCount].role != "teacher" && users[userCount].role != "student") {
        cout << "Invalid role." << endl;
        return;
    }

    userCount++;
    cout << "Registration successful." << endl;
}

// Login user
void loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && users[i].password == password) {
            if (users[i].role == "teacher") {
                teacherMenu(username);
            } else {
                studentMenu(username);
            }
            return;
        }
    }
    cout << "Invalid username or password." << endl;
}

// Teacher menu
void teacherMenu(const string& username) {
    int choice;
    while (true) {
        cout << "\n--- Teacher Menu ---" << endl;
        cout << "1. Create Class" << endl;
        cout << "2. Post Assignment" << endl;
        cout << "3. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createClass(username);
                break;
            case 2:
                postAssignment(username);
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice." << endl;
        }
    }
}

// Student menu
void studentMenu(const string& username) {
    int choice;
    while (true) {
        cout << "\n--- Student Menu ---" << endl;
        cout << "1. Join Class" << endl;
        cout << "2. View Assignments" << endl;
        cout << "3. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                joinClass(username);
                break;
            case 2:
                viewAssignments(username);
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice." << endl;
        }
    }
}

// Create a class
void createClass(const string& teacher) {
    cout << "Enter class name: ";
    cin >> classrooms[classCount].className;

    classrooms[classCount].teacher = teacher;
    classCount++;
    cout << "Class created successfully." << endl;
}

// Join a class
void joinClass(const string& student) {
    string className;
    cout << "Enter class name to join: ";
    cin >> className;

    for (int i = 0; i < classCount; i++) {
        if (classrooms[i].className == className) {
            classrooms[i].students[classrooms[i].studentCount++] = student;
            cout << "Joined class successfully." << endl;
            return;
        }
    }
    cout << "Class not found." << endl;
}

// Post an assignment
void postAssignment(const string& teacher) {
    string className, assignment;
    cout << "Enter class name: ";
    cin >> className;
    cout << "Enter assignment: ";
    cin.ignore();
    getline(cin, assignment);

    for (int i = 0; i < classCount; i++) {
        if (classrooms[i].className == className && classrooms[i].teacher == teacher) {
            classrooms[i].assignments[classrooms[i].assignmentCount++] = assignment;
            cout << "Assignment posted successfully." << endl;
            return;
        }
    }
    cout << "Class not found or unauthorized access." << endl;
}

// View assignments
void viewAssignments(const string& student) {
    string className;
    cout << "Enter class name: ";
    cin >> className;

    for (int i = 0; i < classCount; i++) {
        if (classrooms[i].className == className) {
            cout << "\nAssignments for class " << className << ":" << endl;
            for (int j = 0; j < classrooms[i].assignmentCount; j++) {
                cout << j + 1 << ". " << classrooms[i].assignments[j] << endl;
            }
            return;
        }
    }
    cout << "Class not found." << endl;
}
