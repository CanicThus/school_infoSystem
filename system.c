//保证测试代码
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<getch.h>
#include"tools.h"
#include"system.h"
Student *sp=NULL;
Teacher *tp=NULL;
//Student *sp_out=NULL;//未声明为外部
//Teacher *tp_out=NULL;//未声明为外部
Principle principle={};
//int Total_out=-1;//未声明为外部
//int Total_T_out=-1;//未声明为外部
char myID[10]={};
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
char ID[]="00000000";

/*void init_outNum()
{
	FILE* out_num_rp=fopen("out_num.txt","r");
	FILE* teacher_out_rp=fopen("teacher_out.txt","r");
	fscanf("%d %d",&Total_out,&Total_T_out);
	printf("%d %d\n",otal_out,Total_T_out);
	sp_out=mailloc(sizeof(Student)*Total_out);
	tp_out=malloc(sizeof(Teacher)*Total_T_out);
	for(int i=0;i<Total_T_out;i++)
	{
		fscanf(out_num_rp,"%s %s %c %c",);
	}
	
	
}*/

void test()
{
	CH_max=1;CH_min=1;CH_avg=1;
	EN_max=1;EN_min=1;EN_avg=1;
	Math_max=1;Math_min=1;Math_avg=1;
	strcpy((sp+2)->name,"TEST");
	strcpy((sp+2)->password,"TEST");
	(sp+2)->gender='T';(sp+2)->is_locked='T';
	(sp+2)->attempt='T';(sp+2)->is_out='T';
	(sp+2)->chinese=1;(sp+2)->math=1;
	(sp+2)->english=1;
//	Total=1;Total_T=1;
}

