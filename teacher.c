#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<getch.h>
#include"tools.h"
#include"system.h"
#include"teacher.h"

Student *p=NULL;//添加学生时申请新的堆内存
static int total=0;//要导入的总人数
void add_std()//
{
	char ID[]="00000000000000";//用于传参，给一个学生学号
	printf("1、只输入一个学生\n2、从文件中批量导入\n");
	int com_a=0;//选择输入模式
	FILE* students_info_ap=fopen("students_info.txt","a");//追加写学生的基本信息
	FILE* students_account_ap=fopen("students_account.txt","a");//追加写学生的密码等信息
	FILE* students_score_ap=fopen("students_score.txt","a");//追加写学生的成绩，主要是把学号写进去，成绩初始值为0。

	scanf("%d",&com_a);
	
	//输入1，进入单人添加模式，每次添加都需要读取文件并保存文件，总人数+1
	if(com_a==1)
	{

		p=malloc(sizeof(Student));
		char arr[256]={};//用于输入学生姓名
		char sex_s='0';//用于输入学生性别
		strcpy(p->id,generate_id(ID));
		printf("请输入学生姓名\n");
		while(1)
		{	
			scanf("%s",arr);
			stdin->_IO_read_ptr = stdin->_IO_read_end;
			if(strlen(arr)<=19&&strlen(arr)>0)//限制学生名字长度（因为结构体中name数组为20）
			{
				break;
			}
			else
			{
				printf("输入错误，请重新输入姓名\n");
			}
		}
		
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		printf("请输入学生性别,F或者M\n");//限制性别输入，只能是F M （女 男）
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
		
		
		//堆内存中新学生信息
		strcpy(p->name,arr);
		md5("000");
		strcpy(p->password,buf);
		p->gender=sex_s;
		p->is_locked='0';
		p->is_out='0';
		p->attempt='0';
		p->chinese=0;
		p->math=0;
		p->english=0;

		fprintf(students_info_ap,"%s %s %c %c\n",p->id,p->name,p->gender,p->is_out);//写入基本信息到文件中
		fprintf(students_account_ap,"%s %s %c %c\n",p->id,p->password,p->is_locked,p->attempt);//写入初始密码到文件中
		fprintf(students_score_ap,"%s %d %d %d\n",p->id,p->chinese,p->math,p->english);//写入初始成绩到文件中
		printf("一名学生添加成功,以下为新学生信息\n");
		printf("id=%s gender=%c name=%s  is_locked=%c is_out=%c\n----\n",p->id,p->gender,p->name,p->is_locked,p->is_out);
		fclose(students_info_ap);
		fclose(students_score_ap);
		fclose(students_account_ap);
		
		Total++;//对人数进行更新
		FILE* total_num_wp=fopen("total_num.txt","w");
		if(total_num_wp==NULL) perror("fopen: ");
		fprintf(total_num_wp,"%d %d",Total,Total_T);
		fclose(total_num_wp);
		
	}

	//以下为添加多个学生
	//先打开新文件，读取依次读取新文件的每一行放到堆内存中，最后追加写入全部学生
	if(com_a==2)
	{
		FILE* stu_info_rp=fopen("stu_info.txt","r");

		
		printf("请输入要导入的总人数\n");
		scanf("%d",&total);		
		printf("%d个学生添加成功,以下为新学生信息\n",total);
		for(int i=0;i<total;i++)
		{
			p=malloc(sizeof(Student));	
			md5("000");
			strcpy(p->password,buf);
			p->is_locked='0';
			p->is_out='0';	
			p->chinese=0;
			p->math=0;
			p->english=0;
			p->attempt='0';
			fscanf(stu_info_rp,"%s %s %c %c",p->id,p->name,&p->gender,&p->is_out);	
			fprintf(students_info_ap,"%s %s %c %c\n",p->id,p->name,p->gender,p->is_out);
			fprintf(students_score_ap,"%s %d %d %d\n",p->id,p->chinese,p->math,p->english);//写入初始成绩到文件中
			fprintf(students_account_ap,"%s %s %c %c\n",p->id,p->password,p->is_locked,p->attempt);//写入初始密码到文件中
			printf("新写入的信息：id=%s gender=%c name=%s  password=%s is_locked=%c is_out=%c\n\n",p->id,p->gender,p->name,p->password,p->is_locked,p->is_out);
		}
		fclose(stu_info_rp);
 	   	fclose(students_info_ap);
 	   	fclose(students_score_ap);
 	   	fclose(students_account_ap);
 	   	
		FILE* total_num_wp=fopen("total_num.txt","w");
		Total+=total;
		if(total_num_wp==NULL) perror("fopen: ");
		fprintf(total_num_wp,"%d %d",Total,Total_T);
		fclose(total_num_wp);
		
	}
	anykey_continue();
	free(sp);
	free(tp);
	free(p);
	p=NULL;
	tp=NULL;
	sp=NULL;
	init();//添加完学生之后重新读取文件，更新堆内存中sp所指向的内容，用于之后显示学生也能显示新加的学生
}


