#include "General_student.h"

General_student::General_student() : Student() {}

bool General_student::Register_Course(Course* course)
{
    if (course_number >= 6)
    {
        cout << "Cannot register more than 6 courses." << endl;
        return false;
    }

    int min_student_level = course->get_minstudent_level();
    if (level < min_student_level)
    {
        cout << "Cannot register for this course. Minimum student level requirement not met." << endl;
        return false;
    }

    course_list[course_number] = course;
    course_number++;

    return true;
}

float General_student::calculate_Expenses()
{
    float tuition_fee = 1500.0;
    float credit_hour_fee = 250.0;
    float total_credit_hours = 0.0;

    for (int i = 0; i < course_number; i++)
    {
        Course* course = course_list[i];
        total_credit_hours += course->gethours();
    }

    return tuition_fee + (credit_hour_fee * total_credit_hours);
}