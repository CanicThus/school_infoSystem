//保证测试代码
#pragma pack(4)
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
Student *sp=NULL;
Teacher *tp=NULL;
int Total=-1;
int Total_T=-1;
int CH_max=-1;
int CH_min=-1;
int CH_avg=-1;
int Math_max=-1;
int EN_max=-1;
int EN_min=-1;
int EN_avg=-1;
int Math_min=-1;
int Math_avg=-1;
void init()
{
	//导入文件数据到堆内存中
	//读入总人数
	FILE* total_num_rp=fopen("/home/canic/桌面/studentSys/src/total_num.txt","r");
	//相对路径无法实现
//	FILE* total_num_rp=fopen("src/total_num.txt","r");
	if(total_num_rp==NULL) perror("fopen: ");
	fscanf(total_num_rp,"%d %d",&Total,&Total_T);
	printf("total=%d total_T=%d\n",Total,Total_T);
	fclose(total_num_rp);
	
	//读入学生信息到堆内存中
	FILE* students_score_rp=fopen("/home/canic/桌面/studentSys/src/students_score.txt","r");
	FILE* students_account_rp=fopen("/home/canic/桌面/studentSys/src/students_account.txt","r");
	FILE* students_info_rp=fopen("/home/canic/桌面/studentSys/src/students_info.txt","r");
	FILE* scores_rp=fopen("/home/canic/桌面/studentSys/src/scores.txt","r");
	sp=malloc(sizeof(Student)*Total);
	for(int i=0;i<Total;i++)
	{
		fscanf(students_info_rp,"%s %s %c %c",(sp+i)->id,(sp+i)->name,&(sp+i)->gender,&(sp+i)->is_out);	
	}
	//puts("------");	
	//根据相同id写入成绩
	Student tem={};
	for(int i=0;i<Total;i++)
	{
		fscanf(students_score_rp,"%s %d %d %d",tem.id,&tem.chinese,&tem.math,&tem.english);
		for(int j=0;j<Total;j++)
		{
			if(strcmp((sp+j)->id,tem.id)==0)
			{
				(sp+j)->math=tem.math;
				(sp+j)->chinese=tem.chinese;
				(sp+j)->english=tem.english;
			}
		}
	}
	
	//根据相同id写入帐号密码是否锁定
	for(int i=0;i<Total;i++)
	{
		fscanf(students_account_rp,"%s %s %c",tem.id,tem.password,&tem.is_locked);
	//	printf("%s %s %c\n",tem.id,tem.password,tem.is_locked);
		for(int j=0;j<Total;j++)
		{
			if(strcmp((sp+j)->id,tem.id)==0)
			{
				strcpy((sp+j)->password,tem.password);
				(sp+j)->is_locked=tem.is_locked;
			}
		}
	}

	//读入各科成绩MAX，MIN，AVG
	fscanf(scores_rp,"%d %d %d",&CH_max,&CH_min,&CH_avg);
	fscanf(scores_rp,"%d %d %d",&Math_max,&Math_min,&Math_avg);
	fscanf(scores_rp,"%d %d %d",&EN_max,&EN_min,&EN_avg);
		
	fclose(students_account_rp);
	fclose(students_score_rp);
	fclose(students_info_rp);
	fclose(scores_rp);

/*	for(int i=0;i<Total;i++)
	{
		printf("id=%s gender=%c name=%s\npassword=%s is_locked=%c is_out=%c\n----\n",(sp+i)->id,(sp+i)->gender,(sp+i)->name,(sp+i)->password,(sp+i)->is_locked,(sp+i)->is_out);
	}
*/
	// 导入教师信息
	tp=malloc(sizeof(Teacher)*Total_T);
	FILE* teacher_info_rp=fopen("/home/canic/桌面/studentSys/src/teacher_info.txt","r");
	FILE* teacher_account_rp=fopen("/home/canic/桌面/studentSys/src/teacher_account.txt","r");
	Teacher temT={};
	for(int i=0;i<Total_T;i++)
	{
		fscanf(teacher_info_rp,"%s %s %c %c",(tp+i)->id,(tp+i)->name,&(tp+i)->gender,&(tp+i)->is_out);
	}
	
	puts("xxxxxxxxxxxxxxxx");
	for(int i=0;i<Total_T;i++)
	{
		//printf("id=%s name=%s password=%s\ngender=%c is_out=%c is_locked=%c\n",(tp+i)->id,(tp+i)->name,(tp+i)->password,(tp+i)->gender,(tp+i)->is_out,(tp+i)->is_locked);	
		printf("%s %s %c\n",temT.id,temT.password,&temT.is_locked);
	}
	puts("11111111111111");
	for(int i=0;i<Total_T;i++)
	{
		fscanf(teacher_account_rp,"%s %s %c",temT.id,temT.password,&temT.is_locked);
		for(int j=0;j<Total_T;j++)
		{
			if(strcmp((tp+j)->id,temT.id)==0)
			{
				strcpy((tp+j)->password,temT.password);
				(tp+j)->is_locked=temT.is_locked;
			}
		}
	}
	puts("22222222");
	puts("333333");
	for(int i=0;i<Total_T;i++)
	{
		printf("id=%s name=%s password=%s\ngender=%c is_out=%c is_locked=%c\n",(tp+i)->id,(tp+i)->name,(tp+i)->password,(tp+i)->gender,(tp+i)->is_out,(tp+i)->is_locked);	
	}
}
void start()
{
	
}

void end()
{

}

int main()
{
		init();
			start();
				end();
}
