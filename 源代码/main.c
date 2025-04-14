#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/fb.h>
#include <linux/un.h>
#include <linux/input.h>


#include <arpa/inet.h>
#include <netinet/in.h>

#include<pthread.h>

#include "sqlite3.h"
#include "rfid.h"
#include "lcd.h"

#define GREEN				0x22b14c
#define WHITE				0xffffff
#define RED					0xff0000
#define YELLOW				0xffff00
#define BLUE				0x99d9ea

void menu();

int room_flag=0;//选择的房间号
int days_flag=0;//选择的天数
int check_flag=1;//是否确认 1为否 0为是
int put_flag = 0;
int back_flag=0;//返回标记 是否返回 0为否 1为是
int passwd_flag=0;//输入的密码
//int user_flag = 0;//输入的账号
int cs_flag = 0;//重输标记
int i = 0;


char cur_time[20];//当前时间

sqlite3 *db = NULL;//数据库
char SQL[300];//SQL语句

char card_id[6][50];//卡号
char room_id[6][50];//房间号
char room_date[6][50];//入住日期
char room_days[6][50];//入住天数
int room_num=0;//入住房间数
//char name[4] = "1234";//用户号
int pass[4] = {4,3,2,1};
//char name_input[4];//存放输入号
int pass_input[100];//存放输入密码

//标记初始化
void flag_init()
{
	room_flag=0;//选择的房间号
	days_flag=0;//选择的天数
	check_flag=1;//是否确认 1为否 0为是
	back_flag=0;//返回标记 是否返回 0为否 1为是
}


//获取当前时间
char *get_time()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	uint64_t sec=tv.tv_sec;
	uint64_t min=tv.tv_sec/60;
	struct tm cur_tm;//保存转换后的时间结果
	localtime_r((time_t*)&sec,&cur_tm);
	snprintf(cur_time,20,"%d-%02d-%02d %02d:%02d:%02d",cur_tm.tm_year+1900,cur_tm.tm_mon+1,cur_tm.tm_mday,cur_tm.tm_hour,cur_tm.tm_min,cur_tm.tm_sec);
	return cur_time;
}


//选择入住房间
char *select_room()
{
	switch(room_flag)
	{
		case 201:
			return "201";
		case 202:
			return "202";
		case 203:
			return "203";
		case 204:
			return "204";
		case 205:
			return "205";
		case 206:
			return "206";
	}
}


//选择入住时长
char *select_days()
{
	switch(days_flag)
	{
		case 1:
			return "1";
		case 2:
			return "2";
		case 3:
			return "3";
		case 4:
			return "4";
		case 5:
			return "5";
		case 6:
			return "6";
		case 7:
			return "7";
		case 8:
			return "8";
		case 9:
			return "9";
		case 10:
			return "10";
		case 11:
			return "11";
		case 12:
			return "12";
		case 13:
			return "13";
		case 14:
			return "14";
		case 15:
			return "15";
		case 16:
			return "16";
		case 17:
			return "17";
		case 18:
			return "18";
		case 19:
			return "19";
		case 20:
			return "20";
		case 21:
			return "21";
		case 22:
			return "22";
		case 23:
			return "23";
		case 24:
			return "24";
		case 25:
			return "25";
		case 26:
			return "26";
		case 27:
			return "27";
		case 28:
			return "28";
		case 29:
			return "29";
		case 30:
			return "30";
		case 31:
			return "31";
	}
}




//执行SQL语句
void Sqlite3_exec(sqlite3 *db, const char *sql, 
		int (*callback)(void *, int, char **, char **), void *arg)
{
	char *errmsg;
	if(sqlite3_exec(db, sql, callback, arg, &errmsg) != SQLITE_OK)
	{
		printf("执行[%s]失败: %s\n", sql, errmsg);
	}
}


