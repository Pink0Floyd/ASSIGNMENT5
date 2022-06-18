
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

void put_str(char* str)
{
	uint8_t k=0;
	while(str[k]!='\0'&&k<0xffff)
	{
		put_char(str[k]);
		k++;
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