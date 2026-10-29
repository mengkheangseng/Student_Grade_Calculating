#include "menu_ui.h"
#include "student.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>

// Forward declarations for functions from Member 1 and Member 3
void saveToFile(const std::vector<Student> &students, const std::string &filename);
Student *searchStudentByName(std::vector<Student> &students, const std::string &searchName);
void computeStudentMetrics(Student &student);
void printIndividualReportCard(const Student &student);
double calculateClassAverage(const std::vector<Student> &students);
double getHighestScore(const std::vector<Student> &students);
double getLowestScore(const std::vector<Student> &students);
int countPassingStudents(const std::vector<Student> &students, double passingThreshold);
int countFailingStudents(const std::vector<Student> &students, double passingThreshold);

// Robust integer input validator
int getValidatedInt(const std::string &prompt, int minVal, int maxVal)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
        {
            if (value >= minVal && value <= maxVal)
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        }
        std::cout << "Invalid input. Please enter a number between " << minVal << " and " << maxVal << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Robust double input validator
double getValidatedDouble(const std::string &prompt, double minVal, double maxVal)
{
    double value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
        {
            if (value >= minVal && value <= maxVal)
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        }
        std::cout << "Invalid input. Please enter a value between " << minVal << " and " << maxVal << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Option 1: Add Student (with Auto-Generated ID)
void addNewStudent(std::vector<Student> &students, const std::string &filename)
{
    Student newStudent;
    std::cout << "\n--- ADD STUDENT ---\n";

    // Auto-generate Student ID (e.g., S1001, S1002, S1003...)
    int nextIdNum = 1001 + static_cast<int>(students.size());
    newStudent.studentID = "S" + std::to_string(nextIdNum);

    std::cout << "Assigned Student ID  : " << newStudent.studentID << "\n";

    std::cout << "Enter Student Name   : ";
    std::getline(std::cin, newStudent.name);

    int numCourses = getValidatedInt("Enter number of courses (1-10): ", 1, 10);

    for (int i = 0; i < numCourses; ++i)
    {
        Course c;
        std::cout << "\nCourse " << (i + 1) << " Name: ";
        std::getline(std::cin, c.subjectName);
        c.score = getValidatedDouble("Enter score (0 - 100): ", 0.0, 100.0);
        c.credits = getValidatedInt("Enter course credits (1 - 5): ", 1, 5);
        newStudent.courses.push_back(c);
    }

    computeStudentMetrics(newStudent);
    students.push_back(newStudent);
    saveToFile(students, filename); // Auto-save on change
    std::cout << "\nStudent successfully added and saved with ID " << newStudent.studentID << "!\n";
}

// Option 2: View Individual Student Record
void viewIndividualRecord(std::vector<Student> &students)
{
    if (students.empty())
    {
        std::cout << "\nNo student records available.\n";
        return;
    }

    std::string searchName;
    std::cout << "\nEnter student name to view record: ";
    std::getline(std::cin, searchName);

    Student *found = searchStudentByName(students, searchName);
    if (found != nullptr)
    {
        printIndividualReportCard(*found);
    }
    else
    {
        std::cout << "\nStudent \"" << searchName << "\" not found.\n";
    }
}

// Option 3: Update Student Record
void updateStudentRecord(std::vector<Student> &students, const std::string &filename)
{
    if (students.empty())
    {
        std::cout << "\nNo student records available to update.\n";
        return;
    }

    std::string searchName;
    std::cout << "\nEnter name of student to update: ";
    std::getline(std::cin, searchName);

    Student *found = searchStudentByName(students, searchName);
    if (found == nullptr)
    {
        std::cout << "Student \"" << searchName << "\" not found.\n";
        return;
    }

    std::cout << "\nFound Student: " << found->name << " (ID: " << found->studentID << ")\n";
    std::cout << "1. Update Name/ID\n";
    std::cout << "2. Re-enter Course Scores\n";
    int choice = getValidatedInt("Choose update option (1-2): ", 1, 2);

    if (choice == 1)
    {
        std::cout << "Enter new Name: ";
        std::getline(std::cin, found->name);
    }
    else if (choice == 2)
    {
        found->courses.clear();
        int numCourses = getValidatedInt("Enter new number of courses (1-10): ", 1, 10);
        for (int i = 0; i < numCourses; ++i)
        {
            Course c;
            std::cout << "\nCourse " << (i + 1) << " Name: ";
            std::getline(std::cin, c.subjectName);
            c.score = getValidatedDouble("Enter score (0 - 100): ", 0.0, 100.0);
            c.credits = getValidatedInt("Enter course credits (1 - 5): ", 1, 5);
            found->courses.push_back(c);
        }
        computeStudentMetrics(*found);
    }
    saveToFile(students, filename); // Auto-save on change
    std::cout << "\nStudent record successfully updated and saved!\n";
}

// Option 4: Delete Student Record
void deleteStudentRecord(std::vector<Student> &students, const std::string &filename)
{
    if (students.empty())
    {
        std::cout << "\nNo student records available to delete.\n";
        return;
    }

    std::string searchName;
    std::cout << "\nEnter name of student to delete: ";
    std::getline(std::cin, searchName);

    auto it = std::remove_if(students.begin(), students.end(), [&searchName](const Student &s)
                             { return s.name == searchName; });

    if (it != students.end())
    {
        students.erase(it, students.end());
        saveToFile(students, filename); // Auto-save on change
        std::cout << "\nStudent record successfully deleted and saved!\n";
    }
    else
    {
        std::cout << "\nStudent \"" << searchName << "\" not found.\n";
    }
}

// Option 5: View Class Analytics Dashboard
void viewClassAnalytics(const std::vector<Student> &students)
{
    if (students.empty())
    {
        std::cout << "\nNo student records available for analytics.\n";
        return;
    }

    int passing = countPassingStudents(students, 60.0);
    int failing = countFailingStudents(students, 60.0);

    std::cout << "\n========================================\n";
    std::cout << "      CLASS ANALYTICS DASHBOARD         \n";
    std::cout << "========================================\n";
    std::cout << " Total Students     : " << students.size() << "\n";
    std::cout << " Class Average GPA  : " << std::fixed << std::setprecision(2) << calculateClassAverage(students) << "\n";
    std::cout << " Highest GPA        : " << std::fixed << std::setprecision(2) << getHighestScore(students) << "\n";
    std::cout << " Lowest GPA         : " << std::fixed << std::setprecision(2) << getLowestScore(students) << "\n";
    std::cout << " Passing Students   : " << passing << "\n";
    std::cout << " Failing Students   : " << failing << "\n";
    std::cout << "========================================\n";
}

// Main Interactive Menu Loop (Strictly 5 Options)
void runApplicationMenu(std::vector<Student> &students, const std::string &filename)
{
    int choice = 0;
    do
    {
        std::cout << "========================================\n";
        std::cout << "      STUDENT GRADE CALCULATOR          \n";
        std::cout << "========================================\n";
        std::cout << " 1. Register New Student Record\n";
        std::cout << " 2. Retrieve Student Transcript\n";
        std::cout << " 3. Modify Student Information\n";
        std::cout << " 4. Remove Student Record\n";
        std::cout << " 5. Generate Performance Analytics\n";
        std::cout << "----------------------------------------\n";

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