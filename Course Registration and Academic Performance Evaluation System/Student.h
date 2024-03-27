#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>
#include "Course.h"
using namespace std;
class Student{
protected:
    string name;
    string ID;
    int level;
    double grades[6];
    Course* course_list[6];
    int course_number;

public:
    Student() : level(0), course_number(0)
    {
        for (int i = 0; i < 6; i++)
        {
            grades[i] = 0.0;
            course_list[i] = nullptr;
        }
    }
    void setSname(string n){
        name=n;
    }
    string getSname(){
        return name;
    }
    void setID(string id){
        ID=id;
    }
    string getID(){
        return ID;
    }
    void setlevel(int L)
    {
        level = L;
    }
    int getlevel() const
    {
        return level;
    }
    void setgrades(double g[6])
    {
        for (int i = 0; i < 6; i++)
        {
            grades[i] = g[i];
        }
    }
    double* getGrades()
    {
        return grades;
    }
    void setcourselist(Course* list[6])
    {
        for (int i = 0; i < 6; i++)
        {
            course_list[i] = list[i];
        }
    }
    Course** getcourselist()
    {
        return course_list;
    }
    void setnumcourses(int count)
    {
        course_number = count;
    }
    int getnumCourses() const
    {
        return course_number;
    }
    void printRegisteredCourses() const
    {
        if (course_number == 0)
        {
            cout << "No courses registered." << endl;

        }
        else {
            cout << "Registered Courses:" << endl;
            for (int i = 0; i < course_number; i++) {
                Course *course = course_list[i];
                double grade = grades[i];
                cout << "Course " << i + 1 << ":" << endl;
                cout << "Name: " << course->getname() << endl;
                cout << "Code: " << course->getcode() << endl;
                cout << "Level: " << course->get_minstudent_level() << endl;
                cout << "Credit Hours: " << course->gethours() << endl;
                cout << "Grade: " << grade << endl;
                cout << endl;
            }
        }
    }
    virtual float calculate_Expenses()=0;
    virtual bool Register_Course(Course*course){
        if (course_number<6 && course != nullptr) {
            course_list[course_number]=course;
            course_number++;
            return true;
        }
        else{
            cout<<"The number of registed courses can't exceed 6 courses";
            return false;
        }
    }
    double get_course_gpa(double percent){
        if (percent>=98){
            return 4.00;
        }
        else if(percent>=93){
            return 4.00;
        }
        else if(percent>=90){
            return 3.70;
        }
        else if(percent>=87){
            return 3.30;
        }
        else if(percent>=83){
            return 3.00;
        }
        else if(percent>=80){
            return 2.70;
        }
        else if(percent>=77){
            return 2.30;
        }
        else if(percent>=73){
            return 2.00;
        }
        else if(percent>=70){
            return 1.70;
        }
        else if(percent>=67){
            return 1.30;
        }
        else if(percent>=63){
            return 1.00;
        }
        else if(percent>=60){
            return 0.70;
        }
        else {
            return 0.00;
        }

    }
    double get_total_gpa(){
        double total=0;
        double total_hours=0;
        for(int i=0;i<course_number;i++){
            total+= get_course_gpa((grades[i]))*course_list[i]->gethours();
            total_hours+=course_list[i]->gethours();
        }
        return total /total_hours;
    }


};
#endif //S8_20227020_20227023_20227014_STUDENT_H
