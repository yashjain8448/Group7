#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>

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

    string calculateGrade() {
        int total = 0;
        for (auto &subject : subjects) {
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

    void addStudent(string name, int roll) {
        students.push_back(Student(name, roll));
    }

    void addMarks(int roll, string subjectName, int mark) {
        for (auto &student : students) {
            if (student.rollNumber == roll) {
                student.addSubject(subjectName, mark);
                break;
            }
        }
    }

    void displayStudent(int roll) {
        for (auto &student : students) {
            if (student.rollNumber == roll) {
                cout << "Name: " << student.name << endl;
                cout << "Roll Number: " << student.rollNumber << endl;
                cout << "Marks:" << endl;
                for (auto &subject : student.subjects) {
                    cout << subject.name << ": " << subject.mark << endl;
                }
                cout << "Grade: " << student.calculateGrade() << endl;
                cout << "Attendance: " << student.attendance << " days" << endl;
                cout << "Feedback: " << student.feedback << endl;
                break;
            }
        }
    }

    void displayAllStudents() {
        for (auto &student : students) {
            cout << "Name: " << student.name << endl;
            cout << "Roll Number: " << student.rollNumber << endl;
            cout << "Marks:" << endl;
            for (auto &subject : student.subjects) {
                cout << subject.name << ": " << subject.mark << endl;
            }
            cout << "Grade: " << student.calculateGrade() << endl;
            cout << "Attendance: " << student.attendance << " days" << endl;
            cout << "Feedback: " << student.feedback << endl;
            cout << "-------------------------" << endl;
        }
    }

    void markAttendance(int roll) {
        for (auto &student : students) {
            if (student.rollNumber == roll) {
                student.attendance++;
                cout << "Attendance marked for " << student.name << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }

    void collectFeedback(int roll, const string &fb) {
        for (auto &student : students) {
            if (student.rollNumber == roll) {
                student.feedback = fb;
                cout << "Feedback recorded for " << student.name << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }

    void generateReport(int roll) {
        for (auto &student : students) {
            if (student.rollNumber == roll) {
                cout << "Report for " << student.name << ":" << endl;
                cout << "Roll Number: " << student.rollNumber << endl;
                cout << "Marks:" << endl;
                for (auto &subject : student.subjects) {
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
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->rollNumber == roll) {
                students.erase(it);
                cout << "Student deleted successfully." << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }

    void searchStudent(int roll) {
        for (auto &student : students) {
            if (student.rollNumber == roll) {
                cout << "Name: " << student.name << endl;
                cout << "Roll Number: " << student.rollNumber << endl;
                for (auto &subject : student.subjects) {
                    cout << subject.name << ": " << subject.mark << endl;
                }
                cout << "Attendance: " << student.attendance << " days" << endl;
                cout << "Feedback: " << student.feedback << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }

    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        for (auto &student : students) {
            outFile << student.rollNumber << " " << student.name << " " << student.attendance << " " << student.feedback;
            for (auto &subject : student.subjects) {
                outFile << " " << subject.name << " " << subject.mark;
            }
            outFile << endl;
        }
        outFile.close();
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "File could not be opened." << endl;
            return;
        }
        students.clear();
        int roll, attendance;
        string name, feedback;
        while (inFile >> roll >> name >> attendance >> feedback) {
            Student student(name, roll);
            student.attendance = attendance;
            student.feedback = feedback;
            string subjectName;
            int mark;
            while (inFile >> subjectName >> mark) {
                student.addSubject(subjectName, mark);
                if (inFile.peek() == '\n') break;
            }
            students.push_back(student);
        }
        inFile.close();
    }
};



class System {
public:
    map<string, string> credentials = {
        {"admin", "admin123"},
        {"teacher", "teacher123"}
    };

    Teacher teacher = Teacher("Prof. Smith");

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

    void changePassword() {
        string username, oldPassword, newPassword;

        cout << "Enter username: ";
        cin >> username;
        cout << "Enter old password: ";
        cin >> oldPassword;

        if (credentials.find(username) != credentials.end() && credentials[username] == oldPassword) {
            cout << "Enter new password: ";
            cin >> newPassword;
            credentials[username] = newPassword;
            cout << "Password changed successfully!" << endl;
        } else {
            cout << "Invalid credentials." << endl;
        }
    }

    void menu() {
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
        cout << "11. Save to File" << endl;
        cout << "12. Load from File" << endl;
        cout << "13. Change Password" << endl;
        cout << "14. Exit" << endl;
    }

    void run() {
        login();
        int choice;

        while (true) {
            menu();
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                string name;
                int roll;
                cout << "Enter student name: ";
                cin >> name;
                cout << "Enter roll number: ";
                cin >> roll;
                teacher.addStudent(name, roll);
            } else if (choice == 2) {
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
            } else if (choice == 3) {
                int roll;
                cout << "Enter roll number: ";
                cin >> roll;
                teacher.displayStudent(roll);
            } else if (choice == 4) {
                teacher.displayAllStudents();
            } else if (choice == 5) {
                int roll;
                cout << "Enter roll number to search: ";
                cin >> roll;
                teacher.searchStudent(roll);
            } else if (choice == 6) {
                int roll;
                string newName;
                cout << "Enter roll number to update: ";
                cin >> roll;
                cout << "Enter new name: ";
                cin >> newName;
                teacher.updateStudent(roll, newName);
            } else if (choice == 7) {
                int roll;
                cout << "Enter roll number to delete: ";
                                cin >> roll;
                teacher.deleteStudent(roll);
            } else if (choice == 8) {
                int roll;
                cout << "Enter roll number: ";
                cin >> roll;
                teacher.markAttendance(roll);
            } else if (choice == 9) {
                int roll;
                string feedback;
                cout << "Enter roll number: ";
                cin >> roll;
                cout << "Enter feedback: ";
                cin.ignore();
                getline(cin, feedback);
                teacher.collectFeedback(roll, feedback);
            } else if (choice == 10) {
                int roll;
                cout << "Enter roll number: ";
                cin >> roll;
                teacher.generateReport(roll);
            } else if (choice == 11) {
                string filename;
                cout << "Enter filename to save: ";
                cin >> filename;
                teacher.saveToFile(filename);
            } else if (choice == 12) {
                string filename;
                cout << "Enter filename to load: ";
                cin >> filename;
                teacher.loadFromFile(filename);
            } else if (choice == 13) {
                changePassword();
            } else if (choice == 14) {
                break;
            } else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};

int main() {
    System system;
    system.run();

    return 0;
}
