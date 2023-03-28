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

void show_score(char* id)//显示成绩
{
	printf("语文成绩：%d\n",getscore_chinese(id));
	printf("数学成绩：%d\n",getscore_math(id));
	printf("英语成绩：%d\n",getscore_english(id));
	anykey_continue();
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

void show_rank(char* id)//显示排名
{
	printf("语文成绩排名：%d\n",rank_chinese(id));
	printf("数学成绩排名：%d\n",rank_math(id));
	printf("英语成绩排名：%d\n",rank_english(id));
	printf("总排名为:%d\n",rank_all(id));
	anykey_continue();
}


void show_std_information(char* id)//显示学生信息
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
	anykey_continue();
	return;
}

void change_password(char* id)//修改学生密码
{
	char newkey[20]={};
	char oldkey[20]={};
	char* temp_password= getpass("请输入旧密码: ");
	strcpy(oldkey,temp_password);
	md5(oldkey);
	printf("\n");
	if(0==strcmp(buf,(sp+find(id))->password))
	{
		char newkey1[20]={};
		char* temp_password1= getpass("请输入新密码:");
		strcpy(newkey1,temp_password1);
		printf("\n");
		char* temp_password2= getpass("请第二次输入新密码:");
		strcpy(newkey,temp_password2);
		printf("\n");
		if(strcmp(newkey,newkey1)==0)
		{
			md5(newkey);
			strcpy((sp+find(id))->password,buf);
			printf("密码修改成功!\n");
			anykey_continue();
			return;
		}
		else
		{
			printf("密码与第一次输入的不一致\n");
			anykey_continue();
			return;
		}
	}
	else
	{
		puts("密码输入错误!");
		anykey_continue();
		return;
	}
	return;
}

void show_max()//显示各科的最高成绩
{
	int max_e=sp->english;
	int max_m=sp->math;
	int max_c=sp->chinese;
	int max_all=sp->english+sp->math+sp->chinese;
	for(int i=1;i<Total;i++)
	{
		if(max_e<((sp+i)->english))
		{
			max_e=(sp+i)->english;
		}
		if(max_m<((sp+i)->math))
		{
			max_m=(sp+i)->math;
		}
		if(max_c<((sp+i)->chinese))
		{
			max_c=(sp+i)->chinese;
		}
		if(max_all<((sp+i)->english+(sp+i)->math+(sp+i)->chinese))
		{
			max_all=((sp+i)->english+(sp+i)->math+(sp+i)->chinese);
		}
	}
	printf("语文最高分:%d 数学最高分:%d 英语最高分:%d\n",max_c,max_m,max_e);
	printf("总成绩最高分:%d\n",max_all); 
	return;
}

void show_min()//显示各科最低成绩
{
	int min_e=sp->english;
	int min_m=sp->math;
	int min_c=sp->chinese;
	int min_all=sp->english+sp->math+sp->chinese;
	for(int i=1;i<Total;i++)
	{
		if(min_e>((sp+i)->english))
		{
			min_e=(sp+i)->english;
		}
		if(min_m>((sp+i)->math))
		{
			min_m=(sp+i)->math;
		}
		if(min_c>((sp+i)->chinese))
		{
			min_c=(sp+i)->chinese;
		}
		if(min_all>((sp+i)->english+(sp+i)->math+(sp+i)->chinese))
		{
			min_all=((sp+i)->english+(sp+i)->math+(sp+i)->chinese);
		}
	}
	printf("语文最低分:%d 数学最低分:%d 英语低分:%d\n",min_c,min_m,min_e);
	printf("总成绩最低分:%d\n",min_all); 
	return;
}

void show_average()//计算平均分
{
	float average_c=0;
	float average_m=0;
	float average_e=0;
	float average_all=0;
	for(int i = 0;i<Total;i++)
	{
		average_c=(average_c*i+(sp+i)->chinese)/(1+i);
		average_m=(average_m*i+(sp+i)->math)/(1+i);
		average_e=(average_e*i+(sp+i)->english)/(1+i);
		average_all=(average_c*i+(sp+i)->english+(sp+i)->math+(sp+i)->chinese)/(1+i);
	}
	printf("语文平均分:%.2f 数学平均分:%.2f 英语平均分:%.2f\n",average_c,average_m,average_e);
	printf("总成绩平均分:%.2f\n",average_all); 
	return;
}	
	
