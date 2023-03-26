#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<getch.h>
#include"tools.h"
#include"system.h"
#include"teacher.h"
//添加学生
Student *p=NULL;
static int total=0;//要导入的总人数
void add_std()//
{
	printf("1、只输入一个学生\n2、从文件中批量导入\n");
	int com_a=0;
	FILE* students_info_ap=fopen("students_info.txt","a");//追加写学生的基本信息
	FILE* students_score_ap=fopen("students_score.txt","a");//追加写学生的成绩，主要是把学号写进去，成绩初始值为0。
	scanf("%d",&com_a);
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	//输入1，进入单人添加模式，每次添加都需要读取文件并保存文件，总人数+1
	if(com_a==1)
	{

		p=malloc(sizeof(Student));
		char arr[256]={};
		strcpy(p->id,generate_id(ID));
		printf("请输入学生姓名\n");
		scanf("%s",arr);
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		strcpy(p->name,arr);
		strcpy(p->password,"000");
		p->gender='F';
		p->is_locked='0';
		p->is_out='0';
		
		p->chinese=0;
		p->math=0;
		p->english=0;

		fprintf(students_info_ap,"%s %s %c %c\n",p->id,p->name,p->gender,p->is_out);//写入基本信息到文件中
		fprintf(students_score_ap,"%s %d %d %d\n",p->id,p->chinese,p->math,p->english);//写入初始成绩到文件中
		printf("id=%s gender=%c name=%s\npassword=%s is_locked=%c is_out=%c\n----\n",p->id,p->gender,p->name,p->password,p->is_locked,p->is_out);
		fclose(students_info_ap);
		fclose(students_score_ap);
		
		FILE* total_num_wp=fopen("total_num.txt","w");
		Total++;
		if(total_num_wp==NULL) perror("fopen: ");
		fprintf(total_num_wp,"%d %d",Total,Total_T);
		fclose(total_num_wp);
		
	}

	//以下为添加多个学生
	//先打开新文件，读取依次读取新文件的每一行放到堆内存中，最后追加写入全部学生
	if(com_a==2)
	{
		FILE* stu_info_rp=fopen("stu_info.txt","r");
		FILE* students_info_ap=fopen("students_info.txt","a");
		printf("请输入要导入的总人数\n");
		scanf("%d",&total);		
		for(int i=0;i<total;i++)
		{
			p=malloc(sizeof(Student));
			fscanf(stu_info_rp,"%s %s %c %c",p->id,p->name,&p->gender,&p->is_out);	
			fprintf(students_info_ap,"%s %s %c %c\n",p->id,p->name,p->gender,p->is_out);
			printf("新写入的信息：id=%s gender=%c name=%s\npassword=%s is_locked=%c is_out=%c\n\n",p->id,p->gender,p->name,p->password,p->is_locked,p->is_out);
		}
		fclose(stu_info_rp);
 	   	fclose(students_info_ap);
 	   	
 	   	printf("这是写入前total=%d total_T=%d\n",Total,Total_T);
		FILE* total_num_wp=fopen("total_num.txt","w");
		Total+=total;
		if(total_num_wp==NULL) perror("fopen: ");
		fprintf(total_num_wp,"%d %d",Total,Total_T);
		fclose(total_num_wp);
		printf("这是写入后total=%d total_T=%d\n",Total,Total_T);	
	}
	free(sp);
	sp=NULL;
	init();
}


//方法 删除学生
void del_std()
{
	char del_id[9]={};
	printf("请输入要删除的学生学号\n");
	scanf("%s",del_id);
	for(int i=0;i<Total;i++)
	{	
		if(strcmp(del_id,(sp+i)->id)==0)
		{
			(sp+i)->is_out='1';
			break;
		}
	}
}
void search_std()//查找学生
{
	int search=0;
	system("clear");
	
	while(search<1||search>2)
	{
		printf("1、按学号查找\n2、按姓名查找\n");
		scanf("%d",&search);
		switch(search)
		{
			case 1:search_std_id();break;
			case 2:search_std_name();break;
			default:puts("请重新选择查找方式");break;
		}
	}
}
void search_std_id()//按照学生ID查找信息
{
	char std_id[9]={};
	printf("请输入要查找的学生学号\n");
	scanf("%s",std_id);
	for(int i=0;i<Total;i++)
	{	
		if(strcmp(std_id,(sp+i)->id)==0)
		{
			printf("学号    性别 姓名   语文 数学 英语 密码 是否冻结 \n----\n");
			printf("%s %c %s %d %d %d %s %c\n",(sp+i)->id,(sp+i)->gender,(sp+i)->name,(sp+i)->chinese,(sp+i)->math,(sp+i)->english,(sp+i)->password,(sp+i)->is_locked);
			break;
		}
	}
}
void search_std_name()//按照学生姓名查找信息
{
	char std_name[20]={};
	printf("请输入要查找的学生姓名\n");
	scanf("%s",std_name);
	for(int i=0;i<Total;i++)
	{	
		if(strcmp(std_name,(sp+i)->name)==0)
		{
			printf("学号    性别 姓名   语文 数学 英语 密码 是否冻结 \n----\n");
			printf("%s %c %s %d %d %d %s %c\n",(sp+i)->id,(sp+i)->gender,(sp+i)->name,(sp+i)->chinese,(sp+i)->math,(sp+i)->english,(sp+i)->password,(sp+i)->is_locked);
		}
	}
}



