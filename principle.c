
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<getch.h>
#include"tools.h"
#include"system.h"
#include"teacher.h"
#include"principle.h"


Student *t_p=NULL;
static int total_t=0;//要导入的总人数

void reset_password_P()
{
	md5("000");
	strcpy(principle.password,buf);
	return;
}

void add_T()//添加老师
{
	char ID[]="00000000000000";
	printf("1、只输入一个教师\n2、从文件中批量导入\n");
	int com_a=0;//选择输入模式
	FILE* teacher_info_ap=fopen("teacher_info.txt","a");//追加写教师的基本信息
	FILE* teacher_account_ap=fopen("teacher_account.txt","a");//追加写教师的密码等信息。

	scanf("%d",&com_a);
	
	//输入1，进入单人添加模式，每次添加都需要读取文件并保存文件，总人数+1
	if(com_a==1)
	{

		t_p=malloc(sizeof(Student));
		char arr[256]={};//用于输入姓名
		char sex_s='0';//用于输入性别
		strcpy(t_p->id,generate_id_t(ID));
		printf("请输入教师姓名\n");
		while(1)
		{	
			scanf("%s",arr);
			stdin->_IO_read_ptr = stdin->_IO_read_end;
			if(strlen(arr)<=19&&strlen(arr)>0)
			{
				break;
			}
			else
			{
				printf("输入错误，请重新输入姓名\n");
			}
		}
		
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		printf("请输入教师性别,w或者m\n");
		while(1)
		{	
			scanf("%c",&sex_s);
			stdin->_IO_read_ptr = stdin->_IO_read_end;
			if(sex_s=='F'||sex_s=='M')
			{
				break;
			}
			else
			{
				printf("输入错误，请重新输入性别\n");
			}
		}
		
		//把姓名、学号等信息放入堆内存
		strcpy(t_p->name,arr);
		md5("000");
		strcpy(t_p->password,buf);
		t_p->gender=sex_s;
		t_p->is_locked='0';
		t_p->is_out='0';
		t_p->attempt='0';


		fprintf(teacher_info_ap,"%s %s %c %c\n",t_p->id,t_p->name,t_p->gender,t_p->is_out);//从堆内存写入基本信息到文件中
		fprintf(teacher_account_ap,"%s %s %c %c\n",t_p->id,t_p->password,t_p->is_locked,t_p->attempt);//从堆内存写入初始密码到文件中
		
		printf("id=%s gender=%c name=%s  is_locked=%c is_out=%c\n----\n",t_p->id,t_p->gender,t_p->name,t_p->is_locked,t_p->is_out);
		fclose(teacher_info_ap);
		fclose(teacher_account_ap);
		
		Total_T++;//每次添加一个人，总人数+1并修改到文件中
		FILE* total_num_wp=fopen("total_num.txt","w");
		if(total_num_wp==NULL) perror("fopen: ");
		fprintf(total_num_wp,"%d %d",Total_T,Total_T);
		fclose(total_num_wp);
		anykey_continue();
		
	}

	//以下为添加多个教师
	//先打开新文件，读取依次读取新文件的每一行放到堆内存中，最后追加写入全部教师
	if(com_a==2)
	{
		FILE* stu_info_rp=fopen("stu_info.txt","r");

		printf("请输入要导入的总人数\n");
		scanf("%d",&total_t);		
		for(int i=0;i<total_t;i++)//循环total_t次，一边读一边写
		{
			t_p=malloc(sizeof(Student));	
			md5("000");
			strcpy(t_p->password,buf);
			t_p->is_locked='0';
			t_p->is_out='0';	
			
			t_p->attempt='0';
			fscanf(stu_info_rp,"%s %s %c %c",t_p->id,t_p->name,&t_p->gender,&t_p->is_out);	
			fprintf(teacher_info_ap,"%s %s %c %c\n",t_p->id,t_p->name,t_p->gender,t_p->is_out);
			fprintf(teacher_account_ap,"%s %s %c %c\n",t_p->id,t_p->password,t_p->is_locked,t_p->attempt);//写入初始密码到文件中
			printf("新写入的信息：id=%s gender=%c name=%s  is_locked=%c is_out=%c\n\n",t_p->id,t_p->gender,t_p->name,t_p->is_locked,t_p->is_out);
		}
		fclose(stu_info_rp);
 	   	fclose(teacher_info_ap);
 	   	fclose(teacher_account_ap);
 	   	
		FILE* total_num_wp=fopen("total_num.txt","w");
		Total_T+=total_t;
		if(total_num_wp==NULL) perror("fopen: ");
		fprintf(total_num_wp,"%d %d",Total,Total_T);
		fclose(total_num_wp);
		
	}
	free(sp);
	free(tp);
	free(t_p);
	t_p=NULL;
	tp=NULL;
	sp=NULL;
	init();
	anykey_continue();
}

