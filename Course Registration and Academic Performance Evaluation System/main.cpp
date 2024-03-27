#include <iostream>
#include <iomanip>
#include "Course.h"
#include "NormalCourse.h"
#include "SummerCourse.h"
#include "Student.h"
#include "General_student.h"
#include "Special_student.h"
using namespace std;
static Course* courses [] = {new NormalCourse("Math", 1, 2),
                             new NormalCourse("Programming_1", 1, 3),
                             new NormalCourse("Technical_Writing", 1, 3),
                             new NormalCourse("Electronics", 2, 4),
                             new NormalCourse("Data_Structures", 2, 3),
                             new NormalCourse("OOP", 2, 3),
                             new NormalCourse("Algorithms", 3, 2),
                             new NormalCourse("Operating_Systems", 3, 3),
                             new NormalCourse("Databases", 3, 3),
                             new NormalCourse("Machine_Learning", 4, 3),
                             new NormalCourse("Compilers", 4, 4),
                             new NormalCourse("Programming_Concepts", 4, 4),
                             new SummerCourse("Math", 1, 2),
                             new SummerCourse("Compilers", 4, 4),
                             new SummerCourse("Algorithms", 3, 2),
                             new SummerCourse("OOP", 2, 3)};
Course* searchcourse(string code){
    for(int i=0;i<16;i++){
        if(courses[i]->getcode()==code){
            return courses[i];
        }
    }
    return nullptr;
}
bool validateNumber(string &s){
    try{
        stoi(s);
        return true;
    }
    catch (invalid_argument){
        return false;
    }
}
int main()
{
    int num_of_students;
    int student_type;
    string student_name;
    string student_ID;
    int student_level;
    int num_of_courses;
    string course_code;
    int course_grade;
    string schoice;
    while(true) {
        cout << "enter total number of students: ";
        cin >> schoice;
        if (validateNumber(schoice)) {
            num_of_students = stoi(schoice);
            break;
        } else {
            cout << "invalid input" << endl;
        }
    }
    Student* student_list[num_of_students];
    for(int i=0;i<num_of_students;i++){

        while (true){
            cout<<"enter student type (0: general, 1: special): ";
            cin>>schoice;
            if (validateNumber(schoice)) {
                student_type = stoi(schoice);
                if (student_type==0||student_type==1){
                    break;}
                else{
                    cout<<"invalid choice"<<endl;
                }
            }
            else{
                cout<<"invalid input"<<endl;
            }
        }
        if(student_type==0){
            student_list[i]= new General_student;
        }
        else if(student_type==1){
            student_list[i]=new Special_student;
        }
        else{
            cout<<"invalid choice";
        }
        cout<<"enter name: ";
        cin.ignore();
        getline(cin,student_name);
        student_list[i]->setSname(student_name);

        cout<<"enter ID: ";
        cin>>student_ID;
        student_list[i]->setID(student_ID);
        while(true){
            cout<<"enter student level: ";
            cin>>schoice;
            if (validateNumber(schoice)) {
                student_level = stoi(schoice);
                if (student_level > 0 && student_level <= 4) {
                    break;
                } else {
                    cout << "invalid level" << endl;
                }
            }
            else{
                cout<<"invalid input"<<endl;
            }



        }

        student_list[i]->setlevel(student_level);
        while(true){
            cout<<"Number of courses to be registered: ";
            cin>>schoice;
            if (validateNumber(schoice)) {
                num_of_courses = stoi(schoice);
                if (num_of_courses <= 6 && num_of_courses > 0) {
                    break;
                } else {
                    cout << "invalid number of courses" << endl;
                }
            }
            else{
                cout<<"invalid input"<<endl;
            }
        }



        cout<<"courses to be registered: "<<endl;
        double *grades=student_list[i]->getGrades();
        for(int j=0;j<num_of_courses;j++){
            cout<<"course "<<j+1<<": "<<endl;
            cout<<"enter course code: " << endl;
            cin>>course_code;
            Course* course= searchcourse(course_code);
            if(course == nullptr){
                cout << "This course doesn't exist"<<endl;
                continue;
            }
            if (course->get_minstudent_level()>student_level){
                cout<<"You cannot register in this course"<<endl;
                continue;
            }

            student_list[i]->Register_Course(course);
            while(true){
                cout<<"enter grade: " << endl;
                cin>>schoice;
                if (validateNumber(schoice)) {
                    course_grade = stoi(schoice);
                    break;
                } else {
                    cout << "invalid input" << endl;
                }

            }

            grades[student_list[i]->getnumCourses()-1]=course_grade;


        }
        student_list[i]->setgrades(grades);

    }

    for(int i=0;i<num_of_students;i++){
        cout<<"student name: ";
        cout<<student_list[i]->getSname()<<endl;
        cout<<"student ID: ";
        cout<<student_list[i]->getID()<<endl;
        cout<<"student level: ";
        cout<<student_list[i]->getlevel()<<endl;
        student_list[i]->printRegisteredCourses();
        cout<<"overall GPA: ";
        cout<<fixed << setprecision(1) << student_list[i]->get_total_gpa()<<endl;
        cout<<"expenses="<<student_list[i]->calculate_Expenses()<<"EGP"<<endl;

    }

    return 0;
}

