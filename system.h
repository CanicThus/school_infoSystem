
#ifndef SYSTEM_H
#define SYSTEM_H
typedef struct Principle
{	
    char password[33];
    char id[10];
    char attempt;
} Principle;
typedef struct Student
{	
    char name[20];
    char password[33];
    char id[9];
    int math;
    int english;
    int chinese;
    char  is_locked;
    char  is_out;	
    char gender;
    char attempt;
} Student;
typedef struct Teacher
{	
    char name[20];
	char password[33];
	char id[10];
	char attempt;
	char is_locked; //一律0为假 1为真	
	char gender;//M=male F=female
	char is_out;
} Teacher;
extern Student *sp;
extern Teacher *tp;
extern int Total;
extern int Total_T;

extern char ID[];
extern char myID[];
extern Principle principle;

void certify_principle();
void certify_std();
void certify_teacher();
void show();
void start();
void teacher_show();
void student_show();
void principle_show();
void end();
void init();


void init_md5();

#endif//SYSTEM_H

