#ifndef SPECIAL_STUDENT_H
#define SPECIAL_STUDENT_H
#include <iostream>
#include "Course.h"
#include "Student.h"
using namespace std;
class Special_student: public Student{
public:
    Special_student(): Student(){

    }
    bool Register_Course(Course*course){
        if(course_number<6 && course != nullptr){

            course_list[course_number]=course;
            course_number++;
            return true;
        }
        else{
            return false;
        }
    }
    float calculate_Expenses() {
        int total_hours = 0;
        for (int i = 0; i < course_number; ++i) {
            total_hours += course_list[i]->gethours();
        }
        return total_hours * 500.0;
    }

};
#endif
