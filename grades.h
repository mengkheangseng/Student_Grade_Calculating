#ifndef GRADES_H
#define GRADES_H

#include "student.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

// ============================================================================
// 1. GRADE & AVERAGE CALCULATION ENGINE
// ============================================================================

/**
 * Calculates the arithmetic mean (average) from a list of numerical marks/scores.
 *
 * @param marks Vector of double score values.
 * @return double The arithmetic average, or 0.0 if marks is empty.
 */
double calculateAverage(const std::vector<double>& marks);

/**
 * Calculates the average percentage score across all courses for a student.
 *
 * @param student The student record.
 * @return double The average score, or 0.0 if no courses are present.
 */
double calculateStudentAverage(const Student& student);

/**
 * Translates a numerical average/score (0 - 100) into a letter grade:
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
 *
 * @param score Numerical percentage score.
 * @return std::string The corresponding letter grade.
 */
std::string calculateLetterGrade(double score);

/**
 * Maps a numerical percentage score to official 4.0 scale GPA quality points.
 *
 * @param score Numerical percentage score.
 * @return double Quality points (0.00 to 4.00).
 */
double scoreToGradePoint(double score);

/**
 * Returns descriptive remarks for a given letter grade.
 *
 * @param letterGrade The letter grade string.
 * @return std::string Official description / remarks.
 */
std::string getGradeRemarks(const std::string& letterGrade);

/**
 * Computes all grading metrics for a student:
 * - Updates course-level letter grades and quality points.
 * - Computes total credits attempted and total credits earned.
 * - Computes credit-weighted cumulative GPA.
 * - Sets the student's overall academic standing.
 *
 * @param student Reference to the student record to update.
 */
void computeStudentMetrics(Student& student);

// ============================================================================
// 2. CLASS ANALYTICS DASHBOARD
// ============================================================================

/**
 * Calculates the overall class average cumulative GPA across all enrolled students.
 *
 * @param students Collection of enrolled students.
 * @return double Average cumulative GPA of the class, or 0.0 if empty.
 */
double calculateClassAverage(const std::vector<Student>& students);

/**
 * Finds and returns the highest cumulative GPA among enrolled students.
 *
 * @param students Collection of enrolled students.
 * @return double The highest cumulative GPA found, or 0.0 if empty.
 */
double getHighestScore(const std::vector<Student>& students);

/**
 * Finds and returns the lowest cumulative GPA among enrolled students.
 *
 * @param students Collection of enrolled students.
 * @return double The lowest cumulative GPA found, or 0.0 if empty.
 */
double getLowestScore(const std::vector<Student>& students);

/**
 * Counts the total number of students meeting or exceeding the passing threshold.
 *
 * @param students Collection of enrolled students.
 * @param passingThreshold Minimum average score percentage required to pass (default: 60.0).
 * @return int Total number of passing students.
 */
int countPassingStudents(const std::vector<Student>& students, double passingThreshold = 60.0);

/**
 * Counts the total number of students failing to meet the passing threshold.
 *
 * @param students Collection of enrolled students.
 * @param passingThreshold Minimum average score percentage required to pass (default: 60.0).
 * @return int Total number of failing students.
 */
int countFailingStudents(const std::vector<Student>& students, double passingThreshold = 60.0);

/**
 * Displays a complete analytics dashboard summary to the console.
 *
 * @param students Collection of enrolled students.
 */
void displayClassAnalytics(const std::vector<Student>& students);

// ============================================================================
// 3. FORMATTED REPORT GENERATOR
// ============================================================================

/**
 * Formats and prints a detailed individual student report card with
 * course-by-course breakdown, total credits, GPA, and standing.
 *
 * @param student The student record to print.
 */
void printIndividualReportCard(const Student& student);

/**
 * Formats and prints a neatly aligned class roster table showing all students,
 * total enrolled courses, credits, average scores, GPAs, letter grades, and standings.
 *
 * @param students Collection of enrolled students.
 */
void printClassRosterTable(const std::vector<Student>& students);

#endif // GRADES_H
