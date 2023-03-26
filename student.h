#ifndef STUDENT_H
#define STUDENT_H

int getscore_chinese(char* id);//获取学生语文成绩的函数
int getscore_math(char* id);
int getscore_english(char* id);
void show_score(char* id);
int rank_chinese(char* id);//通过id获取排名
int rank_math(char* id);
int rank_english(char* id);
int rank_all(char* id);
void show_rank();
void show_std_information(char* id);//显示学生信息
void change_password(char* id);
#endif
