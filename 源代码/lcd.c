/*
 ���ܣ�lcd��Ļ�����ر�
		��ʾbmpͼƬ
		��ȡ����������
		ָ��������ɫ�л�
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
 *��������:file_size_get
 *�������:pfile_path	-�ļ�·��
 *�� �� ֵ:-1		-ʧ��
		   ����ֵ	-�ļ���С
 *˵	��:��ȡ�ļ���С
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

//��ȡ����������
int get_xy(int *ts_x, int *ts_y)
{
	//�򿪴�����
	int ts_fd = open("/dev/input/event0", O_RDONLY);
	if(ts_fd == -1)
	{
		printf("open TOUCH failed!\n");
		return -1;
	}
	//��ȡ����������
	struct input_event mytouch;
	while(1)
	{
	read(ts_fd,  &mytouch, sizeof(mytouch));
		//�ж��¼�����
		if (mytouch.type == EV_ABS)
		{
		//�ж��¼�����
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
			//�ж���ָ�Ƿ��뿪
		if(mytouch.code == BTN_TOUCH && mytouch.value == 0)
		{
				break;
			}

		}
	}
	//�ر�
	close(ts_fd);
	return 0;
}


//��ʼ��LCD
int lcd_open(const char *str)
{
	g_fb_fd = open(str, O_RDWR);
	
	if(g_fb_fd<0)
	{
			printf("open lcd error\n");
			return -1;
	}

	g_pfb_memory  = (int *)mmap(	NULL, 					//ӳ�����Ŀ�ʼ��ַ������ΪNULLʱ��ʾ��ϵͳ����ӳ��������ʼ��ַ
									FB_SIZE, 				//ӳ�����ĳ���
									PROT_READ|PROT_WRITE, 	//���ݿ��Ա���ȡ��д��
									MAP_SHARED,				//�����ڴ�
									g_fb_fd, 				//��Ч���ļ�������
									0						//��ӳ��������ݵ����
								);

	return g_fb_fd;

}

//LCD����
void lcd_draw_point(unsigned int x,unsigned int y, unsigned int color)
{
	*(g_pfb_memory+y*800+x)=color;
}

//ָ��������ɫ�л�
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

//LCD�����ַ����ͼƬ

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
			
	
	/* ����λͼ��Դ��Ȩ�޿ɶ���д */	
	bmp_fd=open(pbmp_path,O_RDWR);
	
	if(bmp_fd == -1)
	{
	   printf("open bmp error\r\n");
	   
	   return -1;	
	}
	
	/* ��ȡλͼͷ����Ϣ */
	read(bmp_fd,buf,54);
	
	/* ���  */
	bmp_width =buf[18];
	bmp_width|=buf[19]<<8;
	//printf("bmp_width=%d\r\n",bmp_width);
	
	/* �߶�  */
	bmp_height =buf[22];
	bmp_height|=buf[23]<<8;
	//printf("bmp_height=%d\r\n",bmp_height);	
	
	/* �ļ����� */
	bmp_type =buf[28];
	bmp_type|=buf[29]<<8;
	//printf("bmp_type=%d\r\n",bmp_type);	

	/* ������ʾx��y�������λ�� */
	x_e = x + bmp_width;
	y_e = y + bmp_height;
	
	/* ��ȡλͼ�ļ��Ĵ�С */
	bmp_size=file_size_get(pbmp_path);

	
	/* ��ȡ����RGB���� */
	read(bmp_fd,pbmp_buf,bmp_size-54);
	
	for(;y < y_e; y++)
	{
		for (;x < x_e; x++)
		{
				/* ��ȡ��������ɫ���� */
				blue  = *pbmp_buf++;
				green = *pbmp_buf++;
				red   = *pbmp_buf++;
				
				/* �жϵ�ǰ��λͼ�Ƿ�32λ��ɫ */
				if(bmp_type == 32)
				{
					pbmp_buf++;
				}
				
				/* ���24bit��ɫ */
				color = red << 16 | green << 8 | blue << 0;
				lcd_draw_point(x, y_e-1-(y-y_s), color);				
		}
		
		x = x_s;
	}
	
	/* ����ʹ��BMP�����ͷ�bmp��Դ */
	close(bmp_fd);	
	
	return 0;
}


//LCD�ر�
void close_lcd(void)
{
	
	/* ȡ���ڴ�ӳ�� */
	munmap(g_pfb_memory, FB_SIZE);
	
	/* �ر�LCD�豸 */
	close(g_fb_fd);
}