// 每当查询到一条记录，就会自动调用一次以下回调函数
// arg: 这是用户自定义参数 i = -1
// col_num : 当前记录的列数
// col_val : 每一列的值
// col_name: 每一列的名称
int callback(void *arg, int col_num, char **col_val, char **col_name)
{
	int i;
	if(arg != NULL)
	{
		(*(int *)arg) = room_num;
	}

	else
	{
		for(i=0; i<col_num; i++)
		{
			printf("%s\t", col_val[i]);
		}
		printf("\n");
	}
	
	strcpy(card_id[room_num],col_val[0]);
	strcpy(room_id[room_num],col_val[1]);
	strcpy(room_date[room_num],col_val[2]);
	strcpy(room_days[room_num],col_val[3]);
	room_num++;
	
	return 0; // 返回0，代表可以继续回调；否则，终止该函数
}
		
		
		
//打开/创建数据库
void db_init()
{

	int ret = sqlite3_open_v2("hotel.db", &db,
			SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

	if(ret != SQLITE_OK)
	{
		printf("[%d] error: %s\n", __LINE__, sqlite3_errmsg(db));
		exit(0);
	}
	//创建表格
	bzero(SQL, 300);
	snprintf(SQL, 300, "%s", "CREATE TABLE IF NOT EXISTS carinfo(卡号	TEXT,"
							       "房间号 TEXT,"
								   "入住日期 TEXT,"
							       "入住时长 TEXT);");
	Sqlite3_exec(db,  /*数据库文件指针*/
		     SQL, /*要执行的SQL语句*/
		     NULL,/*对执行SQL后得到的记录进行处理的回调函数，一般只对SELECT语句有效*/
		     NULL/*以上回调函数的第一个参数*/);
}
//子线程实现通过触摸屏控制功能
void *func_ts4(void *arg)
{
	pthread_detach(pthread_self());
	int x,y;
	while(1)
	{
		get_xy(&x,&y);
		//0
		if(x>96&&x<182 && y>133&&y<295)
		{
			printf("0\n");	
			passwd_flag = 0;
			put_flag=1;
			//sleep(2);
		
		}
		//1
		if(x>300&&x<390 && y>133&&y<295)
		{
			printf("1\n");	
			passwd_flag = 1;
			put_flag=1;
		}
		//2
		if(x>490&&x<576 && y>133&&y<295)
		{
			printf("2\n");
			passwd_flag = 2;
			put_flag=1;
		}
		//3
		if(x>640&&x<707 && y>133&&y<295)
		{
			printf("3\n");
			passwd_flag = 3;
			put_flag=1;
			sleep(3);
		}
		//4
		if(x>800&&x<850 && y>133&&y<295)
		{
			printf("4\n");
			passwd_flag = 4;
			put_flag=1;
		}

		//5
		if(x>96&&x<182 && y>340&&y<480)
		{
			printf("5\n");
			passwd_flag = 5;
			put_flag=1;
		}

		//6
		if(x>300&&x<390 && y>340&&y<480)
		{
			printf("6\n");
			passwd_flag = 6;
			put_flag=1;
		}
		//7
		if(x>490&&x<576 &&  y>340&&y<480)
		{
			printf("7\n");
			passwd_flag = 7;
			put_flag=1;
		}
		//8
		if(x>621&&x<707 && y>340&&y<480)
		{	
				printf("8\n");
				passwd_flag = 8;
				put_flag=1;
			
		}
		//9
		if(x>800&&x<850 && y>340&&y<480)
		{
				printf("9\n");
				passwd_flag = 9;
				put_flag=1;
			
		}

		//确认
		if(x>86 && x<150 && y>15 && y<100)
		{
			printf("ensure\n");
			put_flag=1;
			passwd_flag = -1;
			if(pass[0]== pass_input[0]&&pass[1]==pass_input[1]&&pass[2]==pass_input[2]&&pass[3]==pass_input[3])
			{if (i ==5) break;}
			
		}
		//

	}
		pthread_exit(NULL);

	}

//登录
void login()
{	
	lcd_draw_bmp(0,0,"/project/test/bg/new_mima.bmp");
	//创建子线程
	//pthread_t tid;	
	//pthread_create(&tid,NULL,func_ts4,NULL);
	while(1)
	{
	//创建子线程
	pthread_t tid;	
	pthread_create(&tid,NULL,func_ts4,NULL);
		for(i;i<100; )
		{	
			if(put_flag!= 0) 
			{
				
				pass_input[i] = passwd_flag;
				put_flag = 0;
				i++;

				if(passwd_flag == -1)//是否按下确认键
				{
					if(pass[0]== pass_input[0]&&pass[1]==pass_input[1]&&pass[2]==pass_input[2]&&pass[3]==pass_input[3])//验证输入的密码是否正确
					{
						if(i==5)//验证密码长度
						{
						sleep(1);
						menu();
						}
						else 
						{
						lcd_draw_bmp(150,80,"/project/test/bg/pderror.bmp");
						i = 0;
						put_flag= 0;
						passwd_flag = -2;
						sleep(1);
						lcd_draw_bmp(0,0,"/project/test/bg/new_mima.bmp");
						}
					}
					else //输入的密码错误，弹出提醒1秒，重新输入
					{
						lcd_draw_bmp(150,80,"/project/test/bg/pderror.bmp");
						i = 0;
						put_flag= 0;
						passwd_flag = -2;
						sleep(1);
						lcd_draw_bmp(0,0,"/project/test/bg/new_mima.bmp");
					}
				}
			}
			
		}
		//sleep(2);
		

	}
	
	
	//sleep(2);

}

//改变房间颜色
void change_room_color(int flag,int color)
{
	switch(flag)
	{
		case 201:
			change_color(80,58,183,218,GREEN,color);
			break;
		case 202:
			change_color(80,267,183,428,GREEN,color);
			break;
		case 203:
			change_color(238,58,341,218,GREEN,color);
			break;
		case 204:
			change_color(238,267,341,428,GREEN,color);
			break;
		case 205:
			change_color(400,58,505,218,GREEN,color);
			break;
		case 206:
			change_color(400,267,505,428,GREEN,color);
			break;
		default:
			change_color(80,58,183,218,color,GREEN);
			change_color(80,267,183,428,color,GREEN);
			change_color(238,58,341,218,color,GREEN);
			change_color(238,267,341,428,color,GREEN);
			change_color(400,58,505,218,color,GREEN);
			change_color(400,267,505,428,color,GREEN);
			break;
	}	
}
//改变天数颜色
void change_days_color(int flag)
{
	switch(flag)
	{
		case 1:
			change_color(581,103,735,173,WHITE,RED);
			break;
		case 3:
			change_color(581,199,735,269,WHITE,RED);
			break;
		case 5:
			change_color(581,295,735,365,WHITE,RED);
			break;
		default:
			change_color(581,103,735,173,RED,WHITE);
			change_color(581,199,735,269,RED,WHITE);
			change_color(581,295,735,365,RED,WHITE);
			break;
	}
}



//子线程实现通过触摸屏控制功能
void *func_ts(void *arg)
{
	pthread_detach(pthread_self());
	int x,y;
	while(1)
	{
		get_xy(&x,&y);
		//201
		if(x>80&&x<183 && y>58&&y<218)
		{
			if(room_flag==201)
			{
				room_flag=0;
			}
			else
			{
				room_flag=201;
			}
		}
		//202
		if(x>80&&x<183 && y>267&&y<428)
		{
			if(room_flag==202)
			{
				room_flag=0;
			}
			else
			{
				room_flag=202;
			}
		}
		//203
		if(x>288&&x<388 && y>58&&y<218)
		{
			if(room_flag==203)
			{
				room_flag=0;
			}
			else
			{
				room_flag=203;
			}
		}
		//204
		if(x>288&&x<388 && y>267&&y<428)
		{
			if(room_flag==204)
			{
				room_flag=0;
			}
			else
			{
				room_flag=204;
			}
		}
		//205
		if(x>460&&x<560 && y>58&&y<218)
		{
			if(room_flag==205)
			{
				room_flag=0;
			}
			else
			{
				room_flag=205;
			}
		}
		//206
		if(x>460&&x<560 && y>267&&y<428)
		{
			if(room_flag==206)
			{
				room_flag=0;
			}
			else
			{
				room_flag=206;
			}
		}
		//1 day
		if(x>730&&x<800 && y>103&&y<173)
		{
			if(days_flag==1)
			{
				days_flag=0;
			}
			else
			{
				days_flag=1;
			}
		}
		//3 days
		if(x>730&&x<800 && y>220&&y<290)
		{
			if(days_flag==3)
			{
				days_flag=0;
			}
			else
			{
				days_flag=3;
			}
		}
		//5 days
		if(x>730&&x<800 && y>350&&y<400)
		{
			if(days_flag==5)
			{
				days_flag=0;
			}
			else
			{
				days_flag=5;
			}
		}
		//确认
		if(x>740&&x<820 && y>460&&y<520)
		{
			if(room_flag!=0 && days_flag!=0)
			{
				check_flag=0;
				break;
			}
		}
		//返回
		if(x>15 && x<78 && y>15 && y<100)
		{
			check_flag=0;
			back_flag=1;
			break;
		}
	}
	pthread_exit(NULL);
}

//入住
void check_in()
{
	lcd_draw_bmp(0,0,"/project/test/bg/check_iin.bmp");
	//创建子线程
	pthread_t tid;	
	pthread_create(&tid,NULL,func_ts,NULL);
	//查询已入住的房间
	room_num=0;
	bzero(SQL, 300);
	snprintf(SQL, 300, "SELECT * FROM carinfo;");
	Sqlite3_exec(db, SQL, callback, NULL);
	//显示已入住的房间
	int i,j;
	for(i=0;i<room_num;i++)
	{
		j=atoi(room_id[i]);
		change_room_color(j,RED);
	}
	//选择房间和天数
	while(check_flag)
	{
		change_room_color(room_flag,YELLOW);
		change_days_color(days_flag);
	}
	//确认刷卡,当返回标记不等于1时
	if(back_flag!=1)
	{
		lcd_draw_bmp(150,80,"/project/test/bg/swip.bmp");
		//读卡号并写入数据库
		int card=rfid();
		sleep(2);
		//查询是否已入住
		room_num=0;
		int i=-1;
		bzero(SQL, 300);
		snprintf(SQL, 300, "SELECT * FROM carinfo WHERE 卡号='%x';", card);
		Sqlite3_exec(db, SQL, callback, (void *)&i);
		if(i!=-1)
		{
			lcd_draw_bmp(150,80,"/project/test/bg/yes.bmp");
			sleep(2);
		}
		else
		{
			bzero(SQL, 300);
			snprintf(SQL, 300, "INSERT INTO carinfo VALUES('%x', '%s' , '%s', '%s');",
									card, select_room(), get_time(), select_days());						
			Sqlite3_exec(db, SQL, NULL, NULL);
			//入住成功并返回主界面
			lcd_draw_bmp(150,80,"/project/test/bg/check_in_ok.bmp");
			sleep(2);
		}
		menu();
	}
	else
	{
		menu();
	}
}

//改变天数颜色
void days_up_color(int flag)
{
	switch(flag)
	{
		case 1:
			change_color(96,133,182,295,BLUE,YELLOW);
			break;
		case 2:
			change_color(227,133,314,295,BLUE,YELLOW);
			break;
		case 3:
			change_color(359,133,445,295,BLUE,YELLOW);
			break;
		case 4:
			change_color(490,133,576,295,BLUE,YELLOW);
			break;
		case 5:
			change_color(621,133,707,295,BLUE,YELLOW);
			break;
		case 7:
			change_color(96,315,182,480,BLUE,YELLOW);
			break;
		case 10:
			change_color(227,315,314,480,BLUE,YELLOW);
			break;
		case 30:
			change_color(359,315,445,480,BLUE,YELLOW);
			break;
		default:
			change_color(96,133,182,295,YELLOW,BLUE);
			change_color(227,133,314,295,YELLOW,BLUE);
			change_color(359,133,445,295,YELLOW,BLUE);
			change_color(490,133,576,295,YELLOW,BLUE);
			change_color(621,133,707,295,YELLOW,BLUE);
			change_color(96,315,182,480,YELLOW,BLUE);
			change_color(227,315,314,480,YELLOW,BLUE);
			change_color(359,315,445,480,YELLOW,BLUE);
			break;
	}
}

//子线程实现通过触摸屏控制功能
void *func_ts2(void *arg)
{
	pthread_detach(pthread_self());
	int x,y;
	while(1)
	{
		get_xy(&x,&y);
		//1 day
		if(x>96&&x<182 && y>133&&y<295)
		{
			if(days_flag==1)
			{
				days_flag=0;
			}
			else
			{
				days_flag=1;
			}
		}
		//2 days
		if(x>300&&x<390 && y>133&&y<295)
		{
			if(days_flag==2)
			{
				days_flag=0;
			}
			else
			{
				days_flag=2;
			}
		}
		//3 days(359,445)
		if(x>490&&x<576 && y>133&&y<295)
		{
			if(days_flag==3)
			{
				days_flag=0;
			}
			else
			{
				days_flag=3;
			}
		}
		//4 days(490,576)
		if(x>621&&x<707 && y>133&&y<295)
		{
			if(days_flag==4)
			{
				days_flag=0;
			}
			else
			{
				days_flag=4;
			}
		}
		//5 days(621,707)
		if(x>775&&x<800 && y>133&&y<295)
		{
			if(days_flag==5)
			{
				days_flag=0;
			}
			else
			{
				days_flag=5;
			}
		}

		//7 days(621,707)
		if(x>96&&x<182 && y>340&&y<480)
		{
			if(days_flag==7)
			{
				days_flag=0;
			}
			else
			{
				days_flag=7;
			}
		}

		//10 days(621,707)
		if(x>300&&x<390 && y>340&&y<480)
		{
			if(days_flag==10)
			{
				days_flag=0;
			}
			else
			{
				days_flag=10;
			}
		}
		//30days
		if(x>490&&x<576 &&  y>340&&y<480)
		{
			if(days_flag==30)
			{
				days_flag=0;
			}
			else
			{
				days_flag=30;
			}
		}
		//确认(558,720)
		if(x>740&&x<820 && y>400&&y<470)
		{
			if(days_flag!=0)
			{
				check_flag=0;
				break;
			}
		}
		//返回
		if(x>78 && x<180 && y>42 && y<90)
		{
			check_flag=0;
			back_flag=1;
			break;
		}
	}
	pthread_exit(NULL);
}



//续房
void days_up()
{
	lcd_draw_bmp(0,0,"/project/test/bg/new_days_up.bmp");
	//创建子线程
	pthread_t tid2;	
	pthread_create(&tid2,NULL,func_ts2,NULL);
	//选择房间和天数
	while(check_flag)
	{
		days_up_color(days_flag);

	}
	if(check_flag==0&&back_flag!=1)
	{
		lcd_draw_bmp(150,80,"/project/test/bg/swip.bmp");
		//读卡号
		int card=rfid();
		sleep(2);
		//查询是否已入住
		int i=-1;
		room_num=0;
		bzero(SQL, 300);
		snprintf(SQL, 300, "SELECT * FROM carinfo WHERE 卡号='%x';", card);
		Sqlite3_exec(db, SQL, callback, (void *)&i);
		int now = atoi(room_days[i]);
		int add = days_flag;
		int new_days = now + add;
		if(i!=-1)
		{
			bzero(SQL, 300);
			if(new_days<=61)
			{
			snprintf(SQL, 300, "UPDATE carinfo SET 入住时长=%d WHERE 卡号='%x';",(atoi(room_days[i])+days_flag), card);
			Sqlite3_exec(db, SQL, NULL, NULL );
			lcd_draw_bmp(150,80,"/project/test/bg/days_up_ok.bmp");
			sleep(2);
			}
			else
			{
				lcd_draw_bmp(150,80,"/project/test/bg/super.bmp");
				sleep(2);
			}
		}
		else
		{
			lcd_draw_bmp(150,80,"/project/test/bg/no.bmp");
			sleep(2);
		}
		menu();
	}
	else
	{
		menu();
	} 
}

//查询
void check_days()
{
	char check_buf1[50]={0};
	char check_buf2[50]={0};
	lcd_draw_bmp(0,0,"/project/test/bg/bg.bmp");
	lcd_draw_bmp(150,80,"/project/test/bg/swip.bmp");
	int card=rfid();
	sleep(2);
	//查询是否为入住卡
	room_num=0;
	int i=-1;
	bzero(SQL, 300);
	snprintf(SQL, 300, "SELECT * FROM carinfo WHERE 卡号='%x';", card);
	Sqlite3_exec(db, SQL, callback, (void *)&i);
	if(i!=-1)
	{
		sprintf(check_buf1, "/project/test/bg/%s.bmp",room_id[i]);
		sprintf(check_buf2, "/project/test/bg/%s.bmp",room_days[i]);
		lcd_draw_bmp(150,80,"/project/test/bg/check_days.bmp");
		lcd_draw_bmp(400,130,check_buf1);
		lcd_draw_bmp(400,250,check_buf2);
		sleep(2);
	}
	else
	{
		lcd_draw_bmp(150,80,"/project/test/bg/no.bmp");
		sleep(2);
	}
	menu();
}



//退房
void check_out()
{
	lcd_draw_bmp(0,0,"/project/test/bg/bg.bmp");
	lcd_draw_bmp(150,80,"/project/test/bg/swip.bmp");
	int card=rfid();
	sleep(2);
	//查询是否为入住卡
	room_num=0;
	int i=-1;
	bzero(SQL, 300);
	snprintf(SQL, 300, "SELECT * FROM carinfo WHERE 卡号='%x';", card);
	Sqlite3_exec(db, SQL, callback, (void *)&i);
	if(i!=-1)
	{
		bzero(SQL, 300);
		snprintf(SQL, 300, "DELETE FROM carinfo WHERE 卡号='%x';", card);
		Sqlite3_exec(db, SQL, NULL, NULL);
		lcd_draw_bmp(150,80,"/project/test/bg/check_out_ok.bmp");
		sleep(2);
	}
	else
	{
		lcd_draw_bmp(150,80,"/project/test/bg/no.bmp");
		sleep(2);
	}
	menu();
}
//子线程实现通过触摸屏控制功能
void *func_ts3(void *arg)
{
	pthread_detach(pthread_self());
	int x,y;
	while(1)
	{
		get_xy(&x,&y);
		//201
		if(x>80&&x<183 && y>58&&y<218)
		{
			if(room_flag==201)
			{
				room_flag=0;
			}
			else
			{
				room_flag=201;
			}
		}
		//202
		if(x>80&&x<183 && y>267&&y<428)
		{
			if(room_flag==202)
			{
				room_flag=0;
			}
			else
			{
				room_flag=202;
			}
		}
		//203
		if(x>288&&x<388 && y>58&&y<218)
		{
			if(room_flag==203)
			{
				room_flag=0;
			}
			else
			{
				room_flag=203;
			}
		}
		//204
		if(x>288&&x<388 && y>267&&y<428)
		{
			if(room_flag==204)
			{
				room_flag=0;
			}
			else
			{
				room_flag=204;
			}
		}
		//205
		if(x>460&&x<560 && y>58&&y<218)
		{
			if(room_flag==205)
			{
				room_flag=0;
			}
			else
			{
				room_flag=205;
			}
		}
		//206
		if(x>460&&x<560 && y>267&&y<428)
		{
			if(room_flag==206)
			{
				room_flag=0;
			}
			else
			{
				room_flag=206;
			}
		}
		
		//确认
		if(x > 730 && x < 800 && y > 220 && y < 290)
		{
			if(room_flag!=0)
			{
				check_flag=0;
				break;
			}
		}
		//返回
		if(x>15 && x<78 && y>15 && y<100)
		{
			check_flag=0;
			back_flag=1;
			break;
		}
	}
	pthread_exit(NULL);
}

//换房
void change_room()
{	
	int new_room = -1;
	lcd_draw_bmp(0,0,"/project/test/bg/change_room.bmp");
	//创建子线程
	pthread_t tid;	
	pthread_create(&tid,NULL,func_ts3,NULL);
	//查询已入住的房间
	room_num=0;
	bzero(SQL, 300);
	snprintf(SQL, 300, "SELECT * FROM carinfo;");
	Sqlite3_exec(db, SQL, callback, NULL);
	//显示已入住的房间
	int i,j;
	for(i=0;i<room_num;i++)
	{
		j=atoi(room_id[i]);
		change_room_color(j,RED);
	}
	//选择房间
	while(check_flag)
	{
		new_room = room_flag;;
		change_room_color(room_flag,YELLOW);
		
	}
	//确认刷卡,当返回标记不等于1时
	if(back_flag!=1)
	{
		lcd_draw_bmp(150,80,"/project/test/bg/swip.bmp");
		//读卡号并写入数据库
		int card=rfid();
		sleep(2);
		//查询是否已入住
		int i=-1;
		room_num=0;
		bzero(SQL, 300);
		snprintf(SQL, 300, "SELECT * FROM carinfo WHERE 卡号='%x';", card);
		Sqlite3_exec(db, SQL, callback, (void *)&i);
		if(i!=-1)
		
          { // 更新数据库中的房间信息
            bzero(SQL, 300);
            snprintf(SQL, 300, "UPDATE carinfo SET 房间号='%d' WHERE 卡号='%x';", new_room, card);
            Sqlite3_exec(db, SQL, NULL, NULL);

            // 更换成功并返回主界面
            lcd_draw_bmp(150, 80, "/project/test/bg/change_yes.bmp");
            sleep(2);
		}
		else
	{
		lcd_draw_bmp(150,80,"/project/test/bg/no.bmp");
		sleep(2);
	}
		menu();
	}
	else
	{
		menu();
	}
}

void menu()
{
	flag_init();
	while(1)
	{
		lcd_draw_bmp(0,0,"/project/test/bg/new_main.bmp");
		int x,y;	
		get_xy(&x,&y);
		//入住
		if(x>96 && x<225 && y>137 && y<377)
		{
			check_in();
		}
		//续房
		if(x>261 && x<390 && y>137 && y<377)
		{
			days_up();
		}
		//查询
		if(x>425 && x<555 && y>137 && y<377)
		{
			check_days();
		}
		//退房
		if(x>590 && x<720 && y>137 && y<377)
		{
			check_out();
		}
		//换房
		if(x>800 && x<850 && y>137 && y<377)
		{
			change_room();
		}
		//退出系统
		if(x>694 && x<770 && y>15 && y<100)
		{
			close_lcd();
			break;
		}

	}
}






int main()
{	
	lcd_open("/dev/fb0");
	db_init();
	//passwd();
	login();
	//menu();

	return 0;
}






















