#include <stdio.h>
#include <stdlib.h>
struct student {
    int    student_number;
    char   name[31];
    int    grade;
    int    semester_credit;
    float  gpa;
};
struct note {
    int    course_code;
    int    student_number;
    int    student_point;
    struct lesson *dugum_basi;
    struct circular *following_number;
    struct circular *following_point;
    struct circular *previous_point;
};
struct  lesson {
    int    course_code;
    char   course_name[26];
    int    credit;
    int    student_counter;
    float  general_gpa;
};


int main()
{

        return 0;
}
