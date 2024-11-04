#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

class Subject {
public:
    string name;
    int mark;

    Subject(string n, int m) : name(n), mark(m) {}
};

class Student {
public:
    string name;
    int rollNumber;
    vector<Subject> subjects;
    int attendance;
    string feedback;

    Student(string n, int roll) : name(n), rollNumber(roll), attendance(0) {}

    void addSubject(string subjectName, int mark) {
        subjects.push_back(Subject(subjectName, mark));
    }

    string calculateGrade() const {  // Added const qualifier
        if (subjects.empty()) return "N/A";  // Avoid division by zero if no subjects
        int total = 0;
        for (const auto &subject : subjects) {
            total += subject.mark;
        }
        int average = total / subjects.size();

        if (average >= 90) return "A";
        else if (average >= 80) return "B";
        else if (average >= 70) return "C";
        else if (average >= 60) return "D";
        else return "F";
    }
};

class Teacher {
public:
    string name;
    vector<Student> students;

    Teacher(string n) : name(n) {}

    void addStudent(const string &name, int roll) {
        // Check if the student already exists
        for (const auto &student : students) {
            if (student.rollNumber == roll) {
                cout << "Student with roll number " << roll << " already exists." << endl;
                return;
            }
        }
        students.emplace_back(name, roll);
        cout << "Student added successfully." << endl;
    }

