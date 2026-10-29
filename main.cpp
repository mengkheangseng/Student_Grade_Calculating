#include <vector>
#include <string>
#include "student.h"
#include "menu_ui.h"

// Forward declaration for file loading function (from Member 1's file I/O module)
void loadFromFile(std::vector<Student> &students, const std::string &filename);

int main()
{
    std::vector<Student> students;
    std::string filename = "students.txt"; // Database text file

    // 1. Load existing records automatically at startup
    loadFromFile(students, filename);

    // 2. Run the 5-option interactive menu system
    runApplicationMenu(students, filename);

    return 0;
}


//g++ main.cpp menu_ui.cpp grades.cpp file_io.cpp search_sort.cpp -o student_calculator