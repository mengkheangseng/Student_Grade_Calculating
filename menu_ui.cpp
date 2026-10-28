#include "menu_ui.h"
#include "student.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>

// Forward declarations for functions from Member 1 and Member 3
void saveToFile(const std::vector<Student>& students, const std::string& filename);
Student* searchStudentByName(std::vector<Student>& students, const std::string& searchName);
void sortByHighestGPA(std::vector<Student>& students);
void computeStudentMetrics(Student& student);
void printIndividualReportCard(const Student& student);
void printClassRosterTable(const std::vector<Student>& students);
double calculateClassAverage(const std::vector<Student>& students);
double getHighestScore(const std::vector<Student>& students);
double getLowestScore(const std::vector<Student>& students);
int countPassingStudents(const std::vector<Student>& students, double passingThreshold);
int countFailingStudents(const std::vector<Student>& students, double passingThreshold);

// Robust integer input validator (prevents crashes from letters or out-of-range choices)
int getValidatedInt(const std::string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= minVal && value <= maxVal) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        }
        std::cout << "Invalid input. Please enter a number between " << minVal << " and " << maxVal << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Robust double input validator (for scores and marks between 0 and 100)
double getValidatedDouble(const std::string& prompt, double minVal, double maxVal) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= minVal && value <= maxVal) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        }
        std::cout << "Invalid input. Please enter a value between " << minVal << " and " << maxVal << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Add a new student record along with courses and scores
void addNewStudent(std::vector<Student>& students) {
    Student newStudent;
    std::cout << "\n--- ADD NEW STUDENT ---\n";
    std::cout << "Enter Student ID: ";
    std::getline(std::cin, newStudent.studentID);
    
    std::cout << "Enter Student Name: ";
    std::getline(std::cin, newStudent.name);

    int numCourses = getValidatedInt("Enter number of courses for this student (1-10): ", 1, 10);
    
    for (int i = 0; i < numCourses; ++i) {
        Course c;
        std::cout << "\nCourse " << (i + 1) << " Name: ";
        std::getline(std::cin, c.subjectName);

        c.score = getValidatedDouble("Enter score (0 - 100): ", 0.0, 100.0);
        c.credits = getValidatedInt("Enter course credits (1 - 5): ", 1, 5);
        
        newStudent.courses.push_back(c);
    }

    // Compute grades and cumulative GPA using Member 3's engine
    computeStudentMetrics(newStudent);
    students.push_back(newStudent);
    std::cout << "\nStudent successfully added and metrics computed!\n";
}

// Update an existing student's record
void updateStudentRecord(std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "\nNo student records available to update.\n";
        return;
    }

    std::string searchName;
    std::cout << "\nEnter name of student to update: ";
    std::getline(std::cin, searchName);

    Student* found = searchStudentByName(students, searchName);
    if (found == nullptr) {
        std::cout << "Student \"" << searchName << "\" not found.\n";
        return;
    }

    std::cout << "\nFound Student: " << found->name << " (ID: " << found->studentID << ")\n";
    std::cout << "1. Update Name/ID\n";
    std::cout << "2. Re-enter Course Scores\n";
    int choice = getValidatedInt("Choose update option (1-2): ", 1, 2);

    if (choice == 1) {
        std::cout << "Enter new name (current: " << found->name << "): ";
        std::getline(std::cin, found->name);
    } else if (choice == 2) {
        found->courses.clear();
        int numCourses = getValidatedInt("Enter new number of courses (1-10): ", 1, 10);
        for (int i = 0; i < numCourses; ++i) {
            Course c;
            std::cout << "\nCourse " << (i + 1) << " Name: ";
            std::getline(std::cin, c.subjectName);
            c.score = getValidatedDouble("Enter score (0 - 100): ", 0.0, 100.0);
            c.credits = getValidatedInt("Enter course credits (1 - 5): ", 1, 5);
            found->courses.push_back(c);
        }
        computeStudentMetrics(*found);
    }
    std::cout << "\nStudent record successfully updated!\n";
}

// Delete an existing student entry from the vector
void deleteStudentRecord(std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "\nNo student records available to delete.\n";
        return;
    }

    std::string searchName;
    std::cout << "\nEnter name of student to delete: ";
    std::getline(std::cin, searchName);

    auto it = std::remove_if(students.begin(), students.end(), [&searchName](const Student& s) {
        return s.name == searchName;
    });

    if (it != students.end()) {
        students.erase(it, students.end());
        std::cout << "\nStudent record successfully deleted.\n";
    } else {
        std::cout << "\nStudent \"" << searchName << "\" not found.\n";
    }
}

// Main Interactive Menu Loop
void runApplicationMenu(std::vector<Student>& students, const std::string& filename) {
    int choice = 0;
    do {
        std::cout << "\n========================================\n";
        std::cout << "      STUDENT REPORT CARD SYSTEM        \n";
        std::cout << "========================================\n";
        std::cout << "1. Add New Student Record\n";
        std::cout << "2. View Class Roster Summary\n";
        std::cout << "3. Search & View Individual Report Card\n";
        std::cout << "4. Update Student Record\n";
        std::cout << "5. Delete Student Record\n";
        std::cout << "6. Rank Students by Highest GPA\n";
        std::cout << "7. View Class Analytics Dashboard\n";
        std::cout << "8. Save Data to File\n";
        std::cout << "9. Exit Program\n";
        
        choice = getValidatedInt("Enter your choice (1-9): ", 1, 9);

        switch (choice) {
            case 1:
                addNewStudent(students);
                break;
            case 2:
                if (students.empty()) {
                    std::cout << "\nNo student records found.\n";
                } else {
                    printClassRosterTable(students);
                }
                break;
            case 3: {
                std::string searchName;
                std::cout << "\nEnter student name to search: ";
                std::getline(std::cin, searchName);
                Student* found = searchStudentByName(students, searchName);
                if (found != nullptr) {
                    printIndividualReportCard(*found);
                } else {
                    std::cout << "\nStudent \"" << searchName << "\" not found.\n";
                }
                break;
            }
            case 4:
                updateStudentRecord(students);
                break;
            case 5:
                deleteStudentRecord(students);
                break;
            case 6:
                if (students.empty()) {
                    std::cout << "\nNo student records to sort.\n";
                } else {
                    sortByHighestGPA(students);
                    std::cout << "\nStudents ranked by highest GPA:\n";
                    printClassRosterTable(students);
                }
                break;
            case 7: {
                if (students.empty()) {
                    std::cout << "\nNo student records available for analytics.\n";
                    break;
                }
                std::cout << "\n========================================\n";
                std::cout << "      CLASS ANALYTICS DASHBOARD         \n";
                std::cout << "========================================\n";
                std::cout << "Total Students     : " << students.size() << "\n";
                std::cout << "Class Average GPA  : " << std::fixed << std::setprecision(2) << calculateClassAverage(students) << "\n";
                std::cout << "Highest GPA        : " << std::fixed << std::setprecision(2) << getHighestScore(students) << "\n";
                std::cout << "Lowest GPA         : " << std::fixed << std::setprecision(2) << getLowestScore(students) << "\n";
                std::cout << "Passing Students   : " << countPassingStudents(students, 50.0) << "\n";
                std::cout << "Failing Students   : " << countFailingStudents(students, 50.0) << "\n";
                std::cout << "========================================\n";
                break;
            }
            case 8:
                saveToFile(students, filename);
                std::cout << "\nData saved successfully.\n";
                break;
            case 9:
                saveToFile(students, filename);
                std::cout << "\nAuto-saved data. Exiting program. Goodbye!\n";
                break;
        }
    } while (choice != 9);
}