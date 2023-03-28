//保证测试代码
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<getch.h>
#include"tools.h"
#include"system.h"
#include "teacher.h"
#include "student.h"
#include "principle.h"

Student *sp=NULL;
Teacher *tp=NULL;
Principle principle={};

char myID[10]={};//id of logined account
int Total=-1;// students total number
int Total_T=-1;// teachers' total number


//for test and first ENmd5
void test()
{	
	//教师密码初始化md5
	for(int i=0;i<Total;i++)
	{
		md5((sp+i)->password);
		strcpy((sp+i)->password,buf);	
	}
	//教师密码初始化md5
	for(int i=0;i<Total_T;i++)
	{
		md5((tp+i)->password);
		strcpy((tp+i)->password,buf);	
	}
	//校长密码初始化md5
	md5(principle.password);
	strcpy(principle.password,buf);
	
	/*CH_max=1;CH_min=1;CH_avg=1;
	EN_max=1;EN_min=1;EN_avg=1;
	Math_max=1;Math_min=1;Math_avg=1;
	strcpy((sp+2)->name,"TEST");
	strcpy((sp+2)->password,"TEST");
	(sp+2)->gender='T';(sp+2)->is_locked='T';
	(sp+2)->attempt='T';(sp+2)->is_out='T';
	(sp+2)->chinese=1;(sp+2)->math=1;
	(sp+2)->english=1;*/
//	Total=1;Total_T=1;
}

//导入文件数据到堆内存中
void init()
{
	
	init_Total_txt();
	
	init_stu();
	
	init_teacher();
	
	init_principle();
}

void show()
{	
	while(1)
	{
		system("clear");
		int com=0;
		for(;com<1||com>4;)
		{
			system("clear");
			printf("******请选择登入类型******\n");
			printf("1.学生登入\n2.教师登入\n3.校长登入\n4.退出\n");
			scanf("%d",&com);
			switch(com)
			{
				case 1:
					certify_std();
					break;
				case 2:
					certify_teacher();
					break;
				case 3:
					certify_principle();
					break;
				case 4:
					return;
					break;
				default:
					stdin->_IO_read_ptr =stdin->_IO_read_end;
					puts("******请重新选择登入类型******");
			}
		}
	}
}

//login certify for principle
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
		if(strcmp(account,principle.id)==0)
		{	
			if(principle.attempt=='3')
			{
				puts("该帐号已锁定");
				anykey_continue();
				return;
			}
			principle.attempt++;
			md5(password);
			if(strcmp(buf,principle.password)==0)
			{
				principle.attempt='0';
				if(is_first_login_t(principle.password))
				{
					change_password_p(principle.id);
					return;
				}
				principle_show();
				return;
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
				anykey_continue();
				return;
			}
			count++;
			puts("帐号不存在，请重新输入\n");
		}
		
	}
	
	puts("输入错误超过三次\n");
	anykey_continue();
	return ;
}

