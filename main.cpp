#include <vector>
#include <string>
#include "student.h"
#include "menu_ui.h"

using namespace std;

// Forward declaration for file loading function (from Member 1's file I/O module)
void loadFromFile(vector<Student> &students, const string &filename);

int main()
{
    vector<Student> students;
    string filename = "students.txt"; // Database text file

    // 1. Load existing records automatically at startup
    loadFromFile(students, filename);

    // 2. Run the 5-option interactive menu system
    runApplicationMenu(students, filename);

    return 0;
}


//g++ main.cpp menu_ui.cpp grades.cpp file_io.cpp search_sort.cpp -o student_calculator