#include "student.h"
#include "course.h"

Student::Student(string name)
{
    this->name = name;
}

void Student::enroll(Course *course)
{
    enrolledCourses.push_back(course);
    course->addStudent(this);
}

void Student::printCourses()
{
    cout << name << " is enrolled in:\n";
    for (auto course : enrolledCourses)
    {
        cout << "- " << course->getName() << endl;
    }
}

string Student::getName()
{
    return name;
}
