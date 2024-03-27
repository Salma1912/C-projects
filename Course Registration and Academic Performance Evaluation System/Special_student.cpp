#include "Special_student.h"

Special_student::Special_student() : Student() {}

bool Special_student::Register_Course(Course* course)
{
    if (course_number >= 6)
    {
        cout << "Cannot register more than 6 courses." << endl;
        return false;
    }

    course_list[course_number] = course;
    course_number++;

    return true;
}

float Special_student::calculate_Expenses()
{
    float tuition_fee = 2000.0;
    float credit_hour_fee = 200.0;
    float total_credit_hours = 0.0;

    for (int i = 0; i < course_number; i++)
    {
        Course* course = course_list[i];
        total_credit_hours += course->gethours();
    }

    return tuition_fee + (credit_hour_fee * total_credit_hours);
}