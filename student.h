#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

using namespace std;

struct Course
{
    std::string subjectName;
    double score;
    int credits;
    std::string grade;
    double gpa;
};

struct Student
{
    std::string studentID;
    std::string name;
    std::vector<Course> courses;
    int totalCreditsAttempted;
    int totalCreditsEarned;
    double cumulativeGPA;
    std::string academicStanding;
};

// Function declarations for File I/O 
void saveToFile(const vector<Student> &students, const string &filename);
void loadFromFile(vector<Student> &students, const string &filename);


#endif

// #ifndef STUDENT_H / #define STUDENT_H / #endif : These are called header guards.They prevent C++ from accidentally reading this file twice if multiple other files include it, which would cause an error.

// const: Stands for "constant." It is a promise to the computer (and to your teammates) that this function will not change or modify this data.

//vector<Student> & : As we talked about earlier, the &means "pass by reference"(passing the original data instead of a slow photocopy).

//string &filename : Passing the filename reference safely.