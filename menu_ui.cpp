#include "menu_ui.h"
#include "student.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>

using namespace std;

// Forward declarations for functions from Member 1 and Member 3
void saveToFile(const vector<Student> &students, const string &filename);
Student *searchStudentByName(vector<Student> &students, const string &searchName);
void computeStudentMetrics(Student &student);
void printIndividualReportCard(const Student &student);
double calculateClassAverage(const vector<Student> &students);
double getHighestScore(const vector<Student> &students);
double getLowestScore(const vector<Student> &students);
int countPassingStudents(const vector<Student> &students, double passingThreshold);
int countFailingStudents(const vector<Student> &students, double passingThreshold);

// Robust integer input validator
int getValidatedInt(const string &prompt, int minVal, int maxVal)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            if (value >= minVal && value <= maxVal)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
        }
        cout << "Invalid input. Please enter a number between " << minVal << " and " << maxVal << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Robust double input validator
double getValidatedDouble(const string &prompt, double minVal, double maxVal)
{
    double value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            if (value >= minVal && value <= maxVal)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
        }
        cout << "Invalid input. Please enter a value between " << minVal << " and " << maxVal << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Option 1: Add Student (with Auto-Generated ID)
void addNewStudent(vector<Student> &students, const string &filename)
{
    Student newStudent;
    cout << "\n--- ADD STUDENT ---\n";

    // Auto-generate next Student ID by finding the highest existing ID
    int maxIdNum = 1000; // Base starting number if list is empty

    for (const auto &s : students)
    {
        // Assuming format is 'S' followed by numbers (e.g., "S1001")
        if (s.studentID.length() > 1 && s.studentID[0] == 'S')
        {
            int idNum = stoi(s.studentID.substr(1));
            if (idNum > maxIdNum)
            {
                maxIdNum = idNum;
            }
        }
    }

    int nextIdNum = maxIdNum + 1;
    newStudent.studentID = "S" + to_string(nextIdNum);

    cout << "Assigned Student ID  : " << newStudent.studentID << "\n";

    cout << "Enter Student Name   : ";
    getline(cin, newStudent.name);

    int numCourses = getValidatedInt("Enter number of courses (1-10): ", 1, 10);

    for (int i = 0; i < numCourses; ++i)
    {
        Course c;
        cout << "\nCourse " << (i + 1) << " Name: ";
        getline(cin, c.subjectName);
        c.score = getValidatedDouble("Enter score (0 - 100): ", 0.0, 100.0);
        c.credits = getValidatedInt("Enter course credits (1 - 5): ", 1, 5);
        newStudent.courses.push_back(c);
    }

    computeStudentMetrics(newStudent);
    students.push_back(newStudent);
    saveToFile(students, filename); // Auto-save on change
    cout << "\nStudent successfully added and saved with ID " << newStudent.studentID << "!\n";
}

// Option 2: View Individual Student Record
void viewIndividualRecord(vector<Student> &students)
{
    if (students.empty())
    {
        cout << "\nNo student records available.\n";
        return;
    }

    string searchName;
    cout << "\nEnter student name to view record: ";
    getline(cin, searchName);

    Student *found = searchStudentByName(students, searchName);
    if (found != nullptr)
    {
        printIndividualReportCard(*found);
    }
    else
    {
        cout << "\nStudent \"" << searchName << "\" not found.\n";
    }
}

// Option 3: Update Student Record
void updateStudentRecord(vector<Student> &students, const string &filename)
{
    if (students.empty())
    {
        cout << "\nNo student records available to update.\n";
        return;
    }

    string searchName;
    cout << "\nEnter name of student to update: ";
    getline(cin, searchName);

    Student *found = searchStudentByName(students, searchName);
    if (found == nullptr)
    {
        cout << "Student \"" << searchName << "\" not found.\n";
        return;
    }

    cout << "\nFound Student: " << found->name << " (ID: " << found->studentID << ")\n";
    cout << "1. Update Name\n";
    cout << "2. Re-Enter Course Scores\n";
    int choice = getValidatedInt("Choose update option (1-2): ", 1, 2);

    if (choice == 1)
    {
        cout << "Enter New Name: ";
        getline(cin, found->name);
    }
    else if (choice == 2)
    {
        found->courses.clear();
        int numCourses = getValidatedInt("Enter new number of courses (1-10): ", 1, 10);
        for (int i = 0; i < numCourses; ++i)
        {
            Course c;
            cout << "\nCourse " << (i + 1) << " Name: ";
            getline(cin, c.subjectName);
            c.score = getValidatedDouble("Enter score (0 - 100): ", 0.0, 100.0);
            c.credits = getValidatedInt("Enter course credits (1 - 5): ", 1, 5);
            found->courses.push_back(c);
        }
        computeStudentMetrics(*found);
    }
    saveToFile(students, filename); // Auto-save on change
    cout << "\nStudent record successfully updated and saved!\n";
}

// Option 4: Delete Student Record
void deleteStudentRecord(vector<Student> &students, const string &filename)
{
    if (students.empty())
    {
        cout << "\nNo student records available to delete.\n";
        return;
    }

    string searchName;
    cout << "\nEnter name of student to delete: ";
    getline(cin, searchName);

    auto it = remove_if(students.begin(), students.end(), [&searchName](const Student &s)
                             { return s.name == searchName; });

    if (it != students.end())
    {
        students.erase(it, students.end());
        saveToFile(students, filename); // Auto-save on change
        cout << "\nStudent record successfully deleted and saved!\n";
    }
    else
    {
        cout << "\nStudent \"" << searchName << "\" not found.\n";
    }
}

// Option 5: View Class Analytics Dashboard
void viewClassAnalytics(const vector<Student> &students)
{
    if (students.empty())
    {
        cout << "\nNo student records available for analytics.\n";
        return;
    }

    int passing = countPassingStudents(students, 60.0);
    int failing = countFailingStudents(students, 60.0);

    cout << "\n========================================\n";
    cout << "      CLASS ANALYTICS DASHBOARD         \n";
    cout << "========================================\n";
    cout << " Total Students     : " << students.size() << "\n";
    cout << " Class Average GPA  : " << fixed << setprecision(2) << calculateClassAverage(students) << "\n";
    cout << " Highest GPA        : " << fixed << setprecision(2) << getHighestScore(students) << "\n";
    cout << " Lowest GPA         : " << fixed << setprecision(2) << getLowestScore(students) << "\n";
    cout << " Passing Students   : " << passing << "\n";
    cout << " Failing Students   : " << failing << "\n";
    cout << "========================================\n";
}

// Main Interactive Menu Loop (Strictly 5 Options)
void runApplicationMenu(vector<Student> &students, const string &filename)
{
    int choice = 0;
    do
    {
        cout << "========================================\n";
        cout << "      STUDENT GRADE CALCULATOR          \n";
        cout << "========================================\n";
        cout << " 1. Register New Student Record\n";
        cout << " 2. Retrieve Student Transcript\n";
        cout << " 3. Modify Student Information\n";
        cout << " 4. Remove Student Record\n";
        cout << " 5. Generate Performance Analytics\n";
        cout << "----------------------------------------\n";

        choice = getValidatedInt(" Enter your choice (1-5): ", 1, 5);

        switch (choice)
        {
        case 1:
            addNewStudent(students, filename);
            break;
        case 2:
            viewIndividualRecord(students);
            break;
        case 3:
            updateStudentRecord(students, filename);
            break;
        case 4:
            deleteStudentRecord(students, filename);
            break;
        case 5:
            viewClassAnalytics(students);
            break;
        }
    } while (true);
}