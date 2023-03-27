#ifndef TOOLS_H
#define TOOLS_H

#include<stdbool.h>

void md5(char *data);
void anykey_continue(void);
extern char buf[];
char* generate_id(char* ID);
//判断是否是第一次登录，初始密码是否为000
bool is_first_login(char* password);
//重置密码,赋值000
void rest_passward(char* id);
//id是否解锁
bool unlock(char* id);
char* generate_id_t(char* ID);
//判断是否是第一次登录，初始密码是否为000
bool is_first_login_t(char* password);
//重置密码,赋值000
void rest_passward_t(char* id);
//id是否解锁
bool unlock_t(char* id);
int find(char* id);
int find_t(char* id);
void init_Total_txt(void);
void init_stu(void);
void init_teacher(void);
void init_principle(void);
void change_password_t(char* id);
void change_password_p(char* id);
void change_name();
void change_gender();
void change_math();
void change_english();
void change_chinese();
void change_isout();







#endif//TOOLS_H
