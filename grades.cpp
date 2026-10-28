#include "grades.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

// ============================================================================
// HELPER FUNCTIONS (Internal Linkage)
// ============================================================================
// Clears erroneous input flags and flushes leftover characters from cin stream.
static void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Computes the GPA of a Student struct instance.
// If the student has marks in s.marks, calculates the GPA across individual marks.
// If s.marks is empty, converts s.averageScore to GPA quality points.
static double getStudentGPA(const Student &s)
{
    if (!s.marks.empty())
    {
        double totalQP = 0.0;
        for (size_t i = 0; i < s.marks.size(); ++i)
        {
            totalQP += scoreToGradePoint(s.marks[i]);
        }
        return totalQP / static_cast<double>(s.marks.size());
    }
    return scoreToGradePoint(s.averageScore);
}

// ============================================================================
// CORE GRADING & GPA IMPLEMENTATIONS
// ============================================================================

string calculateLetterGrade(double score)
{
    if (score >= 93.0)      return "A";
    else if (score >= 90.0) return "A-";
    else if (score >= 87.0) return "B+";
    else if (score >= 83.0) return "B";
    else if (score >= 80.0) return "B-";
    else if (score >= 77.0) return "C+";
    else if (score >= 73.0) return "C";
    else if (score >= 70.0) return "C-";
    else if (score >= 67.0) return "D+";
    else if (score >= 63.0) return "D";
    else if (score >= 60.0) return "D-";
    else                    return "F";
}

double scoreToGradePoint(double score)
{
    string grade = calculateLetterGrade(score);

    if (grade == "A")       return 4.00;
    else if (grade == "A-") return 3.67;
    else if (grade == "B+") return 3.33;
    else if (grade == "B")  return 3.00;
    else if (grade == "B-") return 2.67;
    else if (grade == "C+") return 2.33;
    else if (grade == "C")  return 2.00;
    else if (grade == "C-") return 1.67;
    else if (grade == "D+") return 1.33;
    else if (grade == "D")  return 1.00;
    else if (grade == "D-") return 0.67;
    else                    return 0.00; // "F"
}

string getGradeDescription(const string &letterGrade)
{
    if (letterGrade == "A")       return "Outstanding attainment of course goals";
    else if (letterGrade == "A-") return "Superior attainment of course goals";
    else if (letterGrade == "B+") return "Very good attainment of course goals";
    else if (letterGrade == "B")  return "Good attainment of course goals";
    else if (letterGrade == "B-") return "Well above avg attainment of course goals";
    else if (letterGrade == "C+") return "Above avg attainment of course goals";
    else if (letterGrade == "C")  return "Average attainment of course goals";
    else if (letterGrade == "C-") return "Below avg attainment of course goals";
    else if (letterGrade == "D+") return "Weak attainment of course goals";
    else if (letterGrade == "D")  return "Poor attainment of course goals";
    else if (letterGrade == "D-") return "Very poor attainment of course goals";
    else                          return "Unsatisfactory attainment of course goals";
}

int calculateTotalCredits(const int credits[], int numSubjects)
{
    int total = 0;
    for (int i = 0; i < numSubjects; ++i)
    {
        total += credits[i];
    }
    return total;
}

int calculateEarnedCredits(const double scores[], const int credits[], int numSubjects)
{
    int earned = 0;
    for (int i = 0; i < numSubjects; ++i)
    {
        if (scores[i] >= 60.0)
        {
            earned += credits[i];
        }
    }
    return earned;
}

double calculateGPA(const double scores[], const int credits[], int numSubjects)
{
    if (numSubjects <= 0)
    {
        return 0.00;
    }

    double totalQualityPoints = 0.0;
    int totalCredits = 0;

    for (int i = 0; i < numSubjects; ++i)
    {
        double qp = scoreToGradePoint(scores[i]);
        totalQualityPoints += (qp * credits[i]);
        totalCredits += credits[i];
    }

    if (totalCredits == 0)
    {
        return 0.00;
    }

    return totalQualityPoints / static_cast<double>(totalCredits);
}

