#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Student {
public:
    string name;
    int rollNumber;

    Student(string name, int rollNumber) : name(name), rollNumber(rollNumber) {}
};

class Subject {
public:
    string subjectName;
    vector<int> scores;

    Subject(string name) : subjectName(name) {}
};

class ExamManagementSystem {
private:
    vector<Student> students;
    vector<Subject> subjects;

public:
    void addStudent(string name, int rollNumber) {
        students.emplace_back(name, rollNumber);
        cout << "Student added: " << name << " (Roll Number: " << rollNumber << ")" << endl;
    }

    void addSubject(string name) {
        subjects.emplace_back(name);
        cout << "Subject added: " << name << endl;
    }

    void recordScore(int rollNumber, string subjectName, int score) {
        for (auto& subject : subjects) {
            if (subject.subjectName == subjectName) {
                subject.scores.push_back(score);
                cout << "Score recorded: " << score << " for " << subjectName << " (Roll Number: " << rollNumber << ")" << endl;
                return;
            }
        }
        cout << "Subject not found!" << endl;
    }

    void displayResults() {
        cout << "Exam Results:\n";
        for (const auto& subject : subjects) {
            cout << "Subject: " << subject.subjectName << endl;
            for (size_t i = 0; i < subject.scores.size(); ++i) {
                cout << "  Student " << (i + 1) << " Score: " << subject.scores[i] << endl;
            }
        }
    }
};

int main() {
    ExamManagementSystem ems;

    ems.addStudent("Ram", 101);
    ems.addStudent("Shyam", 102);

    ems.addSubject("Mathematics");
    ems.addSubject("Physics");

    ems.recordScore(101, "Mathematics", 85);
    ems.recordScore(102, "Mathematics", 90);
    ems.recordScore(101, "Physics", 78);

    ems.displayResults();

    return 0;
}
