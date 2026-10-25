#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

using namespace std;

// The shared Student struct
struct Student
{
    string studentID;
    string name;
    vector<string> courseNames;
    vector<double> marks;
    double averageScore;
    string letterGrade;
    string status;
};

// Function declarations for File I/O 
void saveToFile(const vector<Student> &students, const string &filename);
void loadFromFile(vector<Student> &students, const string &filename);

#endif