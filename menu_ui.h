#ifndef MENU_UI_H
#define MENU_UI_H

#include "student.h"
#include <vector>
#include <string>

// Input Validation Helpers
int getValidatedInt(const std::string& prompt, int minVal, int maxVal);
double getValidatedDouble(const std::string& prompt, double minVal, double maxVal);

// Record Modification Functions
void addNewStudent(std::vector<Student>& students);
void updateStudentRecord(std::vector<Student>& students);
void deleteStudentRecord(std::vector<Student>& students);

// Main Interactive Menu Loop
void runApplicationMenu(std::vector<Student>& students, const std::string& filename);

#endif