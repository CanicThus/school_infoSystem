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
   // printf("%s\n",temData);
    int i;
    for(int i=0;i<33;i++)
    {
    	buf[i]=0;
    }
   // printf("%s\n",buf);
    
    char tmp[3]={};
    MD5(temData,strlen(data),md);
    for (i = 0; i < 16; i++){
        sprintf(tmp,"%2.2x",md[i]);
        strcat(buf,tmp);
    }
    //printf("%s\n",buf);
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
		fscanf(teacher_info_rp,"%s %s %s %c",(tp+i)->id,(tp+i)->name,(tp+i)->gender,&(tp+i)->is_out);
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
		printf("id=%s name=%s password=%s\ngender=%s is_out=%c is_locked=%c\n",(tp+i)->id,(tp+i)->name,(tp+i)->password,(tp+i)->gender,(tp+i)->is_out,(tp+i)->is_locked);	
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
	sp=malloc(sizeof(Student)*Total);
	for(int i=0;i<Total;i++)
	{
		fscanf(students_info_rp,"%s %s %s %c",(sp+i)->id,(sp+i)->name,(sp+i)->gender,&(sp+i)->is_out);	
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
	
	fclose(students_account_rp);
	fclose(students_score_rp);
	fclose(students_info_rp);
}

//读入总人数
void init_Total_txt(void)
{
	/*FILE* total_num_rp=fopen("total_num.txt","r");
	//相对路径无法实现
//	FILE* total_num_rp=fopen("src/total_num.txt","r");
	if(total_num_rp==NULL) perror("fopen: ");
	fscanf(total_num_rp,"%d %d",&Total,&Total_T);
	//printf("total=%d total_T=%d\n",Total,Total_T);
	fclose(total_num_rp);*/
	FILE *students_info_rp=fopen("students_info.txt","r");
	FILE* teacher_account_rp=fopen("teacher_account.txt","r");
	if(students_info_rp==NULL)perror("fopen students_info.txt:");
	Total=count_Total(students_info_rp);//fclose in count_Total
	printf("Total=%d\n",Total);
	Total_T=count_Total(teacher_account_rp);//fclose in count_Total
	printf("Total_T=%d\n",Total_T);
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
	//printf("%s\n1\n",oldkey);
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
			anykey_continue();
			
		}
		else
		{
			printf("密码与第一次输入的不一致\n");
			anykey_continue();
			return;
		}

		return;
	}
	else
	{
		puts("密码输入错误!");
		anykey_continue();
		return;
	}
	return;
}


char* generate_id(char* ID)//ID是全局变量id  老师和学生的要分开写两个全局变量，分别从0号开始
{	
		
	int id=0;
	id=atoi(ID);
	id++;
	sprintf(ID,"%08d",id);
	return ID;
}
//判断是否是第一次登录，初始密码是否为000
bool is_first_login(char* password)
{
	//printf("%s\n",password);
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






char* generate_id_t(char* ID)//用于生成教师的ID 
{	
		
	int id=0;
	char tem_ID[10]="T";//需要T开头
	id=atoi(ID);
	id++;
	sprintf(ID,"%08d",id);
	strcat(tem_ID,ID);
	strcpy(ID,tem_ID);
	return ID;
}
//判断是否是第一次登录，初始密码是否为000
bool is_first_login_t(char* password)
{
	//printf("%s\n",password);
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
			while(1)
			{
				fgets(ch_name,20,stdin);
				discard_n(ch_name);
				if(strlen(ch_name)<19&&strlen(ch_name)>0)
				{
					break;
				}
				else
				{
					printf("输入名字过长或过短，请重新输入\n");
				}
			}
			strcpy(p,ch_name);
			printf("修改成功\n");
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
	char ch_gender[128]={};
	int a=0;
	printf("1、修改性别\n2、取消修改\n");
	
	while(a<1||a>2)
	{	
		scanf("%d",&a);
		if(a==1)
		{
			printf("请输入性别\n");
			while(1)
			{
				fgets(ch_gender,5,stdin);
				discard_n(ch_gender);
				if(strcmp(ch_gender,"女")==0||strcmp(ch_gender,"男")==0)
				{
					break;
				}
				else
				{
					printf("输入性别错误，请重新输入\n");
				}
			}
			
			strcpy(p,ch_gender);
			printf("修改成功\n");
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
			printf("修改成功\n");
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
			printf("修改成功\n");
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

bool discard_n(char* arr)//用于丢弃字符串中最后一个回车,并清理输入缓冲区
{
	if(arr[strlen(arr)-1]=='\n')
	{
		arr[strlen(arr)-1]='\0';
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		return true;
	}
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	return false;	
}

int count_Total(FILE* fp)//用于计数文件中的学生数量
{
	int flag = 0, count = 0;
	if(fp  == NULL)
	return -1;
	while(!feof(fp))
	{
		flag = fgetc(fp);
		if(flag == '\n')
		{

			count++;
		}
	}
	Total = count ; //加上最后一行
	printf("row = %d\n", Total);
	fclose(fp);
	return Total;
}







