/******************************************************************************************
//File Name:		iic-sim-at24.c
//Description:	GPIOģ��IIC_SCL IIC_SDA ���� at24c08
								iic-sim-at24-zz����������.c
								neware ������������
//Date:			zz @2014-4-29 09:51:05
						zz @2014-5-13 09:07:54
*/


#define IIC_SCL		S3C2410_GPB(0)
#define IIC_SDA		S3C2410_GPB(1)

#define DEV_ADDR	0xa0
#define DATA_ADDR	0x10

/******************************************************************************************
//Func Name:		delay()
//Description:		����ʱ����
//				
//Date:			zz @2014-4-29 10:39:47
*/
void delay(int t)
{
	while(i>0)
	{
		i--;
	}
}

/******************************************************************************************
//Func Name:		_ack()
//Description:		iic���߽��պ���,aΪ0��Ч
//				
//Date:			zz @2014-4-29 10:39:47
*/
void _ack(int a)
{
	IIC_SCL = 0;
	if(a == 0)
	{
		IIC_SDA = 0;
	}
	else
	{
		IIC_SDA = 1;
	}
	IIC_SCL = 1;
	delay(1);
	
	//zz// ����stopתΪ����,����������󶼱�֤SCL=0����..
	IIC_SCL = 0;
	delay(1);

}

/******************************************************************************************
//Func Name:		_wait_ack()
//Description:		���ͺ�ȴ�AT24C08����0
//				
//Date:			zz @2014-4-29 10:39:47
*/
int _wait_ack()
{
	int tm_out = 50;
	IIC_SCL = 0;
	IIC_SDA = 1;

	while(IIC_SDA && tm_out>0)
	{
		tm_out--;
		delay(1);
	}

	if(IIC_SDA)
	{
		IIC_SCL = 1;
		delay(1);
		
		//zz// ����stopתΪ����,����������󶼱�֤SCL=0����..
		IIC_SCL = 0;
		delay(1);
		
		return(-1);
	}
	else
	{
		IIC_SCL = 1;
		delay(1);
		
		//zz// ����stopתΪ����,����������󶼱�֤SCL=0����..
		IIC_SCL = 0;
		delay(1);

		return(0);
	}
}

/******************************************************************************************
//Func Name:		_start()
//Description:		iic��������
//				
//Date:			zz @2014-4-29 10:39:47
*/
void _start()
{
	IIC_SDA = 1;
	IIC_SCL = 1;

	delay(1);
	IIC_SDA = 0;
	delay(1);

	//zz// ����stopתΪ����,����������󶼱�֤SCL=0����..
	IIC_SCL = 0;
	delay(1);

}

/******************************************************************************************
//Func Name:		_stop()
//Description:		iic����ֹͣ
//				
//Date:			zz @2014-4-29 10:39:47
*/
void _stop()
{
	IIC_SDA = 0;
	IIC_SCL = 1;

	delay(1);
	IIC_SDA = 1;
	delay(1);
}

/******************************************************************************************
//Func Name:		_write()
//Description:		��iic���߷�������
//				
//Date:			zz @2014-4-29 10:39:47
*/
int _write(unsigned char data)
{
	int i = 8;

	for(i=0;i<8;i++)
	{
		IIC_SCL = 0;

		if(data&0x80)
		{
			IIC_SDA = 1;
		}
		else
		{
			IIC_SDA = 0;
		}

		data = data<<1;
		
		delay(1);
		IIC_SCL = 1;
		delay(1);
	}

	//zz// ����stopתΪ����,����������󶼱�֤SCL=0����..
	IIC_SCL = 0;
	delay(1);
		
	return _wait_ack();
	
}

/******************************************************************************************
//Func Name:		_read()
//Description:		��iic���߶�ȡ����
//				
//Date:			zz @2014-4-29 10:39:47
*/
unsigned char _read()
{
	unsigned char data = 0;
	int i = 8;

	for(i=0;i<8;i++)
	{
		IIC_SCL = 0;
		delay(1);
		IIC_SCL = 1;

#if 0
		data = data<<1;
		if(IIC_SDA)
			data |= 0x01;
		else
			data &= ~0x01;
#endif
#if 1
		if(IIC_SDA)
			data |= 0x01<<(7-i);
		else
			data &= ~(0x01<<(7-i));		
#endif

		delay(1);
	}

	//zz// ����stopתΪ����,����������󶼱�֤SCL=0����..
	IIC_SCL = 0;
	delay(1);

	_ack(0);
	return data;

}

/******************************************************************************************
//Func Name:		main()
//Description:		main����,���AT24C08��һ���ֽڵĶ�ȡ
//				
//Date:			zz @2014-4-29 10:39:47
*/
int main()
{
	unsigned char rec_buf;

	_start();
	_write(DEV_ADDR);
	_write(DATA_ADDR);
	_stop();

	_start();
	_write(DEV_ADDR|0x01);
	rec_buf = _read();
	_stop();

	printf("The recv data of AT24C08 at 0x%x is %c"\n,\
		DATA_ADDR,rec_buf);
	
	return 0;
}




