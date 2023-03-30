#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<getch.h>
#include"tools.h"
#include"system.h"
#include"teacher.h"
static char id[10]={};//用于顺序生成教师工号，可以放到system中
static Student *p=NULL;//添加教师时申请新的堆内存
static int total_t=0;//要导入的总人数
void add_T()//
{
	printf("1、只输入一个教师\n2、从文件中批量导入\n3、其他键退出\n");
	int com_a=0;//选择输入模式
	FILE* teacher_info_ap=fopen("teacher_info.txt","a");//追加写教师的基本信息
	FILE* teacher_account_ap=fopen("teacher_account.txt","a");//追加写教师的密码等信息

	scanf("%d",&com_a);
	
	//输入1，进入单人添加模式，每次添加都需要读取文件并保存文件，总人数+1
	if(com_a==1)
	{

		p=malloc(sizeof(Student));
		char arr[256]={};//用于输入教师姓名
		char sex_s[256]={};//用于输入教师性别
		strcpy(p->id,generate_id_t(ID));
		printf("请输入教师姓名\n");
		while(1)
		{	
			fgets(arr,20,stdin);//限制教师名字长度（因为结构体中name数组为20）
			discard_n(arr);
			stdin->_IO_read_ptr = stdin->_IO_read_end;
			if(strlen(arr)<=19&&strlen(arr)>0)//作为保险：限制教师名字长度（因为结构体中name数组为20）
			{
				break;
			}
			else
			{
				printf("输入错误，请重新输入姓名\n");
			}
		}
		
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		printf("请输入教师性别,女或者男\n");//限制性别输入，只能是女 男）
		while(1)
		{	
			fgets(sex_s,5,stdin);
			discard_n(sex_s);
			stdin->_IO_read_ptr = stdin->_IO_read_end;
			if(strcmp(sex_s,"女")==0||strcmp(sex_s,"男")==0)
			{
				break;
			}
			else
			{
				printf("输入错误，请重新输入性别\n");
			}
		}
	
		//堆内存中新教师信息
		strcpy(p->name,arr);
		md5("000");
		strcpy(p->password,buf);
		strcpy(p->gender,sex_s);
		p->is_locked='0';
		p->is_out='0';
		p->attempt='0';

		fprintf(teacher_info_ap,"%s %s %s %c\n",p->id,p->name,p->gender,p->is_out);//写入基本信息到文件中
		fprintf(teacher_account_ap,"%s %s %c %c\n",p->id,p->password,p->is_locked,p->attempt);//写入初始密码到文件中

		printf("一名教师添加成功,以下为新教师信息\n");
		printf("id=%s gender=%s name=%s  is_locked=%c is_out=%c\n----\n",p->id,p->gender,p->name,p->is_locked,p->is_out);
		fclose(teacher_info_ap);
		fclose(teacher_account_ap);
		
		
	}

	//以下为添加多个教师
	//先打开新文件，读取依次读取新文件的每一行放到堆内存中，最后追加写入全部教师
	if(com_a==2)
	{
		FILE* tea_info_rp1=fopen("tea_info.txt","r");

		
		printf("请输入要导入的总人数\n");
		total_t = count_Total(tea_info_rp1);//导出数据的人数
		FILE* tea_info_rp=fopen("tea_info.txt","r");
		printf("%d个教师添加成功,以下为新教师信息\n",total_t);
		for(int i=0;i<total_t;i++)
		{
			p=malloc(sizeof(Student));	
			strcpy(p->id,generate_id(id));
			md5("000");
			strcpy(p->password,buf);
			p->is_locked='0';
			p->is_out='0';	
			p->attempt='0';
			fscanf(tea_info_rp,"%s %s %s %c",p->id,p->name,p->gender,&p->is_out);	
			fprintf(teacher_info_ap,"%s %s %s %c\n",p->id,p->name,p->gender,p->is_out);

			fprintf(teacher_account_ap,"%s %s %c %c\n",p->id,p->password,p->is_locked,p->attempt);//写入初始密码到文件中
			printf("新写入的信息：id=%s gender=%s name=%s  password=%s is_locked=%c is_out=%c\n\n",p->id,p->gender,p->name,p->password,p->is_locked,p->is_out);
		}
		fclose(tea_info_rp);
 	   	fclose(teacher_info_ap);
 	   	fclose(teacher_account_ap);	
	}
	anykey_continue();
	free(sp);
	free(tp);
	free(p);
	p=NULL;
	tp=NULL;
	tp=NULL;
	init();//添加完教师之后重新读取文件，更新堆内存中sp所指向的内容，用于之后显示教师也能显示新加的教师
}


