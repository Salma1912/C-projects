#ifndef NORMALCOURSE_H
#define NORMALCOURSE_H
#include <iostream>
#include "Course.h"
using namespace std;
class NormalCourse:public Course{
public:
    NormalCourse():Course(){}
    NormalCourse(string n, int level, int hours): Course(n,level,hours)
    {
        code = n + "_N" + to_string(level);
    }
};
#endif
