#include "Student.h"

Student::Student() : level(0), course_number(0)
{
    for (int i = 0; i < 6; i++)
    {
        grades[i] = 0.0;
        course_list[i] = nullptr;
    }
}

void Student::setSname(string n)
{
    name = n;
}

string Student::getSname()
{
    return name;
}

void Student::setID(string id)
{
    ID = id;
}

string Student::getID()
{
    return ID;
}

void Student::setlevel(int L)
{
    level = L;
}

int Student::getlevel() const
{
    return level;
}

void Student::setgrades(double g[6])
{
    for (int i = 0; i < 6; i++)
    {
        grades[i] = g[i];
    }
}

double* Student::getGrades()
{
    return grades;
}

void Student::setcourselist(Course* list[6])
{
    for (int i = 0; i < 6; i++)
    {
        course_list[i] = list[i];
    }
}

Course** Student::getcourselist()
{
    return course_list;
}

void Student::setnumcourses(int count)
{
    course_number = count;
}

int Student::getnumCourses() const
{
    return course_number;
}

void Student::printRegisteredCourses() const
{
    if (course_number == 0)
    {
        cout << "No courses registered." << endl;
    }
    else
    {
        cout << "Registered Courses:" << endl;
        for (int i = 0; i < course_number; i++)
        {
            Course* course = course_list[i];
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

double Student::get_course_gpa(double percent)
{
    if (percent >= 98)
    {
        return 4.00;
    }
    else if (percent >= 93)
    {
        return 4.00;
    }
    else if (percent >= 90)
    {
        return 3.70;
    }
    else if (percent >= 87)
    {
        return 3.30;
    }
    else if (percent >= 83)
    {
        return 3.00;
    }
    else if (percent >= 80)
    {
        return 2.70;
    }
    else if (percent >= 77)
    {
        return 2.30;
    }
    else if (percent >= 73)
    {
        return 2.00;
    }
    else if (percent >= 70)
    {
        return 1.70;
    }
    else if(percent >= 67)
    {
        return 1.30;
    }
    else if (percent >= 65)
    {
        return 1.00;
    }
    else
    {
        return 0.00;
    }
}

double Student::get_total_gpa()
{
    double total_grade_points = 0.0;
    double total_credit_hours = 0.0;

    for (int i = 0; i < course_number; i++)
    {
        Course* course = course_list[i];
        double grade = grades[i];
        int credit_hours = course->gethours();

        total_grade_points += grade * credit_hours;
        total_credit_hours += credit_hours;
    }

    if (total_credit_hours == 0.0)
    {
        return 0.0;
    }

    return total_grade_points / total_credit_hours;
}
    float Student::calculate_Expenses()
    {
        return 0.0;
    }

    bool Student::Register_Course(Course* course)
    {
        if (course_number < 6 && course != nullptr)
        {
            course_list[course_number] = course;
            course_number++;
            return true;
        }
        else
        {
            cout << "The number of registered courses can't exceed 6 courses." << endl;
            return false;
        }
    }
