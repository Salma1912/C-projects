#include "NormalCourse.h"

NormalCourse::NormalCourse() : Course() {}

NormalCourse::NormalCourse(string n, int level, int hours) : Course(n, level, hours)
{
    code = n + "_N" + to_string(level);
}