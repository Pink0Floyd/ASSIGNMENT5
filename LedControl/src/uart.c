
#include "uart.h"

void uart_init()
{
      console_init();
}

char get_char()
{
      return console_getchar();
}

void put_char(char c)
{
      console_putchar(c);
}

void put_str(char* str)
{
	uint8_t k=0;
	while(str[k]!='\0'&&k<0xffff)
	{
		put_char(str[k]);
		k++;
	}
}

void put_eol()
{
	put_char('\r');
	put_char('\n');
}


void put_neol(uint8_t n)
{
	put_char('\r');
	while(n>0)
	{
		put_char('\n');
		n--;
	}
	put_char('\r');
}

void put_tab()
{
	put_char('\t');
}

void put_ntab(uint8_t n)
{
	while(n>0)
	{
		put_tab();
		n--;
	}
}

void get_str(char* str,char term)
{
	uint8_t k=0;
	do
	{
		str[k]=get_char();
		k++;
	}
	while(str[k-1]!=term);
	str[k-1]='\0';
}

void put_uint4(uint8_t i)
{
	i=i%0x10;
	if(i<10)
	{
		put_char('0'+i);
	}
	else
	{
		put_char('a'+i-10);
	}
}

uint8_t get_uint4()
{
	char aux=get_char();
	if(aux>='0'&&aux<='9')
	{
		return (uint8_t)(aux-'0');
	}
	else if(aux>='a'&&aux<='f')
	{
		return (uint8_t)(aux+10-'a');
	}
	else if(aux>='A'&&aux<='F')
	{
		return (uint8_t)(aux+10-'A');
	}
	else
	{
		return 0;
	}
}

void put_int(int i)
{
	uint8_t k=INT_SIZE;
	if(i<0)
	{
		i=-i;
		put_char('-');
	}
	while(k>1)
	{
		if(i/(int)pow(10,k-1)!=0)
		{
			break;
		}
//		i=i%(int)pow(10,k-1);
		k--;
	}
	while(k>0)
	{
		put_uint4(i/(int)pow(10,k-1%10));
		i=i%(int)pow(10,k-1);
		
		k--;
	}
}

int get_int()
{
	int i=0;
	int signal=1;
	uint8_t k=INT_SIZE;
	
	char c=get_char();
	if(c=='-')
	{
		signal=-1;
		c=get_char();
	}
	
	if(c>='0'&&c<='9')
	{
		i=(int)(c-'0');
		k--;
	}
	else
	{
		k=0;
	}
	
	while(k>0)
	{
		c=get_char();
		if(c<'0'||c>'9')
		{
			break;
		}
		i=i*10+((int)(c-'0'));
		k--;
	}	
	
	return i*signal;
}

void put_float(float f)
{
	int i=(int)f;
	put_int((int)f);
	put_char('.');
	if(f<0)
	{
		f=-f;
	}
	uint8_t k=FLOAT_SIZE;
	f-=(float)i;
	i=(int)(f*pow(10,k));
	while(k>1)
	{
		if(i%(int)pow(10,INT_SIZE-k)!=0)
		{
			break;
		}
		i=i/10;
		k--;
	}
	i=(int)(f*pow(10,k));
	while(k>0)
	{
		put_uint4((i/(int)pow(10,k-1))%10);
		i=i%(int)pow(10,k-1);
		k--;
	}
}

void put_float_(float f,uint8_t ni,uint8_t nf)
{
	if(ni<1)
	{
		ni=1;
	}
	else if(ni>INT_SIZE)
	{
		ni=INT_SIZE;
	}
	if(nf<1)
	{
		nf=1;
	}
	else if(nf>FLOAT_SIZE)
	{
		nf=FLOAT_SIZE;
	}
	int i=(int)f;
	put_int((int)f);
	put_char('.');
	if(f<0)
	{
		f=-f;
	}
	uint8_t k=nf;
	f-=(float)i;
	i=(int)(f*pow(10,k));
	while(k>1)
	{
		if(i%(int)pow(10,ni-k)!=0)
		{
			break;
		}
		i=i/10;
		k--;
	}
	i=(int)(f*pow(10,k));
	while(k>0)
	{
		put_uint4((i/(int)pow(10,k-1))%10);
		i=i%(int)pow(10,k-1);
		k--;
	}
}