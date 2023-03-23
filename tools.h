#ifndef TOOLS_H
#define TOOLS_H

#include<stdbool.h>

char* generate_id(char* ID);
//判断是否是第一次登录，初始密码是否为000
bool is_first_login(char* password);
//重置密码,赋值000
void rest_passward(char* id);
//id是否解锁
bool unlock(char* id);

#endif//TOOLS_H
