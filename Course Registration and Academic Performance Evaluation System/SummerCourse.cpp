#include "SummerCourse.h"

SummerCourse::SummerCourse() : Course() {}

SummerCourse::SummerCourse(string n, int level, int hours) : Course(n, level, hours)
{
    code = n + "_S" + to_string(level);
}