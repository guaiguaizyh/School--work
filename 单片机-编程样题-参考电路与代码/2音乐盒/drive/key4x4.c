#include <key4x4.h>
#define key_data P2 //�궨��4*4���󰴼���������
u8 keyval_4X3[]="123456789*0#";	
u8 keyval_4X4[]="789/456*123-c0=+"; 
u8 key_scan_4X4( )//4*4���󰴼�ɨ�躯�������ذ����ţ�0-16����16��ʾ�ް�������
{
	u8 i,temp,vol,keyvalue=16;
	//�ȼ���Ƿ��м�����
	key_data=0xf0;
	temp=key_data;
	if((temp&0xf0)!=0xf0)
	{
		//ȥ��
		delay_ms(10);
		key_data=0xf0;
		temp=key_data;		
		if((temp&0xf0)!=0xf0)
		{
			 //ȷ���м�������ɨ���ĸ�������
			 vol=0xfe;
			 for(i=0;i<4;i++)
			 {
			 	key_data=vol;
				temp=key_data;
				switch(temp&0xf0)
				{
				 	case 0xe0:keyvalue=4*i+0;break;
					case 0xd0:keyvalue=4*i+1;break;
					case 0xb0:keyvalue=4*i+2;break;
				    case 0x70:keyvalue=4*i+3;break;		
				}
				vol=_crol_(vol,1);
			 }
			 //�ȴ������ͷ�
			 do{
			 key_data=0xf0;
			 temp=key_data;
			}while((temp&0xf0)!=0xf0);
		}
	}
	//���ذ���ֵ
	return 	keyvalue;
}
u8 key_scan_4X3( )//4*3���󰴼�ɨ�躯�������ذ����ţ�0-11����12��ʾ�ް�������
{
	u8 i,temp,vol,keyvalue=12;
	//�ȼ���Ƿ��м�����
	key_data=0xf0;
	temp=key_data;
	if((temp&0xf0)!=0xf0)
	{
		//ȥ��
		delay_ms(10);
		key_data=0xf0;
		temp=key_data;		
		if((temp&0xf0)!=0xf0)
		{
			 //ȷ���м�������ɨ���ĸ�������
			 vol=0xfe;
			 for(i=0;i<4;i++)
			 {
			 	key_data=vol;
				temp=key_data;
				switch(temp&0xf0)
				{
				 	case 0xe0:keyvalue=3*i+0;break;
					case 0xd0:keyvalue=3*i+1;break;
					case 0xb0:keyvalue=3*i+2;break;		
				}
				vol=_crol_(vol,1);
			 }
			 //�ȴ������ͷ�
			 do{
			 key_data=0xf0;
			 temp=key_data;
			}while((temp&0xf0)!=0xf0);
		}
	}
	//���ذ���ֵ
	return 	keyvalue;
}