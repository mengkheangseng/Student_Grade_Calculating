#include "student.h"
#include <vector>
#include <string>
#include <algorithm>

// 1. Search for a student by name (returns pointer to student, or nullptr if not found)
Student *searchStudentByName(std::vector<Student> &students, const string &searchName)
{
    for (auto &s : students)
    {
        if (s.name == searchName)
        {
            return &s; // Return memory address of the matching student
        }
    }
    return nullptr; // Not found
}

// 2. Sort students by highest-to-lowest cumulative GPA (for rankings)
void sortByHighestGPA(std::vector<Student> &students)
{
    sort(students.begin(), students.end(), [](const Student &a, const Student &b)
              {
                  return a.cumulativeGPA > b.cumulativeGPA; // Descending order (highest GPA first)
              });
}

// lambda function: function without name. [](const Student &a, const Student &b) {return a.cumulativeGPA > b.cumulativeGPA;}

// In Student *searchStudentByName(...), the asterisk (*) means that the function returns a pointer to a Student object rather than a copy of the object itself.