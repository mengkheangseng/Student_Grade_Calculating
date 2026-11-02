#ifndef MENU_UI_H
#define MENU_UI_H

#include "student.h"
#include <vector>
#include <string>

using namespace std;

// Input Validation Helpers
int getValidatedInt(const string& prompt, int minVal, int maxVal);
double getValidatedDouble(const string& prompt, double minVal, double maxVal);

// Record Modification Functions
void addNewStudent(vector<Student>& students);
void updateStudentRecord(vector<Student>& students);
void deleteStudentRecord(vector<Student>& students);

// Main Interactive Menu Loop
void runApplicationMenu(vector<Student>& students, const string& filename);

#endif