
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
