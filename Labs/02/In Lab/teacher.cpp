#include "teacher.h"
#include "course.h"

Teacher::Teacher(string name)
{
    this->name = name;
}

void Teacher::assignCourse(Course *course)
{
    teachingCourses.push_back(course);
    course->addTeacher(this);
}

void Teacher::printCourses()
{
    cout << name << " is teaching:\n";
    for (auto course : teachingCourses)
    {
        cout << "- " << course->getName() << endl;
    }
}

string Teacher::getName()
{
    return name;
}