//方法 删除学生，需要两次输入相同的学号
void del_std()
{
	char del_id[128]={};//第一次输入的学号
	char del_id1[128]={};//再次输入学号确定
	int del=0;//用于选择模式1 2 按学号删除或者退出删除功能
	
	while(del<1||del>2)
	{
		system("clear");
		int flag=0;//判断是否输入正确的标识
		printf("1、按学号删除学生\n2、退出\n");
		scanf("%d",&del);
		if(del==1)
		{
			printf("请输入要删除的学生学号\n");
			scanf("%s",del_id);
			for(int i=0;i<Total;i++)
			{	
				if(strcmp(del_id,(sp+i)->id)==0)
				{
					flag=1;
					break;
				}
			}
			if(flag==1)
			{
				printf("请再次输入要删除的学生学号\n");
				scanf("%s",del_id1);
			}
			else
			{
				printf("输入的学号不存在，请重新输入或退出\n");
				del=0;
				continue;
			}
			
			if(strcmp(del_id,del_id1)==0)
			{
				for(int i=0;i<Total;i++)
				{	
					if(strcmp(del_id,(sp+i)->id)==0)
					{
						(sp+i)->is_out='1';
						printf("已经删除学生:%s %s\n",(sp+i)->id,(sp+i)->name);
						anykey_continue();
						return;
					}
				}
			}
			else
			{
				printf("两次学号输入不一致，请重新输入或退出\n");
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
void search_std()//查找学生
{
	int search=0;//用于输入查找模式
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
	char std_id[128]={};//要查找到学生id
	int flag=0;//用于是否找到该学生到标志
	printf("请输入要查找的学生学号\n");
	scanf("%s",std_id);
	for(int i=0;i<Total;i++)
	{	
		if(strcmp(std_id,(sp+i)->id)==0)
		{
			flag=1;
			printf("学号     性别 姓名   语文 数学 英语 是否冻结 \n----\n");
			printf("%s %c   %s %d %d %d %c\n",(sp+i)->id,(sp+i)->gender,(sp+i)->name,(sp+i)->chinese,(sp+i)->math,(sp+i)->english,(sp+i)->is_locked);
			break;
		}
	}
	if(flag==0)
	{
		printf("不存在该学号\n");;
	}
	flag=0;
	anykey_continue();
}
void search_std_name()//按照学生姓名查找信息
{
	char std_name[20]={};
	int flag=0;//用于是否找到该学生到标志
	printf("请输入要查找的学生姓名\n");
	scanf("%s",std_name);
	for(int i=0;i<Total;i++)
	{	
		if(strcmp(std_name,(sp+i)->name)==0)
		{
			flag=1;
			printf("学号     性别 姓名   语文 数学 英语 是否冻结 \n----\n");
			printf("%s %c   %s %d %d %d %c\n",(sp+i)->id,(sp+i)->gender,(sp+i)->name,(sp+i)->chinese,(sp+i)->math,(sp+i)->english,(sp+i)->is_locked);
		}
	}
	if(flag==0)
	{
		printf("不存在该姓名\n");
	}
	flag=0;
	anykey_continue();
}



void change_stdinfo()//修改学生信息
{
	int change=0;//用于选择修改模式
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
	char change_id[128]={};
	printf("请输入要修改的学生学号\n");
	scanf("%s",change_id);
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	int flag=0;//用于判断是否找到该学生
	for(int i=0;i<Total;i++)
	{	
		if(strcmp(change_id,(sp+i)->id)==0)
		{
			flag=1;
			printf("学号    性别 姓名   语文 数学 英语 密码 是否冻结 \n----\n");
			printf("%s %c %s %d %d %d %s %c\n",(sp+i)->id,(sp+i)->gender,(sp+i)->name,(sp+i)->chinese,(sp+i)->math,(sp+i)->english,(sp+i)->password,(sp+i)->is_locked);
			
			int ch=0;
			
			while(ch<1||ch>6)
			{
				printf("请选择要修改的内容\n1、姓名\n2、性别\n3、语文成绩\n4、数学成绩\n5、英语成绩\n6、是否离校\n");
				scanf("%d",&ch);
				stdin->_IO_read_ptr = stdin->_IO_read_end;
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
	if(flag==0)
	{
		printf("不存在该id,无法修改\n");
	}
	flag=0;
	anykey_continue();
}
void change_stdinfo_name()//按照学生姓名修改信息
{
	char change_n[128]={};
	printf("请输入要修改的学生姓名\n");
	scanf("%s",change_n);
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	int flag=0;
	for(int i=0;i<Total;i++)
	{	
		if(strcmp(change_n,(sp+i)->name)==0)
		{
			flag=1;
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
	if(flag==0)
	{
		printf("不存在该姓名,无法修改\n");
	}
	flag=0;
	anykey_continue();
}

void add_grades()//实质是对已经有的学生进行成绩修改，寻找学号进行单个修改或者多个依次修改
{
	printf("1、只输入一个学生的成绩\n2、从文件中批量导入\n");
	int gra_a=0;//选择单个修改成绩或者多个修改成绩
	FILE* students_score_rp=fopen("students_score.txt","r");//读取已有的学生学号和成绩
	scanf("%d",&gra_a);
	if(gra_a==1)//单个修改成绩，然后再选择修改语文、数学或者英语
	{
		FILE* students_score_wp=fopen("students_score.txt","w");
		for(int i=0;i<Total;i++)
		{
		fscanf(students_score_rp,"%s %s %c %c",(sp+i)->id,(sp+i)->name,&(sp+i)->gender,&(sp+i)->is_out);	
		}
		char add_id[128]={};
		printf("请输入要修改成绩的学生学号\n");
		scanf("%s",add_id);
		int flag=0;
		for(int i=0;i<Total;i++)
		{	
			if(strcmp(add_id,(sp+i)->id)==0)
			{
				flag=1;
				printf("学号   姓名   语文 数学 英语 \n\n");
				printf("%s %s %d %d %d\n",(sp+i)->id,(sp+i)->name,(sp+i)->chinese,(sp+i)->math,(sp+i)->english);
			
				int ch=0;
			
				while(ch<1||ch>4)
				{
					printf("请选择要修改的内容\n1、语文\n2、数学\n3、英语\n4、退出\n");
					stdin->_IO_read_ptr =stdin->_IO_read_end;
					scanf("%d",&ch);
					switch(ch)
					{
						case 1:change_chinese(&(sp+i)->chinese);break;
						case 2:change_math(&(sp+i)->math);break;
						case 3:change_english(&(sp+i)->english);break;
						case 4:break;
						default:puts("请重新选择\n");break;
					}
				
				}
				//重新写入成绩到文件中
				fprintf(students_score_rp,"%s %d %d %d",(sp+i)->id,(sp+i)->chinese,(sp+i)->math,(sp+i)->english);
				printf("modified successfully\n");
			}
			
		}
		if(flag==0)
		{
			printf("不存在该学生,无法导入成绩\n");
		}
		flag=0;
		fclose(students_score_wp);
		anykey_continue();
		
	}

	//以下为添加多个学生
	//先打开新文件，读取依次读取新文件的每一行放到堆内存中，最后按照学号修改各科成绩
	if(gra_a==2)
	{
		FILE* add_score_rp=fopen("add_score.txt","r");
		FILE* students_score_wp=fopen("students_score.txt","w");
		printf("请输入要导入的总人数\n");
		scanf("%d",&total);		
		for(int i=0;i<total;i++)
		{
			p=malloc(sizeof(Student));
			fscanf(add_score_rp,"%s %d %d %d",p->id,&p->chinese,&p->math,&p->english);	//读取要导入的成绩
			for(int j=0;j<Total;j++)
			{
				if(strcmp((sp+j)->id,p->id)==0)
				{
					(sp+j)->math=p->chinese;
					(sp+j)->chinese=p->math;
					(sp+j)->english=p->english;
				}
			}
		}
		//重新写入成绩到文件中
		for(int i=0;i<Total;i++)
		{
			fprintf(students_score_wp,"%s %d %d %d\n",(sp+i)->id,(sp+i)->chinese,(sp+i)->math,(sp+i)->english);
		}
		
		fclose(students_score_wp);
		fclose(add_score_rp);

	}
	fclose(students_score_rp);
	free(sp);
	sp=NULL;
	init();
}

//方法 解锁
void unlock_std()
{
	char unlock_id[128]={};
	printf("请输入要解锁的学生学号\n");
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
	for(i=0;i<Total;i++)
	{	
		if(strcmp(unlock_id,(sp+i)->id)==0)
		{
			(sp+i)->is_locked='0';
			(sp+i)->attempt='0';
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


//方法 重置学生密码（学生id）
void reset_password()
{
	char reset_id[128]={};
	printf("请输入要重置密码的学生学号\n");
	scanf("%s",reset_id);
	int i=0;
	for(;i<Total;i++)
	{	
		if(strcmp(reset_id,(sp+i)->id)==0)
		{
			md5("000");
			strcpy((sp+i)->password,buf);
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

//方法 显示所有在校学生
void list_all_std()
{
	printf("学号     性别 姓名   语文 数学 英语 是否冻结 \n----\n");
	for(int i=0;i<Total;i++)
	{	
		if((sp+i)->is_out=='0')
		printf("%s %c   %s %d %d %d %c\n",(sp+i)->id,(sp+i)->gender,(sp+i)->name,(sp+i)->chinese,(sp+i)->math,(sp+i)->english,(sp+i)->is_locked);
	}
	anykey_continue();
}
//方法 显示退学学生
void list_out_std()
{
	printf("学号    性别 姓名   语文 数学 英语  \n----\n");
	for(int i=0;i<Total;i++)
	{	
		if((sp+i)->is_out=='1')
		printf("%8s %8c %8s  %8d  %8d  %8d \n",(sp+i)->id,(sp+i)->gender,(sp+i)->name,(sp+i)->chinese,(sp+i)->math,(sp+i)->english);
	}
	anykey_continue();
}


