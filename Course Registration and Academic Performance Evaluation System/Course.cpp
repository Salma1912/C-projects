#include "Course.h"
Course::Course() : name(""), code(""), student_level(0), credit_hour(0) {}

Course::Course(string n, int level, int hours)
{
    name = n;
    student_level = level;
    credit_hour = hours;
}

ostream& operator<<(ostream& os, const Course& obj)
{
    os << "Course Code: " << obj.code << "\n"
       << "Name: " << obj.name << "\n"
       << "Credit Hours: " << obj.credit_hour << "\n"
       << "Student Level: " << obj.student_level << "\n";
    return os;
}

string Course::getname() const
{
    return name;
}

string Course::getcode() const
{
    return code;
}

int Course::gethours() const
{
    return credit_hour;
}

int Course::get_minstudent_level() const
{
    return student_level;
}