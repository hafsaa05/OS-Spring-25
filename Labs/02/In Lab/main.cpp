#include "student.h"
#include "teacher.h"
#include "course.h"

int main()
{
    Course math("Probability");
    Course physics("Applied Physics");

    Student s1("Amna");
    Student s2("Hafsa");

    Teacher t1("Ms Khadija");
    Teacher t2("Ms Saeeda");

    s1.enroll(&math);
    s2.enroll(&physics);
    s1.enroll(&physics);

    t1.assignCourse(&math);
    t2.assignCourse(&physics);

    s1.printCourses();
    s2.printCourses();

    t1.printCourses();
    t2.printCourses();

    math.printInfo();
    physics.printInfo();

    return 0;
}
