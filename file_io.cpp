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
        file << s.studentID << "," << s.name << "," << s.averageScore << "," << s.letterGrade << "," << s.status << "\n";
    }
    file.close();
    cout << "Data successfully saved to " << filename << "\n";
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
        stringstream ss(line);
        Student s;
        string avgStr;

        getline(ss, s.studentID, ',');
        getline(ss, s.name, ',');
        getline(ss, avgStr, ',');
        s.averageScore = stod(avgStr); // Convert string back to double
        getline(ss, s.letterGrade, ',');
        getline(ss, s.status, ',');

        students.push_back(s);
    }
    file.close();
}