//login certification for teacher	
void certify_teacher()
{
	int count=1;
	char account[10]={};
	char password[20]={};
	// you have three times to try to log in
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
					anykey_continue();
					return;
				}
				(tp+i)->attempt++;
				md5(password);
				if(strcmp(buf,(tp+i)->password)==0)
				{
					if((tp+i)->is_out=='1')
					{
						puts("该教师已离职");
						anykey_continue();
						return;
					}
					(tp+i)->attempt='0';
					strcpy(myID,account);
					if(is_first_login_t((tp+i)->password))
					{
						change_password_t((tp+i)->id);
						return;
					}
					teacher_show();
					return;
				}
				else 
				{
					if((tp+i)->attempt=='3')
					{
						puts("该帐号已锁定");
						anykey_continue();
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
	anykey_continue();
	return ;
}

// login certification for students
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
					anykey_continue();
					return;
				}
				(sp+i)->attempt++;
				md5(password);
				if(strcmp(buf,(sp+i)->password)==0)
				{
					if((sp+i)->is_out=='1')
					{
						puts("该学生已休学");
						anykey_continue();
						return;
					}
					(sp+i)->attempt='0';
					strcpy(myID,account);
					if(is_first_login_t((sp+i)->password))
					{
						change_password((sp+i)->id);
						return;
					}
					student_show();
					return;
				}
				else 
				{
					count++;
					if((sp+i)->attempt=='3')
					{
						puts("该帐号已锁定");
						anykey_continue();
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
	anykey_continue();
	return ;
}
void start()
{
		show();			
}

void principle_show()
{
	while(1)
	{
		system("clear");
		int com=0;
		while(com<1||com>9)
		{
			system("clear");
			puts("******请选择操作******");	
			printf("1.重置校长密码\n2.重置教师密码\n3.添加教师\n4.删除教师\n5.显示在职教师\n6.显示离职教师\n7.解锁教师帐号\n8.修改校长密码\n9.登出帐号\n");
			scanf("%d",&com);
			switch(com)
			{
				case 1:
					reset_password_P();
					break;
				case 2:
					reset_password_T();
					break;
				case 3:
					add_T();
					break;
				case 4:
					del_T();
					break;
				case 5:
					list_all_T();
					break;
				case 6:
					list_out_T();
					break;
				case 7:
					unlock_T();
					break;
				case 8:
					change_password_p(principle.password);
					break;
				case 9:
					return;
					break;
				default:
					stdin->_IO_read_ptr =stdin->_IO_read_end;
					puts("请重新选择操作");
					break;
			}
		}	
	}
}
void teacher_show()
{
	while(1)
	{
		system("clear");
		int com=0;
		while(com<1||com>10)
		{	
			system("clear");
			puts("******请选择操作******");	
			printf("1.添加学生\n2.删除学生\n3.查找学生\n4.修改学生信息\n5.录入学生成绩\n6.重置学生密码\n7.显示所有在读学生\n8.显示退学学生\n9.解锁学生帐号\n10.登出帐号\n");
			scanf("%d",&com);
			switch(com)
			{
				case 1:
					add_std();
					break;
				case 2:
					del_std();
					break;
				case 3:
					search_std();
					break;
				case 4:
					 change_stdinfo();
					break;
				case 5:
					add_grades();
					break;
				case 6:
					reset_password();
					break;
				case 7:
					list_all_std();
					break;
				case 8:
					list_out_std();
					break;
				case 9:
					unlock_std();
					break;
				case 10:
					return;
					break;
				default:
					stdin->_IO_read_ptr =stdin->_IO_read_end;
					puts("请重新选择操作");
					break;
			}
		}	
	}
	
}
void student_show()
{	
	while(1)
	{
		int com=0;
		system("clear");
		while(com<1||com>5)
		{
			system("clear");
			puts("******请选择操作******");	
			printf("1.查询成绩\n2.显示排名\n3.显示本次考试的详细情况\n4.查询个人信息\n5.修改密码\n6.登出帐号\n");
			
			scanf("%d",&com);
			switch(com)
			{
				case 1:
					show_score(myID);
					break;
				case 2:
					show_rank(myID);
					break;
				case 3:
					show_max(myID);
					show_min(myID);
					show_average(myID);
					anykey_continue();
					break;
				case 4:
					show_std_information(myID);
					break;
				case 5:
					change_password(myID);
					break;
				case 6:
					return;
					break;
				default:
					puts("请重新选择操作");
					stdin->_IO_read_ptr =stdin->_IO_read_end;
					break;
			}
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
	
	/*//MAX，IMN，AVG写入文件
	FILE* scores_wp=fopen("scores.txt","w");
	fprintf(scores_wp,"%d %d %d\n",CH_max,CH_min,CH_avg);
	fprintf(scores_wp,"%d %d %d\n",Math_max,Math_min,Math_avg);
	fprintf(scores_wp,"%d %d %d\n",EN_max,EN_min,EN_avg);
	fclose(scores_wp);
	*/
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
	
	//free
	free(sp);
	sp=NULL;
	free(tp);
	tp=NULL;
}
