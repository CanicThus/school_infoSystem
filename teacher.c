#include<stdio.h>
#include "system.h"
#include <stdlib.h>
#include"tools.h"
#include <string.h>
#include <getch.h>
//添加学生
void add_std()
{
	printf("1、只输入一个学生\n2、从文件中批量导入\n");
	FILE* students_info_ap=fopen("students_info.txt","a");
	if(getch()==183)
	{
		sp=malloc(sizeof(Student));
		char arr[256]={};
		strcpy(sp->id,generate_id(ID));
		printf("请输入学生姓名\n");
		scanf("%s",arr);
		strcpy(sp->name,arr);
		strcpy(sp->password,"000");
		sp->gender='F';
		sp->is_locked='0';
		sp->is_out='0';
		fprintf(students_info_ap,"%s %s %c %c\n",sp->id,sp->name,sp->gender,sp->is_out);
		printf("id=%s gender=%c name=%s\npassword=%s is_locked=%c is_out=%c\n----\n",sp->id,sp->gender,sp->name,sp->password,sp->is_locked,sp->is_out);
		fclose(students_info_ap);
	}

	//以下为添加多个学生
	//先打开新文件，读取依次读取新文件的每一行放到堆内存中，最后追加写入全部学生
	if(getch()==184)
	{
		FILE* stu_info_rp=fopen("stu_info.txt","r");
		FILE* students_info_ap=fopen("students_info.txt","a");
		for(int i=0;i<4;i++)
		{
			sp=malloc(sizeof(Student));
			fscanf(stu_info_rp,"%s %s %c %c",sp->id,sp->name,&sp->gender,&sp->is_out);	
			fprintf(students_info_ap,"%s %s %c %c\n",sp->id,sp->name,sp->gender,sp->is_out);
			printf("新写入的信息：id=%s gender=%c name=%s\npassword=%s is_locked=%c is_out=%c\n\n",sp->id,sp->gender,sp->name,sp->password,sp->is_locked,sp->is_out);
		}
		fclose(stu_info_rp);
 	   	fclose(students_info_ap);
	}
}
/*
//方法 删除学生
void del_std();
//方法 修改学生信息_name（姓名）
void change_stdinfo_name(char* s);
//方法 修改学生信息_id（id）
void chage_stdinfo_id(char* s);
//方法 查找学生_name(name)
void search_std_name(char* s)
//方法 查找学生_id(id)
void search_std_id(char* s);
//方法 重置学生密码（学生id）
void reset_password(char* s);
  //      学生密码置为0000 学生改为第一次登入
//方法 解锁
void unlock_std(char* s);
  //      不重置
//方法 显示所有学生
void list_all_std();
        //读所有学生信息，显示标志为在校的学生
        
       */
void list_out_std();
