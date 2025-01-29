#include "course.h"

Course::Course(string name)
{
    courseName = name;
}

void Course::addStudent(Student *student)
{
    students.push_back(student);
}

void Course::addTeacher(Teacher *teacher)
{
    teachers.push_back(teacher);
}

void Course::printInfo()
{
    cout << "Course: " << courseName << "\nStudents:\n";
    for (auto student : students)
    {
        cout << "- " << student->getName() << endl;
    }

    cout << "Teachers:\n";
    for (auto teacher : teachers)
    {
        cout << "- " << teacher->getName() << endl;
    }
}

string Course::getName()
{
    return courseName;
}
