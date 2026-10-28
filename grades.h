#ifndef GRADES_H
#define GRADES_H

#include <string>
#include <vector>
#include "student.h"

// ============================================================================
// CONSTANTS
// ============================================================================
// Maximum number of subjects allowed per student
const int MAX_SUBJECTS = 20;

// Maximum number of students supported for fixed-size student arrays
const int MAX_STUDENTS = 50;

// Valid score boundaries
const double MIN_SCORE = 0.0;
const double MAX_SCORE = 100.0;

// ============================================================================
// CORE GRADING & GPA FUNCTION PROTOTYPES
// ============================================================================

/**
 * Converts a numeric percentage score (0 - 100) into an official letter grade:
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
std::string calculateLetterGrade(double score);

/**
 * Converts a numeric score to official GPA Quality Points:
 *   A  -> 4.00, A- -> 3.67, B+ -> 3.33, B  -> 3.00, B- -> 2.67
 *   C+ -> 2.33, C  -> 2.00, C- -> 1.67, D+ -> 1.33, D  -> 1.00
 *   D- -> 0.67, F  -> 0.00
 */
double scoreToGradePoint(double score);

/**
 * Returns the institutional achievement description for a letter grade.
 * E.g., "A" -> "Outstanding attainment of course goals"
 */
std::string getGradeDescription(const std::string &letterGrade);

/**
 * Computes Cumulative GPA using credit-weighted quality points:
 *   GPA = Sum(Quality Points_i * Credit_i) / Sum(Credit_i)
 */
double calculateGPA(const double scores[], const int credits[], int numSubjects);

/**
 * Calculates total credit hours attempted.
 */
int calculateTotalCredits(const int credits[], int numSubjects);

/**
 * Calculates total credits earned (passing subjects: score >= 60.00%).
 */
int calculateEarnedCredits(const double scores[], const int credits[], int numSubjects);

/**
 * Prompts user interactively for subject credit hours and scores with validation.
 */
void inputSubjectData(double scores[], int credits[], int &numSubjects, int maxSubjects = MAX_SUBJECTS);

// ============================================================================
// SINGLE STUDENT REPORT CARD PROTOTYPES
// ============================================================================

/**
 * Displays an individual student report card with full subject breakdown.
 */
void printReportCard(const double scores[], const int credits[], int numSubjects, 
                     const std::string &studentName = "", const std::string &studentID = "");

/**
 * Overloaded version to print a report card directly from a Student struct.
 */
void printReportCard(const Student &s);

// ============================================================================
// WHOLE CLASS / ALL STUDENTS OUTPUT PROTOTYPES
// ============================================================================

/**
 * Displays a master summary table of ALL students in the class.
 * Includes:
 *   - Table of all students: ID, Name, Average Score, Letter Grade, GPA, and Academic Status
 *   - Class statistics: Total students, Class Average Score, Class Average GPA,
 *     Passing vs Failing counts/rates, Highest Performer, and Lowest Performer.
 *
 * @param students Fixed-size array of Student objects.
 * @param studentCount The number of students in the array.
 */
void displayAllStudents(const Student students[], int studentCount);

/**
 * Overloaded version for std::vector<Student> (integrates directly with Member 1's file_io).
 *
 * @param students Vector of Student objects.
 */
void displayAllStudents(const std::vector<Student> &students);

/**
 * Displays full individual report cards for every student in the collection sequentially.
 *
 * @param students Fixed-size array of Student objects.
 * @param studentCount The number of students in the array.
 */
void printAllReportCards(const Student students[], int studentCount);

/**
 * Overloaded version of batch report cards for std::vector<Student>.
 *
 * @param students Vector of Student objects.
 */
void printAllReportCards(const std::vector<Student> &students);

#endif // GRADES_H
