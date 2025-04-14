/*
 功能：lcd屏幕开启关闭
		显示bmp图片
		获取触摸屏坐标
		指定区域颜色切换
 */
#include <stdio.h>   	
#include <fcntl.h>			 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <linux/input.h>

#include "lcd.h"

static char g_color_buf[FB_SIZE]={0};


static int  g_fb_fd;
static int *g_pfb_memory;



/****************************************************
 *函数名称:file_size_get
 *输入参数:pfile_path	-文件路径
 *返 回 值:-1		-失败
		   其他值	-文件大小
 *说	明:获取文件大小
 ****************************************************/
unsigned long file_size_get(const char *pfile_path)
{
	unsigned long filesize = -1;	
	struct stat statbuff;
	
	if(stat(pfile_path, &statbuff) < 0)
	{
		return filesize;
	}
	else
	{
		filesize = statbuff.st_size;
	}
	
	return filesize;
}

//获取触摸屏坐标
int get_xy(int *ts_x, int *ts_y)
{
	//打开触摸屏
	int ts_fd = open("/dev/input/event0", O_RDONLY);
	if(ts_fd == -1)
	{
		printf("open TOUCH failed!\n");
		return -1;
	}
	//获取触摸屏数据
	struct input_event mytouch;
	while(1)
	{
	read(ts_fd,  &mytouch, sizeof(mytouch));
		//判断事件类型
		if (mytouch.type == EV_ABS)
		{
		//判断事件代码
		   if(mytouch.code == ABS_X)
			{
			   *ts_x = mytouch.value;
			}
		if(mytouch.code == ABS_Y)
			{
			    *ts_y = mytouch.value;
			}
			
		}
		if (mytouch.type == EV_KEY)
		{
			//判断手指是否离开
		if(mytouch.code == BTN_TOUCH && mytouch.value == 0)
		{
				break;
			}

		}
	}
	//关闭
	close(ts_fd);
	return 0;
}


//初始化LCD
int lcd_open(const char *str)
{
	g_fb_fd = open(str, O_RDWR);
	
	if(g_fb_fd<0)
	{
			printf("open lcd error\n");
			return -1;
	}

	g_pfb_memory  = (int *)mmap(	NULL, 					//映射区的开始地址，设置为NULL时表示由系统决定映射区的起始地址
									FB_SIZE, 				//映射区的长度
									PROT_READ|PROT_WRITE, 	//内容可以被读取和写入
									MAP_SHARED,				//共享内存
									g_fb_fd, 				//有效的文件描述词
									0						//被映射对象内容的起点
								);

	return g_fb_fd;

}

//LCD画点
void lcd_draw_point(unsigned int x,unsigned int y, unsigned int color)
{
	*(g_pfb_memory+y*800+x)=color;
}

//指定区域颜色切换
void change_color(unsigned int x_s,unsigned int y_s, unsigned int x_e,unsigned int y_e, unsigned int color1,unsigned int color2 )
{
	unsigned int x ;
	unsigned int y ;

	for(y = y_s;y<y_e;y++)
	{
		for(x = x_s;x<x_e;x++)
		{
			if(*(g_pfb_memory+y*800+x)==color1)
			{
				*(g_pfb_memory+y*800+x)=color2;
			}
		}
		
	}
	
}

//LCD任意地址绘制图片

int lcd_draw_bmp(unsigned int x,unsigned int y,const char *pbmp_path)   
{
			 int bmp_fd;
	unsigned int blue, green, red;
	unsigned int color;
	unsigned int bmp_width;
	unsigned int bmp_height;
	unsigned int bmp_type;
	unsigned int bmp_size;
	unsigned int x_s = x;
	unsigned int y_s = y;
	unsigned int x_e ;	
	unsigned int y_e ;
	unsigned char buf[54]={0};
			 char *pbmp_buf=g_color_buf;
			
	
	/* 申请位图资源，权限可读可写 */	
	bmp_fd=open(pbmp_path,O_RDWR);
	
	if(bmp_fd == -1)
	{
	   printf("open bmp error\r\n");
	   
	   return -1;	
	}
	
	/* 读取位图头部信息 */
	read(bmp_fd,buf,54);
	
	/* 宽度  */
	bmp_width =buf[18];
	bmp_width|=buf[19]<<8;
	//printf("bmp_width=%d\r\n",bmp_width);
	
	/* 高度  */
	bmp_height =buf[22];
	bmp_height|=buf[23]<<8;
	//printf("bmp_height=%d\r\n",bmp_height);	
	
	/* 文件类型 */
	bmp_type =buf[28];
	bmp_type|=buf[29]<<8;
	//printf("bmp_type=%d\r\n",bmp_type);	

	/* 设置显示x、y坐标结束位置 */
	x_e = x + bmp_width;
	y_e = y + bmp_height;
	
	/* 获取位图文件的大小 */
	bmp_size=file_size_get(pbmp_path);

	
	/* 读取所有RGB数据 */
	read(bmp_fd,pbmp_buf,bmp_size-54);
	
	for(;y < y_e; y++)
	{
		for (;x < x_e; x++)
		{
				/* 获取红绿蓝颜色数据 */
				blue  = *pbmp_buf++;
				green = *pbmp_buf++;
				red   = *pbmp_buf++;
				
				/* 判断当前的位图是否32位颜色 */
				if(bmp_type == 32)
				{
					pbmp_buf++;
				}
				
				/* 组成24bit颜色 */
				color = red << 16 | green << 8 | blue << 0;
				lcd_draw_point(x, y_e-1-(y-y_s), color);				
		}
		
		x = x_s;
	}
	
	/* 不再使用BMP，则释放bmp资源 */
	close(bmp_fd);	
	
	return 0;
}


//LCD关闭
void close_lcd(void)
{
	
	/* 取消内存映射 */
	munmap(g_pfb_memory, FB_SIZE);
	
	/* 关闭LCD设备 */
	close(g_fb_fd);
}
