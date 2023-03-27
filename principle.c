
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
		char arr[256]={};
		char sex_s='0';
		strcpy(t_p->id,generate_id_t(ID));
		printf("请输入教师姓名\n");
		scanf("%s",arr);
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		printf("请输入教师性别\n");
		scanf("%c",&sex_s);
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		
		strcpy(t_p->name,arr);
		md5("000");
		strcpy(t_p->password,buf);
		t_p->gender=sex_s;
		t_p->is_locked='0';
		t_p->is_out='0';
		t_p->attempt='0';


		fprintf(teacher_info_ap,"%s %s %c %c\n",t_p->id,t_p->name,t_p->gender,t_p->is_out);//写入基本信息到文件中
		fprintf(teacher_account_ap,"%s %s %c %c\n",t_p->id,t_p->password,t_p->is_locked,t_p->attempt);//写入初始密码到文件中
		
		printf("id=%s gender=%c name=%s  password=%s is_locked=%c is_out=%c\n----\n",t_p->id,t_p->gender,t_p->name,t_p->password,t_p->is_locked,t_p->is_out);
		fclose(teacher_info_ap);

		fclose(teacher_account_ap);
		
		Total_T++;
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
		for(int i=0;i<total_t;i++)
		{
			t_p=malloc(sizeof(Student));	
			
			strcpy(t_p->password,"000");
			t_p->is_locked='0';
			t_p->is_out='0';	
			
			t_p->attempt='0';
			fscanf(stu_info_rp,"%s %s %c %c",t_p->id,t_p->name,&t_p->gender,&t_p->is_out);	
			fprintf(teacher_info_ap,"%s %s %c %c\n",t_p->id,t_p->name,t_p->gender,t_p->is_out);
			fprintf(teacher_account_ap,"%s %s %c %c\n",t_p->id,t_p->password,t_p->is_locked,t_p->attempt);//写入初始密码到文件中
			printf("新写入的信息：id=%s gender=%c name=%s  password=%s is_locked=%c is_out=%c\n\n",t_p->id,t_p->gender,t_p->name,t_p->password,t_p->is_locked,t_p->is_out);
		}
		fclose(stu_info_rp);
 	   	fclose(teacher_info_ap);
 	   	fclose(teacher_account_ap);
 	   	
		FILE* total_num_wp=fopen("total_num.txt","w");
		Total_T+=total_t;
		if(total_num_wp==NULL) perror("fopen: ");
		fprintf(total_num_wp,"%d %d",Total_T,Total_T);
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
	char del_id_t[9]={};
	printf("请输入要删除的老师工号\n");
	scanf("%s",del_id_t);
	for(int i=0;i<Total_T;i++)
	{	
		if(strcmp(del_id_t,(tp+i)->id)==0)
		{
			(tp+i)->is_out='1';
			puts("删除成功");
			anykey_continue();
			return;
		}
	}
}

//方法 解锁
void unlock_T()
{
	char unlock_id_t[9]={};
	printf("请输入要解锁的老师工号\n");
	scanf("%s",unlock_id_t);
	int i=0;
	for(;i<Total_T;i++)
	{	
		if(strcmp(unlock_id_t,(tp+i)->id)==0)
		{
			(tp+i)->is_locked='0';
			(tp+i)->attempt='0';
			printf("解锁成功！\n");
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


//方法 重置老师密码（老师id）
void reset_password_T()
{
	char reset_id_t[9]={};
	printf("请输入要重置密码的老师工号\n");
	scanf("%s",reset_id_t);
	int i=0;
	for(;i<Total_T;i++)
	{	
		if(strcmp(reset_id_t,(tp+i)->id)==0)
		{
			strcpy((tp+i)->password,"000");
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
	printf("工号    性别 姓名  密码 是否冻结 \n----\n");
	for(int i=0;i<Total_T;i++)
	{	
		if((tp+i)->is_out=='0')
		printf("%s %c %s %s %c\n",(tp+i)->id,(tp+i)->gender,(tp+i)->name,(tp+i)->password,(tp+i)->is_locked);
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
		printf("%s %c %s %s %c\n",(tp+i)->id,(tp+i)->gender,(tp+i)->name,(tp+i)->password,(tp+i)->is_locked);
	}
	anykey_continue();
}