void inputSubjectData(double scores[], int credits[], int &numSubjects, int maxSubjects)
{
    cout << "\n============================================\n";
    cout << "           SUBJECT DATA ENTRY               \n";
    cout << "============================================\n";

    while (true)
    {
        cout << "Enter the number of subjects (1 - " << maxSubjects << "): ";
        if (cin >> numSubjects && numSubjects >= 1 && numSubjects <= maxSubjects)
        {
            break;
        }

        cout << "[!] Invalid number. Please enter an integer between 1 and " 
             << maxSubjects << ".\n";
        clearInputBuffer();
    }

    cout << "\n--- Enter Details for Each Subject ---\n";

    for (int i = 0; i < numSubjects; ++i)
    {
        cout << "\n[Subject " << (i + 1) << " of " << numSubjects << "]\n";

        while (true)
        {
            cout << "  Enter credit hours (e.g., 1, 2, 3, 4): ";
            if (cin >> credits[i] && credits[i] > 0)
            {
                break;
            }

            cout << "  [!] Credit hours must be a positive integer greater than 0.\n";
            clearInputBuffer();
        }

        while (true)
        {
            cout << "  Enter score (0 - 100): ";
            if (cin >> scores[i] && scores[i] >= MIN_SCORE && scores[i] <= MAX_SCORE)
            {
                break;
            }

            cout << "  [!] Score must be a numeric value between 0.0 and 100.0.\n";
            clearInputBuffer();
        }
    }

    cout << "\n[+] All subject records successfully entered!\n";
}

// ============================================================================
// SINGLE STUDENT REPORT CARD IMPLEMENTATION
// ============================================================================

void printReportCard(const double scores[], const int credits[], int numSubjects, 
                     const string &studentName, const string &studentID)
{
    cout << "\n========================================================================\n";
    cout << "                         STUDENT REPORT CARD                            \n";
    cout << "========================================================================\n";

    if (!studentName.empty() || !studentID.empty())
    {
        if (!studentName.empty())
        {
            cout << " Student Name : " << studentName << "\n";
        }
        if (!studentID.empty())
        {
            cout << " Student ID   : " << studentID << "\n";
        }
        cout << "------------------------------------------------------------------------\n";
    }

    if (numSubjects <= 0)
    {
        cout << " No subject data available to display.\n";
        cout << "========================================================================\n";
        return;
    }

    cout << left << setw(12) << " Subject"
         << right << setw(14) << "Score (/100)"
         << setw(10) << "Credits"
         << setw(10) << "Grade"
         << setw(14) << "Quality Pts" << "\n";

    cout << "------------------------------------------------------------------------\n";

    for (int i = 0; i < numSubjects; ++i)
    {
        string grade = calculateLetterGrade(scores[i]);
        double qp = scoreToGradePoint(scores[i]);

        cout << " " << left << setw(11) << ("Subject " + to_string(i + 1))
             << right << setw(12) << fixed << setprecision(2) << scores[i]
             << setw(10) << credits[i]
             << setw(10) << grade
             << setw(14) << fixed << setprecision(2) << qp << "\n";
    }

    int totalAttempted = calculateTotalCredits(credits, numSubjects);
    int totalEarned    = calculateEarnedCredits(scores, credits, numSubjects);
    double gpa         = calculateGPA(scores, credits, numSubjects);

    cout << "------------------------------------------------------------------------\n";
    cout << " Total Credits Attempted : " << totalAttempted << "\n";
    cout << " Total Credits Earned    : " << totalEarned << "\n";
    cout << " Cumulative GPA          : " << fixed << setprecision(2) << gpa << " / 4.00\n";

    cout << " Academic Standing       : ";
    if (gpa >= 3.67)      cout << "Superior / Dean's Honor List\n";
    else if (gpa >= 3.00) cout << "Good Standing\n";
    else if (gpa >= 2.00) cout << "Satisfactory\n";
    else                  cout << "Academic Probation / Warning\n";

    cout << "========================================================================\n";
}

void printReportCard(const Student &s)
{
    if (!s.marks.empty())
    {
        double scores[MAX_SUBJECTS];
        int credits[MAX_SUBJECTS];
        int count = 0;

        for (size_t i = 0; i < s.marks.size() && count < MAX_SUBJECTS; ++i)
        {
            scores[count] = s.marks[i];
            credits[count] = 3; // Standard 3-credit default when individual credits aren't specified
            count++;
        }

        printReportCard(scores, credits, count, s.name, s.studentID);
    }
    else
    {
        // Single summary view when individual marks are not stored in memory
        cout << "\n========================================================================\n";
        cout << "                         STUDENT REPORT CARD                            \n";
        cout << "========================================================================\n";
        cout << " Student Name    : " << s.name << "\n";
        cout << " Student ID      : " << s.studentID << "\n";
        cout << " Average Score   : " << fixed << setprecision(2) << s.averageScore << "%\n";
        
        string grade = s.letterGrade.empty() ? calculateLetterGrade(s.averageScore) : s.letterGrade;
        double gpa = scoreToGradePoint(s.averageScore);

        cout << " Letter Grade    : " << grade << "\n";
        cout << " Cumulative GPA  : " << fixed << setprecision(2) << gpa << " / 4.00\n";
        cout << " Description     : " << getGradeDescription(grade) << "\n";
        cout << " Status          : " << (s.status.empty() ? (s.averageScore >= 60.0 ? "Pass" : "Fail") : s.status) << "\n";
        cout << "========================================================================\n";
    }
}

