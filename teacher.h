#ifndef TEACHER_H
#define TEACHER_H

#include<stdbool.h>
//添加学生
void add_std();
//方法 删除学生
void del_std();
void change_stdinfo();//修改学生信息
//方法 修改学生信息_name（姓名）
void change_stdinfo_name();
//方法 修改学生信息_id（id）
void change_stdinfo_id();
void search_std();//查找学生
//方法 查找学生_name(name)
void search_std_name();
//方法 查找学生_id(id)
void search_std_id();
//方法 重置学生密码（学生id//学生密码置为000 学生改为第一次登入
void reset_password();
//方法 解锁
void unlock_std();
//方法 显示所有学生
void list_all_std();
//读所有学生信息，显示标志为在校的学生
//方法 显示退学学生
void list_out_std();
void add_grades();
#endif//TEACHER_H
