#ifndef SUMMERCOURSE_H
#define SUMMERCOURSE_H
#include "Course.h"
#include <iostream>
#include "Student.h"
using namespace std;
class SummerCourse:public Course{
public:
    SummerCourse():Course(){}
    SummerCourse(string n, int level, int hours):Course(n,level,hours)
    {
        code = n + "_S" + to_string(level);
    }
};
#endif

