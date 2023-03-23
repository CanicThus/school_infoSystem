
#ifndef SYSTEM_H
#define SYSTEM_H
typedef struct Student
{	
    char name[20];
    char password[20];
    char id[8];
    int math;
    int english;
    int chinese;
    char  is_locked;
    char  is_out;	
    char gender;
} Student;
typedef struct Teacher
{	
    char name[20];
	char password[20];
	char id[12];
	char is_locked; //一律0为假 1为真	
	char gender;//M=male F=female
	char is_out;
} Teacher;
extern Student *sp;
extern Teacher *tp;
extern int Total;
extern int Total_T;
extern int CH_max;
extern int CH_min;
extern int CH_avg;
extern int Math_max;
extern int EN_max;
extern int EN_min;
extern int EN_avg;
extern int Math_min;
extern int Math_avg;
extern char ID[];

void show();
void start();
void teacher_show();
void student_show();
void principle_show();
void end();
void init();
void start();


#endif//SYSTEM_H

