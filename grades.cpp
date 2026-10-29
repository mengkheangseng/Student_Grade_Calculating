#include "grades.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

// ============================================================================
// 1. GRADE & AVERAGE CALCULATION ENGINE
// ============================================================================


/**
 * Calculates the average percentage score across all courses for a student.
 */
double calculateStudentAverage(const Student& student)
{
    if (student.courses.empty())
    {
        return 0.0;
    }

    double totalScore = 0.0;
    for (size_t i = 0; i < student.courses.size(); ++i)
    {
        totalScore += student.courses[i].score;
    }
    return totalScore / static_cast<double>(student.courses.size());
}

/**
 * Maps numerical percentage score to official institutional letter grades:
 *   93.00 - 100.00% -> "A"
 *   90.00 -  92.99% -> "A-"
 *   87.00 -  89.99% -> "B+"
 *   83.00 -  86.99% -> "B"
 *   80.00 -  82.99% -> "B-"
 *   77.00 -  79.99% -> "C+"
 *   73.00 -  76.99% -> "C"
 *   70.00 -  72.99% -> "C-"
 *   67.00 -  69.99% -> "D+"
 *   63.00 -  66.99% -> "D"
 *   60.00 -  62.99% -> "D-"
 *   Below 60.00%    -> "F"
 */
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

std::string getLetterGradeFromGPA(double cumulativeGPA)
{
    if (cumulativeGPA >= 4.00)
        return "A";
    else if (cumulativeGPA >= 3.67)
        return "A-";
    else if (cumulativeGPA >= 3.33)
        return "B+";
    else if (cumulativeGPA >= 3.00)
        return "B";
    else if (cumulativeGPA >= 2.67)
        return "B-";
    else if (cumulativeGPA >= 2.33)
        return "C+";
    else if (cumulativeGPA >= 2.00)
        return "C";
    else if (cumulativeGPA >= 1.67)
        return "C-";
    else if (cumulativeGPA >= 1.33)
        return "D+";
    else if (cumulativeGPA >= 1.00)
        return "D";
    else if (cumulativeGPA >= 0.67)
        return "D-";
    else
        return "F";
}

/**
 * Converts a score to institutional 4.0 scale GPA quality points.
 */
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

/**
 * Returns remarks / descriptions corresponding to the letter grade.
 */
string getGradeRemarks(const string& letterGrade)
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

/**
 * Computes all grading metrics for a student:
 * - Updates course grade and course gpa.
 * - Sums credit hours attempted and earned.
 * - Calculates weighted cumulative GPA: Sum(Credits * QualityPoints) / Sum(Credits).
 * - Assigns academic standing.
 */
void computeStudentMetrics(Student& student)
{
    if (student.courses.empty())
    {
        student.totalCreditsAttempted = 0;
        student.totalCreditsEarned = 0;
        student.cumulativeGPA = 0.0;
        student.academicStanding = "No Courses Enrolled";
        return;
    }

    int totalAttempted = 0;
    int totalEarned = 0;
    double totalQualityPoints = 0.0;

    for (size_t i = 0; i < student.courses.size(); ++i)
    {
        Course& c = student.courses[i];
        c.grade = calculateLetterGrade(c.score);
        c.gpa = scoreToGradePoint(c.score);

        totalAttempted += c.credits;
        if (c.score >= 60.0) // Passing score threshold (D- or higher) earns credit
        {
            totalEarned += c.credits;
        }

        totalQualityPoints += (c.gpa * c.credits);
    }

    student.totalCreditsAttempted = totalAttempted;
    student.totalCreditsEarned = totalEarned;

    if (totalAttempted > 0)
    {
        student.cumulativeGPA = totalQualityPoints / static_cast<double>(totalAttempted);
    }
    else
    {
        student.cumulativeGPA = 0.0;
    }

    // Assign overall academic standing based on collegiate GPA benchmarks
    if (student.cumulativeGPA >= 3.67)
    {
        student.academicStanding = "Dean's Honor List";
    }
    else if (student.cumulativeGPA >= 3.00)
    {
        student.academicStanding = "Good Standing";
    }
    else if (student.cumulativeGPA >= 2.00)
    {
        student.academicStanding = "Satisfactory";
    }
    else
    {
        student.academicStanding = "Academic Probation";
    }
}

// ============================================================================
// 2. CLASS ANALYTICS DASHBOARD
// ============================================================================

/**
 * Calculates the overall class average cumulative GPA across all students.
 */
double calculateClassAverage(const vector<Student>& students)
{
    if (students.empty())
    {
        return 0.0;
    }

    double sumGPA = 0.0;
    for (size_t i = 0; i < students.size(); ++i)
    {
        sumGPA += students[i].cumulativeGPA;
    }
    return sumGPA / static_cast<double>(students.size());
}

/**
 * Finds and returns the highest cumulative GPA among all students.
 */
double getHighestScore(const vector<Student>& students)
{
    if (students.empty())
    {
        return 0.0;
    }

    double maxVal = students[0].cumulativeGPA;
    for (size_t i = 1; i < students.size(); ++i)
    {
        if (students[i].cumulativeGPA > maxVal)
        {
            maxVal = students[i].cumulativeGPA;
        }
    }
    return maxVal;
}

/**
 * Finds and returns the lowest cumulative GPA among all students.
 */
double getLowestScore(const vector<Student>& students)
{
    if (students.empty())
    {
        return 0.0;
    }

    double minVal = students[0].cumulativeGPA;
    for (size_t i = 1; i < students.size(); ++i)
    {
        if (students[i].cumulativeGPA < minVal)
        {
            minVal = students[i].cumulativeGPA;
        }
    }
    return minVal;
}

/**
 * Counts students meeting or exceeding the passing threshold.
 * Uses the student's average percentage score across courses (or cumulative GPA if courses are empty).
 */
