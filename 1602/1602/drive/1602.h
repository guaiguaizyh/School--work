//�ڵ���1602��غ���ǰ����Ҫ��1602�ĳ�ʼ��
#ifndef _1602_H_
#define _1602_H_

#include <config.h>
#include <delay.h>
void LCD1602_Init( );//1602��ʼ������
void LCD1602_disstr(u8 *p,u8 x,u8 y);//��ָ�����꿪ʼ��ʾӢ���ַ��������Ȳ�����32�����Զ�����
void LCD1602_clear( );//1602��������
void LCD1602_backspace( );//����ɾ��һ���ַ�
void LCD1602_cursor(u8 direct);//��������ƶ���direct=0�����ƣ�direct=1������
void LCD1602_screen(u8 direct);//��Ļ�����ƶ���direct=0�����ƣ�direct=1������
void LCD1602_disch(u8 ch);//�ڵ�ǰλ����ʾһ��Ӣ���ַ�
void LCD1602_disch_x_y(u8 ch,u8 x,u8 y);//��ָ��λ����ʾһ��Ӣ���ַ�
#endif