//方法 删除老师
void del_T()
{
	char del_id[128]={};//第一次输入的工号
	char del_id1[128]={};//再次输入工号确定
	int del=0;//用于选择模式1 2 按工号删除或者退出删除功能
	
	while(del<1||del>2)
	{
		system("clear");
		int flag=0;//判断是否输入正确的标识
		printf("1、按学号删除老师\n2、退出\n");
		scanf("%d",&del);
		if(del==1)
		{
			printf("请输入要删除的老师工号\n");
			scanf("%s",del_id);
			for(int i=0;i<Total_T;i++)
			{	
				if(strcmp(del_id,(tp+i)->id)==0)
				{
					flag=1;
					break;
				}
			}
			if(flag==1)
			{
				printf("请再次输入要删除的老师工号\n");
				scanf("%s",del_id1);
			}
			else
			{
				printf("输入的工号不存在，请重新输入或退出\n");
				del=0;
				continue;
			}
			
			if(strcmp(del_id,del_id1)==0)
			{
				for(int i=0;i<Total_T;i++)
				{	
					if(strcmp(del_id,(tp+i)->id)==0)
					{
						(tp+i)->is_out='1';
						printf("已经删除老师:%s %s\n",(tp+i)->id,(tp+i)->name);
						anykey_continue();
						return;
					}
				}
			}
			else
			{
				printf("两次工号输入不一致，请重新输入或退出\n");
				del=0;
				continue;
			}
			
		}
		else if(del==2)
		{
			return;
		}
		else
		{
			printf("请重新输入\n");
			continue;
		}

	}
	anykey_continue();
}

//方法 解锁
void unlock_T()
{
	char unlock_id[128]={};
	printf("请输入要解锁的老师工号\n");
	while(1)
	{
		scanf("%s",unlock_id);
		if(strlen(unlock_id)<9&&strlen(unlock_id)>0)
		{
			break;
		}
		else
		{
			printf("输入错误，请重新输入id\n");
			
		}
	}
	scanf("%s",unlock_id);
	int i=0;
	int flag=0;
	for(i=0;i<Total_T;i++)
	{	
		if(strcmp(unlock_id,(tp+i)->id)==0)
		{
			flag=1;
			(tp+i)->is_locked='0';
			(tp+i)->attempt='0';
			printf("解锁成功！\n");
			anykey_continue();
			return;
		}
	}
	if(flag==0)
	{
		printf("要解锁的id不存在\n");
		anykey_continue();
		return;
	}
}


//方法 重置老师密码（老师id）
void reset_password_T()
{
	char reset_id_t[128]={};
	printf("请输入要重置密码的老师工号\n");
	scanf("%s",reset_id_t);
	int i=0;
	for(;i<Total_T;i++)
	{	
		if(strcmp(reset_id_t,(tp+i)->id)==0)
		{
			md5("000");
			strcpy((tp+i)->password,buf);
			printf("\n重置成功\n");
			anykey_continue();
			return;
		}
	}
	if(i==Total_T)
	{
		printf("输入id有误\n");
		anykey_continue();
		return;
	}
}

//方法 显示所有在校老师
void list_all_T()
{
	printf("工号    性别 姓名   是否冻结 \n----\n");
	for(int i=0;i<Total_T;i++)
	{	
		if((tp+i)->is_out=='0')
		printf("%s %c %s %c\n",(tp+i)->id,(tp+i)->gender,(tp+i)->name,(tp+i)->is_locked);
	}
	anykey_continue();
}
//方法 显示退学老师
void list_out_T()
{
	printf("工号    性别 姓名  密码 是否冻结 \n----\n");
	for(int i=0;i<Total_T;i++)
	{	
		if((tp+i)->is_out=='1')
		printf("%s %c %s %c\n",(tp+i)->id,(tp+i)->gender,(tp+i)->name,(tp+i)->is_locked);
	}
	anykey_continue();
}

