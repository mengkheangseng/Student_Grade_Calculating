#include "student.h"
#include "menu_ui.h"
#include "grades.h"
#include <vector>
#include <string>
using namespace std;

int main()
{
    vector<Student> students;
    const string filename = "students_records.txt";

    // 1. Automatically load existing records from file on startup
    loadFromFile(students, filename);

    // 2. Launch the team's interactive 9-option menu loop
    runApplicationMenu(students, filename);

    return 0;
}