    void addMarks(int roll, const string& subjectName, int mark) {
    for (auto& student : students) {
        if (student.rollNumber == roll) {
            // Check if the subject already exists
            for (auto& subject : student.subjects) {
                if (subject.name == subjectName) {
                    subject.mark = mark; // Update the mark if subject exists
                    cout << "Marks updated for " << subjectName << "." << endl;
                    return;
                }
            }
            // If subject does not exist, add a new one
            student.addSubject(subjectName, mark);
            cout << "Marks added for " << subjectName << "." << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
}


    void displayStudent(int roll) const {  // Added const qualifier
        for (const auto &student : students) {
            if (student.rollNumber == roll) {
                cout << "Name: " << student.name << endl;
                cout << "Roll Number: " << student.rollNumber << endl;
                cout << "Marks:" << endl;
                for (const auto &subject : student.subjects) {
                    cout << subject.name << ": " << subject.mark << endl;
                }
                cout << "Grade: " << student.calculateGrade() << endl;
                cout << "Attendance: " << student.attendance << " days" << endl;
                cout << "Feedback: " << student.feedback << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }

    void displayAllStudents() const {  // Added const qualifier
        if (students.empty()) {
            cout << "No students found." << endl;
            return;
        }
        for (const auto &student : students) {
            displayStudent(student.rollNumber);
            cout << "-------------------------" << endl;
        }
    }

    void markAttendance(int roll) {
        for (auto &student : students) {
            if (student.rollNumber == roll) {
                student.attendance++;
                cout << "Attendance marked for " << student.name << "." << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }

    void collectFeedback(int roll, const string &fb) {
        for (auto &student : students) {
            if (student.rollNumber == roll) {
                student.feedback = fb;
                cout << "Feedback recorded for " << student.name << "." << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }

    void generateReport(int roll) const {  // Added const qualifier
        for (const auto &student : students) {
            if (student.rollNumber == roll) {
                cout << "Report for " << student.name << ":" << endl;
                cout << "Roll Number: " << student.rollNumber << endl;
                cout << "Marks:" << endl;
                for (const auto &subject : student.subjects) {
                    cout << subject.name << ": " << subject.mark << endl;
                }
                cout << "Grade: " << student.calculateGrade() << endl;
                cout << "Attendance: " << student.attendance << " days" << endl;
                cout << "Feedback: " << student.feedback << endl;
                cout << "-------------------------" << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }

    void updateStudent(int roll, const string &newName) {
        for (auto &student : students) {
            if (student.rollNumber == roll) {
                student.name = newName;
                cout << "Student updated successfully." << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }

    void deleteStudent(int roll) {
        auto it = find_if(students.begin(), students.end(), [&](const Student &s) {
            return s.rollNumber == roll;
        });

        if (it != students.end()) {
            students.erase(it);
            cout << "Student deleted successfully." << endl;
        } else {
            cout << "Student not found." << endl;
        }
    }

    void searchStudent(int roll) const {  // Added const qualifier
        for (const auto &student : students) {
            if (student.rollNumber == roll) {
                cout << "Name: " << student.name << endl;
                cout << "Roll Number: " << student.rollNumber << endl;
                for (const auto &subject : student.subjects) {
                    cout << subject.name << ": " << subject.mark << endl;
                }
                cout << "Attendance: " << student.attendance << " days" << endl;
                cout << "Feedback: " << student.feedback << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }

    void saveToFile(const string &filename) const {  // Added const qualifier
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "File could not be opened." << endl;
            return;
        }
        for (const auto &student : students) {
            outFile << student.rollNumber << " " << student.name << " " << student.attendance << " " << student.feedback;
            for (const auto &subject : student.subjects) {
                outFile << " " << subject.name << " " << subject.mark;
            }
            outFile << endl;
        }
        outFile.close();
        cout << "Data saved to " << filename << " successfully." << endl;
    }

    void loadFromFile(const string &filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "File could not be opened." << endl;
            return;
        }
        students.clear();
        int roll, attendance;
        string name, feedback;
        while (inFile >> roll >> ws && getline(inFile, name, ' ')) {
            inFile >> attendance >> ws;
            getline(inFile, feedback, ' '); // Read feedback
            Student student(name, roll);
            student.attendance = attendance;
            student.feedback = feedback;
            string subjectName;
            int mark;
            while (inFile >> subjectName >> mark) {
                student.addSubject(subjectName, mark);
                if (inFile.peek() == '\n') break; // Stop if a new line is encountered
            }
            students.push_back(student);
        }
        inFile.close();
        cout << "Data loaded from " << filename << " successfully." << endl;
    }
};

class System {
public:
    map<string, string> credentials;

    Teacher teacher = Teacher("Prof. Smith");

    void addCredentials() {
        string username, password;

        cout << "Enter new username: ";
        cin >> username;

        // Check if the username already exists
        if (credentials.find(username) != credentials.end()) {
            cout << "Username already exists. Please choose a different username." << endl;
            return;
        }

        cout << "Enter password: ";
        cin >> password;

        // Add the new username and password
        credentials[username] = password;
        cout << "Credentials added successfully!" << endl;
    }

    void changePassword() {
        string username, oldPassword, newPassword;

        cout << "Enter username: ";
        cin >> username;

        // Check if the username exists
        if (credentials.find(username) != credentials.end()) {
            cout << "Enter old password: ";
            cin >> oldPassword;

            // Check if the old password is correct
            if (credentials[username] == oldPassword) {
                cout << "Enter new password: ";
                cin >> newPassword;

                // Update the password
                credentials[username] = newPassword;
                cout << "Password updated successfully!" << endl;
            } else {
                cout << "Incorrect old password. Password not updated." << endl;
            }
        } else {
            cout << "Username not found. Cannot update password." << endl;
        }
    }

    void login() {
        string username, password;

        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (credentials.find(username) != credentials.end() && credentials[username] == password) {
            cout << "Login successful!" << endl;
        } else {
            cout << "Invalid credentials. Exiting..." << endl;
            exit(0);
        }
    }

    void addOrUpdateCredentials() {
        string username, oldPassword, newPassword;

        cout << "Enter username: ";
        cin >> username;

        // Check if the username exists
        if (credentials.find(username) != credentials.end()) {
            cout << "Enter old password: ";
            cin >> oldPassword;

            // Check if the old password is correct
            if (credentials[username] == oldPassword) {
                cout << "Enter new password: ";
                cin >> newPassword;

                // Update the password
                credentials[username] = newPassword;
                cout << "Password updated successfully!" << endl;
            } else {
                cout << "Incorrect old password. Password not updated." << endl;
            }
        } else {
            cout << "Username not found. Cannot update password." << endl;
        }
    }

    void menu() {
        cout << "\n=== Exam Management System ===" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Add Marks" << endl;
        cout << "3. Display Student" << endl;
        cout << "4. Display All Students" << endl;
        cout << "5. Search Student" << endl;
        cout << "6. Update Student" << endl;
        cout << "7. Delete Student" << endl;
        cout << "8. Mark Attendance" << endl;
        cout << "9. Collect Feedback" << endl;
        cout << "10. Generate Report" << endl;
        cout << "11. Save Data" << endl;
        cout << "12. Load Data" << endl;
        cout << "13. Change Password" << endl;
        cout << "14. Add/Update Credentials" << endl; // Optional, can be kept
        cout << "15. Exit" << endl;
    }

    void run() {
        // First check if there are existing credentials
        if (credentials.empty()) {
            char choice;
            cout << "No existing credentials found. Would you like to add a new user? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                addCredentials();
            }
        }

        // Now proceed to login
        login();

        while (true) {
            menu();
            int choice;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    string name;
                    int roll;
                    cout << "Enter student name: ";
                    cin >> name;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    teacher.addStudent(name, roll);
                    break;
                }
                case 2: {
                    int roll;
                    string subjectName;
                    int mark;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    cout << "Enter subject name: ";
                    cin >> subjectName;
                    cout << "Enter mark: ";
                    cin >> mark;
                    teacher.addMarks(roll, subjectName, mark);
                    break;
                }
                case 3: {
                    int roll;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    teacher.displayStudent(roll);
                    break;
                }
                case 4:
                    teacher.displayAllStudents();
                    break;
                case 5: {
                    int roll;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    teacher.searchStudent(roll);
                    break;
                }
                case 6: {
                    int roll;
                    string newName;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    cout << "Enter new name: ";
                    cin >> newName;
                    teacher.updateStudent(roll, newName);
                    break;
                }
                case 7: {
                    int roll;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    teacher.deleteStudent(roll);
                    break;
                }
                case 8: {
                    int roll;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    teacher.markAttendance(roll);
                    break;
                }
                case 9: {
                    int roll;
                    string feedback;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    cout << "Enter feedback: ";
                    cin.ignore();
                    getline(cin, feedback);
                    teacher.collectFeedback(roll, feedback);
                    break;
                }
                case 10: {
                    int roll;
                    cout << "Enter roll number: ";
                    cin >> roll;
                    teacher.generateReport(roll);
                    break;
                }
                case 11: {
                    string filename;
                    cout << "Enter filename to save: ";
                    cin >> filename;
                    teacher.saveToFile(filename);
                    break;
                }
                case 12: {
                    string filename;
                    cout << "Enter filename to load: ";
                    cin >> filename;
                    teacher.loadFromFile(filename);
                    break;
                }
                case 13:
                    changePassword();
                    break;
                case 14:
                    addOrUpdateCredentials(); // Optional
                    break;
                case 15:
                    exit(0);
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};


int main() {
    System examSystem;
    examSystem.run();
    examSystem.menu();
    return 0;
}