//方法 删除教师，需要两次输入相同的工号
void del_T()
{
	char del_id[128]={};//第一次输入的工号
	char del_id1[128]={};//再次输入工号确定
	int del=0;//用于选择模式1 2 按工号删除或者退出删除功能
	
	while(del<1||del>2)
	{
		system("clear");
		int flag=0;//判断是否输入正确的标识
		printf("1、按工号删除教师\n2、退出\n");
		scanf("%d",&del);
		if(del==1)
		{
			printf("请输入要删除的教师工号\n");
			fgets(del_id,10,stdin);
			discard_n(del_id);
			for(int i=0;i<Total;i++)
			{	
				if(strcmp(del_id,(tp+i)->id)==0)
				{
					flag=1;
					break;
				}
			}
			if(flag==1)
			{
				printf("请再次输入要删除的教师工号\n");
				fgets(del_id1,10,stdin);
				discard_n(del_id1);
			}
			else
			{
				printf("输入的工号不存在，请重新输入或退出\n");
				del=0;
				continue;
			}
			
			if(strcmp(del_id,del_id1)==0)
			{
				for(int i=0;i<Total;i++)
				{	
					if(strcmp(del_id,(tp+i)->id)==0)
					{
						(tp+i)->is_out='1';
						printf("已经删除教师:%s %s\n",(tp+i)->id,(tp+i)->name);
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
	printf("请输入要解锁的教师工号\n");
	while(1)
	{
		fgets(unlock_id,10,stdin);
		discard_n(unlock_id);
		if(strlen(unlock_id)<10&&strlen(unlock_id)>0)
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
	for(i=0;i<Total;i++)
	{	
		if(strcmp(unlock_id,(tp+i)->id)==0)
		{
			(tp+i)->is_locked='0';
			(tp+i)->attempt='0';
			printf("解锁成功！\n");
			anykey_continue();
			return;
		}
	}
	if(i==Total)
	{
		printf("要解锁的id不存在\n");
		anykey_continue();
		return;
	}
}


//方法 重置教师密码（教师id）
void reset_password_T()
{
	char reset_id[128]={};
	printf("请输入要重置密码的教师工号\n");
	fgets(reset_id,10,stdin);
	discard_n(reset_id);
	int i=0;
	for(;i<Total;i++)
	{	
		if(strcmp(reset_id,(tp+i)->id)==0)
		{
			md5("000");
			strcpy((tp+i)->password,buf);
			printf("\n重置成功\n");
			anykey_continue();
			return;
		}
	}
	if(i==Total)
	{
		printf("输入id有误\n");
			anykey_continue();
			return;
	}
}
void reset_password_P(){}
//方法 显示所有在校教师
void list_all_T()
{
	printf("工号     性别 姓名  是否冻结 \n----\n");
	for(int i=0;i<Total;i++)
	{	
		if((tp+i)->is_out=='0')
		printf("%s %s   %s  %c\n",(tp+i)->id,(tp+i)->gender,(tp+i)->name,(tp+i)->is_locked);
	}
	anykey_continue();
}
//方法 显示退学教师
void list_out_T()
{
	printf("工号    性别 姓名     \n----\n");
	for(int i=0;i<Total;i++)
	{	
		if((tp+i)->is_out=='1')
		printf("%8s %8s %8s   \n",(tp+i)->id,(tp+i)->gender,(tp+i)->name);
	}
	anykey_continue();
}


