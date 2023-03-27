#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include"tools.h"
#include"system.h"
#include<openssl/md5.h>
#include<unistd.h>
#include <getch.h>
char buf[33]={};
void md5(char *data)
{
	unsigned char* temData =(unsigned char*)data;
    unsigned char md[16];
    printf("%s\n",temData);
    int i;
    for(int i=0;i<33;i++)
    {
    	buf[i]=0;
    }
    printf("%s\n",buf);
    
    char tmp[3]={};
    MD5(temData,strlen(data),md);
    for (i = 0; i < 16; i++){
        sprintf(tmp,"%2.2x",md[i]);
        strcat(buf,tmp);
    }
    printf("%s\n",buf);
}

void anykey_continue(void)
{
	puts("请按任意键继续...");

	stdin->_IO_read_ptr = stdin->_IO_read_end;
	getch();
}
void init_principle(void)
{
	// 导入校长帐号密码
	FILE* principle_account_rp=fopen("principle_account.txt","r");
	if(principle_account_rp==NULL)perror("fopen:");
	fscanf(principle_account_rp,"%s %s %c",principle.id,principle.password,&principle.attempt);
	fclose(principle_account_rp);
	//printf("%s %s %c",principle.id,principle.password,principle.attempt);
}

void init_teacher(void)
{
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
		fscanf(teacher_account_rp,"%s %s %c %c",temT.id,temT.password,&temT.is_locked,&temT.attempt);
		for(int j=0;j<Total_T;j++)
		{
			if(strcmp((tp+j)->id,temT.id)==0)
			{
				strcpy((tp+j)->password,temT.password);
				(tp+j)->is_locked=temT.is_locked;
				(tp+j)->attempt=temT.attempt;
			}
		}
	}
	//puts("22222222");
	//puts("333333");
	for(int i=0;i<Total_T;i++)
	{
		printf("id=%s name=%s password=%s\ngender=%c is_out=%c is_locked=%c\n",(tp+i)->id,(tp+i)->name,(tp+i)->password,(tp+i)->gender,(tp+i)->is_out,(tp+i)->is_locked);	
	}
	fclose(teacher_info_rp);
	fclose(teacher_account_rp);
	//puts("aaaaa");
}


void init_stu(void)
{
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
	
	//读入各科成绩MAX，MIN，AVG
	fscanf(scores_rp,"%d %d %d",&CH_max,&CH_min,&CH_avg);
	fscanf(scores_rp,"%d %d %d",&Math_max,&Math_min,&Math_avg);
	fscanf(scores_rp,"%d %d %d",&EN_max,&EN_min,&EN_avg);
		

	
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
	
	fclose(students_account_rp);
	fclose(students_score_rp);
	fclose(students_info_rp);
	fclose(scores_rp);
}

//读入总人数
void init_Total_txt(void)
{
	FILE* total_num_rp=fopen("total_num.txt","r");
	//相对路径无法实现
//	FILE* total_num_rp=fopen("src/total_num.txt","r");
	if(total_num_rp==NULL) perror("fopen: ");
	fscanf(total_num_rp,"%d %d",&Total,&Total_T);
	//printf("total=%d total_T=%d\n",Total,Total_T);
	fclose(total_num_rp);
}
	

//通过id定位堆内存的学生位置 RC
int find(char* id)
{
	for(int i=0;i<Total;i++)
	{
		if(strcmp(id,((sp+i)->id))==0)
		{
			return i;
		}
	}
	return -1;
}
//通过id定位堆内存的教师位置 RC
int find_t(char* id)
{
	for(int i=0;i<Total_T;i++)
	{
		if(strcmp(id,((tp+i)->id))==0)
		{
			return i;
		}
	}
	return -1;
}


void change_password_t(char* id)
{
	char newkey[20]={};
	char oldkey[20]={};
	char* temp_password= getpass("请输入旧密码: ");
	
	strcpy(oldkey,temp_password);
	md5(oldkey);
	printf("%s\n1\n",oldkey);
	if(0==strcmp(buf,(tp+find_t(id))->password))
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
			strcpy((tp+find_t(id))->password,buf);
			printf("密码修改成功!\n");
			return;
		}
		else
		{
			printf("密码与第一次输入的不一致\n");
			return;
		}
	}
	else
	{
		puts("密码输入错误!");
		return;
	}
	return;
}

void change_password_p(char* id)
{
	char newkey[20]={};
	char oldkey[20]={};
	char* temp_password= getpass("请输入旧密码: ");
	strcpy(oldkey,temp_password);
	printf("\n");
	md5(oldkey);
	if(0==strcmp(buf,principle.password))
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
			strcpy(principle.password,buf);
			printf("密码修改成功!\n");
		}
		else
		{
			printf("密码与第一次输入的不一致\n");
			return;
		}

		return;
	}
	else
	{
		puts("密码输入错误!");
		return;
	}
	return;
}


char* generate_id(char* ID)
{	
	while(1)
	{	int id=0;
		int a=0;
		for(int i=0;i<8;i++)
		{
			id=id*10+rand()%9+1;
		}
		sprintf(ID,"%d",id);

		for(int i =0;i<Total;i++)
		{	
			
			if(strcmp((sp+i)->id,ID)==0)
			{
				a=1;
				break;
			}
			if(strcmp((sp+i)->id,ID)!=0)
			{
				a=0;
			}
		}
		if(a==0)
		{
			break;
		}
	}
	return ID;
}
//判断是否是第一次登录，初始密码是否为000
bool is_first_login(char* password)
{
	printf("%s\n",password);
	md5("000");
	if(strcmp(password,buf)==0)
	{
		printf("第一次登录，请重置密码\n");
		return true;
	}
	return false;
}
//重置密码,赋值000
void rest_passward(char* id)
{
	if(strcmp(sp->id,id)==0)
	md5("000");
	strcpy(sp->password,buf);
}


