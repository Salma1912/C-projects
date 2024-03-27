#ifndef COURSE_H
#define COURSE_H
#include <iostream>
using namespace std;
class Course{
protected:
    string name;
    string code;
    int student_level;
    int credit_hour;
public:
    Course() : name(""), code(""), student_level(0), credit_hour(0) {}
    Course(string n,int level,int hours)
    {
        name=n;
        student_level=level;
        credit_hour=hours;
    }
    friend ostream& operator<<(ostream& os, const Course& obj)
    {
        os
                << "Course Code: " << obj.code << "\n"
                << "Name: " << obj.name << "\n"
                << "Credit Hours: " << obj.credit_hour << "\n"
                << "Student Level: " << obj.student_level << "\n";
        return os;
    }
    string getname() const
    {
        return name;
    }
    string getcode() const
    {
        return code;
    }
    int gethours() const
    {
        return credit_hour;
    }
    int get_minstudent_level()const{
        return student_level;
    }
};
#endif
