#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Course;

class Student
{
private:
    string name;
    vector<Course *> enrolledCourses;

public:
    Student(string name);
    void enroll(Course *course);
    void printCourses();
    string getName();
};

#endif
