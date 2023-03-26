#include<stdio.h>
#include "system.h"
#include <stdlib.h>
#include"tools.h"
#include <string.h>
#include <getch.h>



int getscore_chinese(char* id)//获取学生语文成绩的函数
{
	for(int i=0;i<Total;i++)
	{
		if(strcmp(id,((sp+i)->id))==0)
		{
			return ((sp+i)->chinese);
		}
	}
	return -1;
}

int getscore_math(char* id)//获取学生数学成绩的函数
{
	for(int i=0;i<Total;i++)
	{
		if(strcmp(id,((sp+i)->id))==0)
		{
			return ((sp+i)->math);
		}
	}
	return -1;
}

int getscore_english(char* id)//获取学生英语成绩的函数
{
	for(int i=0;i<Total;i++)
	{
		if(strcmp(id,((sp+i)->id))==0)
		{
			return ((sp+i)->english);
		}
	}
	return -1;
}

void show_score(char* id)
{
	printf("语文成绩：%d\n",getscore_chinese(id));
	printf("数学成绩：%d\n",getscore_math(id));
	printf("英语成绩：%d\n",getscore_english(id));
}

int rank_chinese(char* id)//排名函数，需要给它一个id，返回一个排名
{
	int num=1;//排名
	//printf("%d\n",getscore(id));
	for(int i =0;i<Total;i++)
	{
		if('1'==((sp+i)->is_out))
		{
			continue;
		}
		if(getscore_chinese(id)<((sp+i)->chinese))
		{
			num++;
		}
	}
	return num;
}

int rank_math(char* id)//排名函数，需要给它一个id，返回一个排名
{
	int num=1;//排名
	//printf("%d\n",getscore(id));
	for(int i =0;i<Total;i++)
	{
		if('1'==((sp+i)->is_out))
		{
			continue;
		}
		if(getscore_math(id)<((sp+i)->math))
		{
			//printf("--------\n");
			num++;
		}
	}
	return num;
}

int rank_english(char* id)//排名函数，需要给它一个id，返回一个排名
{
	int num=1;//排名
	//printf("%d\n",getscore(id));
	for(int i =0;i<Total;i++)
	{
		if('1'==((sp+i)->is_out))
		{
			continue;
		}
		if(getscore_english(id)<((sp+i)->english))
		{
			//printf("--------\n");
			num++;
		}
	}
	return num;
}

int rank_all(char* id)//排名函数，需要给它一个id，返回一个排名
{
	int num=1;//排名
	//printf("%d\n",getscore(id));
	for(int i =0;i<Total;i++)
	{
		if('1'==((sp+i)->is_out))
		{
			continue;
		}
		if((getscore_chinese(id)+getscore_math(id)+getscore_english(id))<((sp+i)->english+(sp+i)->chinese+(sp+i)->math))
		{
			//printf("--------\n");
			num++;
		}
	}
	return num;
}

void show_rank(char* id)
{
	printf("语文成绩排名：%d\n",rank_chinese(id));
	printf("数学成绩排名：%d\n",rank_math(id));
	printf("英语成绩排名：%d\n",rank_english(id));
	printf("总排名为:%d\n",rank_all(id));
}


void show_std_information(char* id)
{
	printf("学号:%s\n",id);
	for(int i=0;i<Total;i++)
	{
		if(strcmp(id,((sp+i)->id))==0)
		{
			printf("姓名:%s\n",(sp+i)->name);
		}
	}
	for(int i=0;i<Total;i++)
	{
		if(strcmp(id,((sp+i)->id))==0)
		{
			printf("性别:%c\n",(sp+i)->gender);
		}
	}
	return;
}

void change_password(char* id)
{
	char newkey[20]={};
	char oldkey[20]={};
	printf("请输入旧密码:");
	scanf("%s",oldkey);
	if(0==strcmp(oldkey,(sp+find(id))->password))
	{
		printf("请输入新密码:");
		scanf("%s",newkey);
		strcpy((sp+find(id))->password,newkey);
		FILE* fwp=fopen("students_account.txt","r+");
		if(fwp==NULL)perror("fopen:");
		int a =fseek(fwp,9+15*find(id),SEEK_SET);
		printf("%d",a);
		fprintf(fwp,"%s",newkey);
		fclose(fwp);
		printf("密码修改成功!\n");
		return;
	}
	else
	{
		puts("密码输入错误!");
		return;
	}
	return;
}