void change_stdinfo()//修改学生信息
{
	int change=0;
	system("clear");
	
	while(change<1||change>2)
	{
		printf("1、按学号修改\n2、按姓名修改\n");
		scanf("%d",&change);
		switch(change)
		{
			case 1:change_stdinfo_id();break;
			case 2:change_stdinfo_name();break;
			default:puts("请重新选择方式");break;
		}
	}
}


void change_stdinfo_id()//按照学生ID修改信息
{
	char change_id[9]={};
	printf("请输入要修改的学生学号\n");
	scanf("%s",change_id);
	for(int i=0;i<Total;i++)
	{	
		if(strcmp(change_id,(sp+i)->id)==0)
		{
			printf("学号    性别 姓名   语文 数学 英语 密码 是否冻结 \n----\n");
			printf("%s %c %s %d %d %d %s %c\n",(sp+i)->id,(sp+i)->gender,(sp+i)->name,(sp+i)->chinese,(sp+i)->math,(sp+i)->english,(sp+i)->password,(sp+i)->is_locked);
			
			int ch=0;
			
			while(ch<1||ch>6)
			{
				printf("请选择要修改的内容\n1、姓名\n2、性别\n3、语文成绩\n4、数学成绩\n5、英语成绩\n6、是否离校\n");
				scanf("%d",&ch);
				switch(ch)
				{
					case 1:change_name(&(sp+i)->name);break;
					case 2:change_gender(&(sp+i)->gender);break;
					case 3:change_chinese(&(sp+i)->chinese);break;
					case 4:change_math(&(sp+i)->math);break;
					case 5:change_english(&(sp+i)->english);break;
					case 6:change_isout(&(sp+i)->is_out);break;
					default:puts("请重新选择方式");break;
				}
				
			}
			
		}
	}
}
void change_stdinfo_name()//按照学生姓名修改信息
{
	char change_n[20]={};
	printf("请输入要x修改的学生姓名\n");
	scanf("%s",change_n);
	for(int i=0;i<Total;i++)
	{	
		if(strcmp(change_n,(sp+i)->name)==0)
		{
			printf("学号    性别 姓名   语文 数学 英语 密码 是否冻结 \n----\n");
			printf("%s %c %s %d %d %d %s %c\n",(sp+i)->id,(sp+i)->gender,(sp+i)->name,(sp+i)->chinese,(sp+i)->math,(sp+i)->english,(sp+i)->password,(sp+i)->is_locked);
			
			int ch=0;
			
			while(ch<1||ch>6)
			{
				printf("请选择要修改的内容\n1、姓名\n2、性别\n3、语文成绩\n4、数学成绩\n5、英语成绩\n6、是否离校\n");
				scanf("%d",&ch);
				switch(ch)
				{
					case 1:change_name(&(sp+i)->name);break;
					case 2:change_gender(&(sp+i)->gender);break;
					case 3:change_chinese(&(sp+i)->chinese);break;
					case 4:change_math(&(sp+i)->math);break;
					case 5:change_english(&(sp+i)->english);break;
					case 6:change_isout(&(sp+i)->is_out);break;
					default:puts("请重新选择方式");break;
				}
				
			}
			
		}
	}
}



//方法 解锁
void unlock_std()
{
	char unlock_id[9]={};
	printf("请输入要解锁的学生学号\n");
	scanf("%s",unlock_id);
	for(int i=0;i<Total;i++)
	{	
		if(strcmp(unlock_id,(sp+i)->id)==0)
		{
			(sp+i)->is_locked='0';
			break;
		}
	}
}


//方法 重置学生密码（学生id）
void reset_password()
{
	char reset_id[9]={};
	printf("请输入要重置密码的学生学号\n");
	scanf("%s",reset_id);
	for(int i=0;i<Total;i++)
	{	
		if(strcmp(reset_id,(sp+i)->id)==0)
		{
			strcpy((sp+i)->password,"000");
			break;
		}
	}
}



//方法 显示所有在校学生
void list_all_std()
{
	printf("学号    性别 姓名   语文 数学 英语 密码 是否冻结 \n----\n");
	for(int i=0;i<Total;i++)
	{	
		if((sp+i)->is_out=='0')
		printf("%s %c %s %d %d %d %s %c\n",(sp+i)->id,(sp+i)->gender,(sp+i)->name,(sp+i)->chinese,(sp+i)->math,(sp+i)->english,(sp+i)->password,(sp+i)->is_locked);
	}
}
//方法 显示退学学生
void list_out_std()
{
	printf("学号    性别 姓名   语文 数学 英语  密码\n----\n");
	for(int i=0;i<Total;i++)
	{	
		if((sp+i)->is_out=='1')
		printf("%8s %8c %8s  %8d  %8d  %8d  %s\n",(sp+i)->id,(sp+i)->gender,(sp+i)->name,(sp+i)->chinese,(sp+i)->math,(sp+i)->english,(sp+i)->password);
	}
}