int countPassingStudents(const vector<Student>& students, double passingThreshold)
{
    int passingCount = 0;
    for (size_t i = 0; i < students.size(); ++i)
    {
        double avg = calculateStudentAverage(students[i]);
        if (students[i].courses.empty())
        {
            if (students[i].cumulativeGPA >= 2.0)
            {
                passingCount++;
            }
        }
        else if (avg >= passingThreshold)
        {
            passingCount++;
        }
    }
    return passingCount;
}

/**
 * Counts students failing to meet the passing threshold.
 */
int countFailingStudents(const vector<Student>& students, double passingThreshold)
{
    return static_cast<int>(students.size()) - countPassingStudents(students, passingThreshold);
}

/**
 * Displays the complete class analytics dashboard.
 */
void displayClassAnalytics(const vector<Student>& students)
{
    cout << "\n========================================\n";
    cout << "      CLASS ANALYTICS DASHBOARD         \n";
    cout << "========================================\n";
    
    if (students.empty())
    {
        cout << "No student records available for analytics.\n";
        cout << "========================================\n";
        return;
    }

    int passingCount = countPassingStudents(students, 60.0);
    int failingCount = countFailingStudents(students, 60.0);
    double passRate = (static_cast<double>(passingCount) / students.size()) * 100.0;

    cout << "Total Students     : " << students.size() << "\n";
    cout << "Class Average GPA  : " << fixed << setprecision(2) << calculateClassAverage(students) << "\n";
    cout << "Highest GPA        : " << fixed << setprecision(2) << getHighestScore(students) << "\n";
    cout << "Lowest GPA         : " << fixed << setprecision(2) << getLowestScore(students) << "\n";
    cout << "Passing Students   : " << passingCount << " (" << fixed << setprecision(1) << passRate << "%)\n";
    cout << "Failing Students   : " << failingCount << " (" << fixed << setprecision(1) << (100.0 - passRate) << "%)\n";
    cout << "========================================\n";
}

// ============================================================================
// 3. FORMATTED REPORT GENERATOR
// ============================================================================

/**
 * Formats and prints an individual student report card using <iomanip>.
 */
void printIndividualReportCard(const Student& student)
{
    cout << "\n========================================================================\n";
    cout << "                         STUDENT REPORT CARD                            \n";
    cout << "========================================================================\n";
    cout << " Student ID : " << student.studentID << "\n";
    cout << " Name       : " << student.name << "\n";
    cout << "------------------------------------------------------------------------\n";

    if (student.courses.empty())
    {
        cout << " No course enrollment records found for this student.\n";
        cout << "========================================================================\n";
        return;
    }

    // Table Header
    cout << left  << setw(24) << " Course Name"
         << right << setw(12) << "Score (/100)"
         << setw(10) << "Credits"
         << setw(10) << "Grade"
         << setw(14) << "GPA" << "\n";
    cout << "------------------------------------------------------------------------\n";

    // Course Rows
    for (size_t i = 0; i < student.courses.size(); ++i)
    {
        const Course& c = student.courses[i];
        cout << " " << left  << setw(23) << c.subjectName
             << right << setw(10) << fixed << setprecision(2) << c.score
             << setw(10) << c.credits
             << setw(10) << c.grade
             << setw(14) << fixed << setprecision(2) << c.gpa << "\n";
    }

    cout << "------------------------------------------------------------------------\n";
    cout << " Total Credits Attempted : " << student.totalCreditsAttempted << "\n";
    cout << " Total Credits Earned    : " << student.totalCreditsEarned << "\n";
    cout << " Cumulative GPA          : " << fixed << setprecision(2) << student.cumulativeGPA << " / 4.00\n";
    cout << " Academic Standing       : " << student.academicStanding << "\n";
    cout << " Remarks                 : \"" << getLetterGradeFromGPA(student.cumulativeGPA) << "\" " << getGradeRemarks(getLetterGradeFromGPA(student.cumulativeGPA)) << "\n";
    cout << "========================================================================\n";
}

/**
 * Formats and prints a neatly aligned class roster summary table using <iomanip>.
 */
void printClassRosterTable(const vector<Student>& students)
{
    cout << "\n==============================================================================================================\n";
    cout << "                                           CLASS ROSTER SUMMARY                                               \n";
    cout << "==============================================================================================================\n";

    if (students.empty())
    {
        cout << " No student records available to display.\n";
        cout << "==============================================================================================================\n";
        return;
    }

    // Table Header
    cout << left  << setw(12) << " Student ID"
         << left  << setw(24) << "Student Name"
         << right << setw(9)  << "Courses"
         << setw(11) << "Attempted"
         << setw(9)  << "Earned"
         << setw(13) << "Avg Score"
         << setw(12) << "Cumul GPA"
         << setw(9)  << "Grade"
         << "   " << left << setw(20) << "Standing" << "\n";
    cout << "--------------------------------------------------------------------------------------------------------------\n";

    // Table Rows
    for (size_t i = 0; i < students.size(); ++i)
    {
        const Student& s = students[i];
        double avgScore = calculateStudentAverage(s);
        string grade = calculateLetterGrade(avgScore);

        cout << " " << left  << setw(11) << s.studentID
             << left  << setw(24) << s.name
             << right << setw(7)  << s.courses.size()
             << setw(11) << s.totalCreditsAttempted
             << setw(9)  << s.totalCreditsEarned
             << setw(11) << fixed << setprecision(2) << avgScore << "%"
             << setw(11) << fixed << setprecision(2) << s.cumulativeGPA
             << setw(8)  << grade
             << "   " << left << setw(20) << s.academicStanding << "\n";
    }

    cout << "==============================================================================================================\n";
}
