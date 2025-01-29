#ifndef TEACHER_H
#define TEACHER_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Course;

class Teacher
{
private:
    string name;
    vector<Course *> teachingCourses;

public:
    Teacher(string name);
    void assignCourse(Course *course);
    void printCourses();
    string getName();
};

#endif