// ============================================================================
// WHOLE CLASS / ALL STUDENTS OUTPUT IMPLEMENTATIONS
// ============================================================================

void displayAllStudents(const Student students[], int studentCount)
{
    cout << "\n========================================================================================================\n";
    cout << "                                      CLASS GRADE SUMMARY REPORT                                        \n";
    cout << "========================================================================================================\n";

    if (studentCount <= 0)
    {
        cout << " [!] No student records currently enrolled in the system.\n";
        cout << "========================================================================================================\n";
        return;
    }

    // Table Header
    cout << left  << setw(12) << " Student ID"
         << left  << setw(24) << "Student Name"
         << right << setw(12) << "Avg Score"
         << setw(10) << "Grade"
         << setw(14) << "GPA (4.00)"
         << "   " << left << setw(24) << "Academic Standing" << "\n";

    cout << "--------------------------------------------------------------------------------------------------------\n";

    double totalScoreSum = 0.0;
    double totalGpaSum   = 0.0;
    int passCount        = 0;
    int failCount        = 0;

    int topIndex = 0;
    int lowIndex = 0;
    double maxGpa = -1.0;
    double minGpa = 999.0;

    // Iterate through all students in the class
    for (int i = 0; i < studentCount; ++i)
    {
        const Student &s = students[i];

        double score = s.averageScore;
        string grade = s.letterGrade.empty() ? calculateLetterGrade(score) : s.letterGrade;
        double gpa   = getStudentGPA(s);
        string status = s.status.empty() ? (score >= 60.0 ? "Pass" : "Fail") : s.status;

        // Statistics accumulation
        totalScoreSum += score;
        totalGpaSum   += gpa;

        if (score >= 60.0)
        {
            passCount++;
        }
        else
        {
            failCount++;
        }

        if (gpa > maxGpa)
        {
            maxGpa = gpa;
            topIndex = i;
        }

        if (gpa < minGpa)
        {
            minGpa = gpa;
            lowIndex = i;
        }

        // Print student row
        cout << " " << left  << setw(11) << s.studentID
             << left  << setw(24) << s.name
             << right << setw(10) << fixed << setprecision(2) << score << "%"
             << setw(9)  << grade
             << setw(12) << fixed << setprecision(2) << gpa
             << "   " << left << setw(24) << status << "\n";
    }

    // Class Statistics Summary
    double classAvgScore = totalScoreSum / static_cast<double>(studentCount);
    double classAvgGpa   = totalGpaSum   / static_cast<double>(studentCount);
    double passRate      = (static_cast<double>(passCount) / studentCount) * 100.0;

    cout << "--------------------------------------------------------------------------------------------------------\n";
    cout << " Total Students Enrolled : " << studentCount << "\n";
    cout << " Class Average Score     : " << fixed << setprecision(2) << classAvgScore << "%\n";
    cout << " Class Average GPA       : " << fixed << setprecision(2) << classAvgGpa   << " / 4.00\n";
    cout << " Passing Students        : " << passCount << " (" << fixed << setprecision(1) << passRate << "%)\n";
    cout << " Failing Students        : " << failCount << " (" << (100.0 - passRate) << "%)\n";
    cout << " Top Performer           : " << students[topIndex].name << " (GPA: " 
         << fixed << setprecision(2) << maxGpa << ")\n";
    cout << " Lowest Performer        : " << students[lowIndex].name << " (GPA: " 
         << fixed << setprecision(2) << minGpa << ")\n";
    cout << "========================================================================================================\n";
}

void displayAllStudents(const vector<Student> &students)
{
    if (students.empty())
    {
        displayAllStudents(nullptr, 0);
        return;
    }
    displayAllStudents(students.data(), static_cast<int>(students.size()));
}

void printAllReportCards(const Student students[], int studentCount)
{
    for (int i = 0; i < studentCount; ++i)
    {
        printReportCard(students[i]);
    }
}

void printAllReportCards(const vector<Student> &students)
{
    for (size_t i = 0; i < students.size(); ++i)
    {
        printReportCard(students[i]);
    }
}
