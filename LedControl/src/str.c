
#include "str.h"

void init_str(char* str,uint16_t length,char c)
{
	while(length>0)
	{
		length--;
		str[length]=c;
	}
}

int16_t len_str(char* str)
{
	int16_t i=-1;
	uint16_t k=0;
	while(k<STR_MAX_LEN)
	{
		if(str[k]=='\0')
		{
			i=k+1;
			break;
		}
		k++;
	}
	return i;
}

int16_t find_str_c(char* str,char c,uint16_t length)
{
	int16_t i=-1;
	uint16_t k=0;
	while(k<length)
	{
		if(str[k]==c)
		{
			i=k;
			break;
		}
		k++;
	}
	return i;
}

int16_t find_str_cc(char* str,char ci,char cf,uint16_t length)
{
	int16_t i=-1;
	while(ci<=cf&&i==-1)
	{
		i=find_str_c(str,ci,length);
		ci++;
	}
	return i;
}

int16_t find_str_str(char* str,char* str0,uint16_t length,uint16_t n)
{
	int16_t i=-1;
	int16_t ii=-1;
	int16_t aux=0;
	uint16_t k=0;
	uint16_t pos=0;
	while(k<n)
	{
		aux=pos+find_str_c(&str[pos],str0[k],length-pos);
		if(aux<pos)
		{
			i=-1;
			break;
		}
		else
		{
			if(k==0)
			{
				ii=aux;
				pos=aux+1;
				k++;
			}
			else
			{
				if(aux==pos)
				{
					pos++;
					k++;
				}
				else
				{
					k=0;
				}
			}
		}

	}
	if(k==n)
	{
		i=ii;
	}
	return i;
}

void copy_str(char* str1,char* str2,uint16_t length)
{
	uint16_t k=0;
	while(k<length&&str1[k]!='\0')
	{
		str2[k]=str1[k];
		k++;
	}
	str2[k]='\0';
}