//id是否解锁
bool unlock(char* id)
{
	if(strcmp(sp->id,id)==0)
	{
		sp->is_locked=false;
		return true;
	}
	return false;
}






char* generate_id_t(char* ID)
{	
	while(1)
	{	int id=0;
		int a=0;
		char ID_T[]="00000000";//定义一个初始数组存储随机产生的数字
		for(int i=0;i<8;i++)
		{
			id=id*10+rand()%9+1;
		}
		sprintf(ID_T,"%d",id);
		strcpy(ID,"T");//教师工号第一个位是T
		strcat(ID,ID_T);//在T的后面加上随机产生的数字
		for(int i =0;i<Total_T;i++)
		{	
			
			if(strcmp((tp+i)->id,ID)==0)
			{
				a=1;
				break;
			}
			if(strcmp((tp+i)->id,ID)!=0)
			{
				a=0;
			}
		}
		if(a==0)
		{
			break;
		}
	}
	return ID;
}
//判断是否是第一次登录，初始密码是否为000
bool is_first_login_t(char* password)
{
	printf("%s\n",password);
	md5("000");
	if(strcmp(password,buf)==0)
	{
		printf("第一次登录，请重置密码\n");
		return true;
	}
	return false;
}
//重置密码,赋值000
void rest_passward_t(char* id)
{
	if(strcmp(tp->id,id)==0)
	md5("000");
	strcpy(tp->password,buf);
}


//id是否解锁
bool unlock_t(char* id)
{
	if(strcmp(tp->id,id)==0)
	{
		tp->is_locked=false;
		return true;
	}
	return false;
}


void change_name(char *p)//修改学生姓名
{
	char ch_name[128]={};
	int a=0;
	printf("1、输入姓名\n2、取消修改\n");
	
	while(a<1||a>2)
	{
		scanf("%d",&a);
		if(a==1)
		{
			printf("输入姓名\n");
			stdin->_IO_read_ptr =stdin->_IO_read_end;
			scanf("%s",ch_name);
			strcpy(p,ch_name);
			return;
		}
		else if(a==2)
		{
			return;
		}
		else
		{
			printf("选择模式有误，请重新选择修改成绩或者退出\n");
			a=0;
		}
	}
}

void change_gender(char *p)
{
	char ch_gender='0';
	int a=0;
	printf("1、修改性别\n2、取消修改\n");
	
	while(a<1||a>2)
	{	
		scanf("%d",&a);
		if(a==1)
		{
			printf("请输入性别\n");
			scanf(" %c",&ch_gender);
			*p=ch_gender;
			return;
		}
		else if(a==2)
		{
			return;
		}
	}
	
}
void change_math(int *p)
{
	int ch_math=0;
	int a=0;//用于选择模式
	printf("1、修改数学成绩\n2、退出修改\n");
	
	while(a<1||a>2)
	{
		scanf("%d",&a);
		if(a==1)
		{
			while(1)
			{
				printf("输入数学成绩0~150\n");
				scanf("%d",&ch_math);
				if(ch_math>0&&ch_math<150)
				{
					break;	
				}
				else
				{
					printf("输入成绩有误，请重新输入0~150\n");
				}
			}
			
			*p=ch_math;
			return;
		}
		else if(a==2)
		{
			return;
		}
		else
		{
			printf("选择模式有误，请重新选择修改成绩或者退出\n");
			a=0;
		}
	}
}
void change_english(int *p)
{
	int ch_english=0;
	int a=0;
	printf("1、修改英语成绩\n2、取消修改\n");
	
	while(a<1||a>2)
	{
		scanf("%d",&a);
		if(a==1)
		{
			while(1)
			{
				printf("输入英语成绩0~150\n");
				scanf("%d",&ch_english);
				if(ch_english>0&&ch_english<150)
				{
					break;	
				}
				else
				{
					printf("输入成绩有误，请重新输入0~150\n");
				}
			}
			*p=ch_english;
			return;
		}
		else if(a==2)
		{
			return;
		}
		else
		{
			printf("选择模式有误，请重新选择修改成绩或者退出\n");
			a=0;
		}
	}
}
void change_chinese(int *p)
{
	int ch_chinese=0;
	int a=0;
	printf("1、修改语文成绩\n2、取消修改\n");
	
	while(a<1||a>2)
	{
		scanf("%d",&a);
		if(a==1)
		{
			while(1)
			{
				printf("输入语文成绩0~150\n");
				scanf("%d",&ch_chinese);
				if(ch_chinese>0&&ch_chinese<150)
				{
					break;	
				}
				else
				{
					printf("输入成绩有误，请重新输入0~150\n");
				}
			}
			*p=ch_chinese;
			return;
		}
		else if(a==2)
		{
			return;
		}
		else
		{
			printf("选择模式有误，请重新选择修改成绩或者退出\n");
			a=0;
		}
	}
}
void change_isout(char *p)
{
	char ch_isout='0';
	int a=0;
	printf("1、请输入是否离校\n2、取消修改\n");
	while(a<1||a>2)
	{
		scanf("%d",&a);
		if(a==1)
		{
			scanf(" %c",&ch_isout);
			*p=ch_isout;
			return;
		}
		else if(a==2)
		{
			return;
		}	
	}
	
}