void init()
{
	//导入文件数据到堆内存中
	//读入总人数
	FILE* total_num_rp=fopen("total_num.txt","r");
	//相对路径无法实现
//	FILE* total_num_rp=fopen("src/total_num.txt","r");
	if(total_num_rp==NULL) perror("fopen: ");
	fscanf(total_num_rp,"%d %d",&Total,&Total_T);
	printf("total=%d total_T=%d\n",Total,Total_T);
	fclose(total_num_rp);
	
	//读入学生信息到堆内存中
	FILE* students_score_rp=fopen("students_score.txt","r");
	FILE* students_account_rp=fopen("students_account.txt","r");
	FILE* students_info_rp=fopen("students_info.txt","r");
	FILE* scores_rp=fopen("scores.txt","r");
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
	
	//根据相同id写入帐号密码是否锁定,尝试登入次数
	for(int i=0;i<Total;i++)
	{
		fscanf(students_account_rp,"%s %s %c %c",tem.id,tem.password,&tem.is_locked,&tem.attempt);
	//	printf("%s %s %c\n",tem.id,tem.password,tem.is_locked);
		for(int j=0;j<Total;j++)
		{
			if(strcmp((sp+j)->id,tem.id)==0)
			{
				strcpy((sp+j)->password,tem.password);
				(sp+j)->is_locked=tem.is_locked;
				(sp+j)->attempt=tem.attempt;
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
	puts("xxxxxxxxxxxxxxxx");
	// 导入教师信息
	tp=malloc(sizeof(Teacher)*Total_T);
	FILE* teacher_info_rp=fopen("teacher_info.txt","r");
	FILE* teacher_account_rp=fopen("teacher_account.txt","r");
	Teacher temT={};
	//puts("2xxxxxxxxxxxxxxxx");
	for(int i=0;i<Total_T;i++)
	{
		fscanf(teacher_info_rp,"%s %s %c %c",(tp+i)->id,(tp+i)->name,&(tp+i)->gender,&(tp+i)->is_out);
	}
	
	
	for(int i=0;i<Total_T;i++)
	{
		fscanf(teacher_account_rp,"%s %s %c %c",temT.id,temT.password,&temT.is_locked,&tem.attempt);
		for(int j=0;j<Total_T;j++)
		{
			if(strcmp((tp+j)->id,temT.id)==0)
			{
				strcpy((tp+j)->password,temT.password);
				(tp+j)->is_locked=temT.is_locked;
				(tp+j)->attempt=tem.attempt;
			}
		}
	}
	puts("22222222");
	puts("333333");
	for(int i=0;i<Total_T;i++)
	{
		printf("id=%s name=%s password=%s\ngender=%c is_out=%c is_locked=%c\n",(tp+i)->id,(tp+i)->name,(tp+i)->password,(tp+i)->gender,(tp+i)->is_out,(tp+i)->is_locked);	
	}
	fclose(teacher_info_rp);
	fclose(teacher_account_rp);
	puts("aaaaa");
	// 导入校长帐号密码
	FILE* principle_account_rp=fopen("principle_account.txt","r");
	if(principle_account_rp==NULL)perror("fopen:");
	fscanf(principle_account_rp,"%s %s %c",principle.id,principle.password,&principle.attempt);
	fclose(principle_account_rp);
	printf("%s %s %c",principle.id,principle.password,principle.attempt);
}

void show()
{	
	int com=0;
	for(;com<1||com>3;)
	{
		printf("请选择登入类型\n");
		printf("1.学生登入\n2.教师登入\n3.校长登入\n");
		scanf("%d",&com);
		switch(com)
		{
			case 1:
				puts("1");
				certify_std();
				return ;
				break;
			case 2:
				puts("2");
				certify_teacher();
				return ;
				break;
			case 3:
				puts("3");
				certify_principle();
				return;
				break;
			default:
				puts("请重新选择登入类型");
		}
	}
	return;
}

void certify_principle()
{
	int count=1;
	char account[10]={};
	char password[20]={};
	while(count<4)
	{
		printf("第%d次操作\n",count);
		stdin->_IO_read_ptr =stdin->_IO_read_end;
		printf("请输入帐号：\n");
		fgets(account,10,stdin);
		stdin->_IO_read_ptr =stdin->_IO_read_end;
		printf("请输入密码：");
		fgets(password,20,stdin);
		stdin->_IO_read_ptr =stdin->_IO_read_end;
		//将回车改为\0
		for(int i=0;i<20;i++)
		{
			if(password[i]=='\n')password[i]='\0';
		}
		
		//判断帐号密码相同
		printf("\n%s %s\n",account,principle.id);
		printf("%d\n",strcmp(account,principle.id));
		if(strcmp(account,principle.id)==0)
		{	
			if(principle.attempt=='3')
			{
				puts("该帐号已锁定");
				return;
			}
			principle.attempt++;
			if(strcmp(password,principle.password)==0)
			{
				principle.attempt='0';
				principle_show();
			}
			else
			{
				count++;
				puts("帐号密码不一致，请重新输入\n");
			}
		}
		else
		{
			if(principle.attempt=='3')
			{
				puts("该帐号已锁定");
				return;
			}
			count++;
			puts("帐号不存在，请重新输入\n");
		}
		
	}
	
	puts("输入错误超过三次\n");
	
	return ;
}
	
void certify_teacher()
{
	int count=1;
	char account[10]={};
	char password[20]={};
	while(count<4)
	{
		printf("第%d次操作\n",count);
		stdin->_IO_read_ptr =stdin->_IO_read_end;
		printf("请输入帐号：\n");
		fgets(account,10,stdin);
		stdin->_IO_read_ptr =stdin->_IO_read_end;
		printf("请输入密码：");
		fgets(password,20,stdin);
		stdin->_IO_read_ptr =stdin->_IO_read_end;
		//将回车改为\0
		for(int i=0;i<20;i++)
		{
			if(password[i]=='\n')password[i]='\0';
		}
		
		//判断帐号密码相同
		int i=0;
		for(;i<Total_T;i++)
		{
			if(strcmp(account,(tp+i)->id)==0)
			{
				if((tp+i)->attempt=='3')
				{
					puts("该帐号已锁定");
					return;
				}
				(tp+i)->attempt++;
				if(strcmp(password,(tp+i)->password)==0)
				{
					if((tp+i)->is_out=='1')
					{
						puts("该教师已离职");
						return;
					}
					(tp+i)->attempt='0';
					strcpy(myID,password);
					teacher_show();
				}
				else 
				{
					if((tp+i)->attempt=='3')
					{
						puts("该帐号已锁定");
						return;
					}
					count++;
					puts("帐号密码不一致，请重新输入\n");
					break;
				}
			}
		}
		if(i==Total_T)
		{
			printf("当前帐号不存在\n");
			count++;
		}	
	}
	
	
	puts("输入错误超过三次\n");
	return ;
}
void certify_std()
{
	int count=1;
	char account[9]={};
	char password[20]={};
	while(count<4)
	{
		printf("第%d次操作\n",count);
		stdin->_IO_read_ptr =stdin->_IO_read_end;
		printf("请输入帐号：\n");
		fgets(account,9,stdin);
		stdin->_IO_read_ptr =stdin->_IO_read_end;
		printf("请输入密码：");
		fgets(password,20,stdin);
		stdin->_IO_read_ptr =stdin->_IO_read_end;
		//将回车改为\0
		for(int i=0;i<20;i++)
		{
			if(password[i]=='\n')password[i]='\0';
		}
		
		//判断帐号密码相同
		int i=0;
		for(;i<Total;i++)
		{
			if(strcmp(account,(sp+i)->id)==0)
			{
				if((sp+i)->attempt=='3')
				{
					puts("该帐号已锁定");
					return;
				}
				(sp+i)->attempt++;
				if(strcmp(password,(sp+i)->password)==0)
				{
					if((sp+i)->is_out=='1')
					{
						puts("该学生已休学");
						return;
					}
					(sp+i)->attempt='0';
					strcpy(myID,password);
					student_show();
				}
				else 
				{
					count++;
					if((sp+i)->attempt=='3')
					{
						puts("该帐号已锁定");
						return;
					}
					puts("帐号密码不一致，请重新输入\n");
					break;
				}
			}
		}
		if(i==Total)
		{
			printf("当前帐号不存在\n");
			count++;
		}	
	}
	
	puts("输入错误超过三次\n");
	return ;
}
void start()
{
	show();
	return;
		
}

void principle_show()
{
	int com=0;
	while(com<1||com>8)
	{
		puts("请选择操作");	
		printf("1.重置校长密码\n2.重置教师密码\n3.添加教师\n4.删除教师\n5.显示在职教师\n6.显示离职教师\n7.解锁教师帐号\n8.修改校长密码");
		scanf("%d",&com);
		switch(com)
		{
			case 1:
				puts("1");
				break;
			case 2:
				puts("2");
				break;
			case 3:
				puts("3");
				break;
			case 4:
				puts("4");
				break;
			case 5:
				puts("5");
				break;
			case 6:
				puts("6");
				break;
			case 7:
				puts("7");
				break;
			case 8:
				puts("8");
				strcpy(principle.password,"1111");
				break;
			default:
				puts("请重新选择操作");
				break;
		}
	}	
}
void teacher_show()
{
	int com=0;
	while(com<1||com>8)
	{
		puts("请选择操作");	
		printf("1.添加学生\n2.删除学生\n3.查找学生\n4.修改学生信息\n5.录入学生成绩\n6.重置学生密码\n7.显示所有在读学生\n8.test显示休学学生\n");
		scanf("%d",&com);
		switch(com)
		{
			case 1:
				puts("1");
				break;
			case 2:
				puts("2");
				break;
			case 3:
				puts("3");
				break;
			case 4:
				puts("4");
				break;
			case 5:
				puts("5");
				break;
			case 6:
				puts("6");
				break;
			case 7:
				puts("7");
				break;
			case 8:
				puts("8");
				strcpy((tp+2)->name,"AAAA");
				break;
			default:
				puts("请重新选择操作");
				break;
		}
	}	
}
void student_show()
{	
	int com=0;
	while(com<1||com>4)
	{
		puts("请选择操作");	
		printf("1.查询成绩\n2.显示排名\n3.查询个人信息\n4.修改密码\n");
		scanf("%d",&com);
		switch(com)
		{
			case 1:
				puts("1");
				break;
			case 2:
				puts("2");
				break;
			case 3:
				puts("3");
				break;
			case 4:
				puts("4");
				break;
			default:
				puts("请重新选择操作");
				break;
		}
	}
}


void end()
{
	//学生、教师总人数写入
	FILE* total_num_wp=fopen("total_num.txt","w");
	fprintf(total_num_wp,"%d %d",Total,Total_T);
	fclose(total_num_wp);
	//FILE* students_out_ap=fopen("students_out.txt","a");
	
	//学生信息写入文件	
	FILE* students_score_wp=fopen("students_score.txt","w");
	FILE* students_account_wp=fopen("students_account.txt","w");
	FILE* students_info_wp=fopen("students_info.txt","w");
	
	for(int i=0;i<Total;i++)
	{
		fprintf(students_score_wp,"%s %d %d %d\n",(sp+i)->id,(sp+i)->chinese,(sp+i)->math,(sp+i)->english);
		fprintf(students_account_wp,"%s %s %c %c\n",(sp+i)->id,(sp+i)->password,(sp+i)->is_locked,(sp+i)->attempt);
		fprintf(students_info_wp,"%s %s %c %c\n",(sp+i)->id,(sp+i)->name,(sp+i)->gender,(sp+i)->is_out);
	}
	fclose(students_score_wp);
	fclose(students_account_wp);
	fclose(students_info_wp);
	
	//MAX，IMN，AVG写入文件
	FILE* scores_wp=fopen("scores.txt","w");
	fprintf(scores_wp,"%d %d %d\n",CH_max,CH_min,CH_avg);
	fprintf(scores_wp,"%d %d %d\n",Math_max,Math_min,Math_avg);
	fprintf(scores_wp,"%d %d %d\n",EN_max,EN_min,EN_avg);
	fclose(scores_wp);
	
	//堆内存教师信息写入文件
	FILE* teacher_info_wp=fopen("teacher_info.txt","w");
	FILE* teacher_account_wp=fopen("teacher_account.txt","w");
	for(int i=0;i<Total_T;i++)
	{
		fprintf(teacher_info_wp,"%s %s %c %c\n",(tp+i)->id,(tp+i)->name,(tp+i)->gender,(tp+i)->is_out);
		fprintf(teacher_account_wp,"%s %s %c %c\n",(tp+i)->id,(tp+i)->password,(tp+i)->is_locked,(tp+i)->attempt);
	}
	fclose(teacher_account_wp);
	fclose(teacher_info_wp);
	
	//FILE* teacher_out_ap=fopen("teacher_out.txt","a");
	
	//校长信息堆内存写入文件
	FILE* principle_account_wp=fopen("principle_account.txt","w");
	fprintf(principle_account_wp,"%s %s %c\n",principle.id,principle.password,principle.attempt);
	fclose(principle_account_wp);

}
