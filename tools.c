#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include"tools.h"
#include"system.h"
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
	if(strcmp(password,"000")==0)
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
	strcpy(sp->password,"000");
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

