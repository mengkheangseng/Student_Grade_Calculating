#include "student.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Save records to a text file when exiting
void saveToFile(const vector<Student> &students, const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Could not open file for saving!\n";
        return;
    }

    for (const auto &s : students)
    {
        // Write basic student info and summary stats
        file << s.studentID << ","
             << s.name << ","
             << s.totalCreditsAttempted << ","
             << s.totalCreditsEarned << ","
             << s.cumulativeGPA << ","
             << s.academicStanding;

        // Append each course separated by ';' and fields separated by '|'
        for (const auto &c : s.courses)
        {
            file << "," << c.subjectName << "|"
                 << c.score << "|"
                 << c.credits << "|"
                 << c.grade << "|"
                 << c.gpa;
        }
        file << "\n";
    }
    file.close();
    cout << "Report card data successfully saved to " << filename << "\n";
}
// Load records from a text file when starting up
void loadFromFile(vector<Student> &students, const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        return; // File might not exist yet on the first run, which is totally fine!
    }

    students.clear();
    string line;
    while (getline(file, line))
    {
        stringstream ss(line); // ss is just a variable name that the programmer chose. It stands for "string stream,"
        Student s;
        string tempStr;

        // Read basic student info
        getline(ss, s.studentID, ',');
        getline(ss, s.name, ',');

        getline(ss, tempStr, ',');
        s.totalCreditsAttempted = stoi(tempStr); // stoi stands for "string to integer".

        getline(ss, tempStr, ',');
        s.totalCreditsEarned = stoi(tempStr);

        getline(ss, tempStr, ',');
        s.cumulativeGPA = stod(tempStr);

        getline(ss, s.academicStanding, ',');

        // Read remaining chunks as courses
        string courseChunk;
        while (getline(ss, courseChunk, ','))
        {
            stringstream courseStream(courseChunk);
            Course c;
            string field;

            getline(courseStream, c.subjectName, '|');

            getline(courseStream, field, '|');
            c.score = stod(field);

            getline(courseStream, field, '|');
            c.credits = stoi(field);

            getline(courseStream, c.grade, '|');

            getline(courseStream, field, '|');
            c.gpa = stod(field);

            s.courses.push_back(c);
        }

        students.push_back(s);
    }
    file.close();
}