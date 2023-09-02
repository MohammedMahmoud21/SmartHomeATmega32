#include "Strings.h"


u8 String_Compare(u8 *str1,u8 *str2)
{
	u8 ret_val=NOT_EQUAL;
	u8 index=0;
	u8 flag=1;
	s16 Diff=0;
	for(; ((str1[index]) || (str2[index])) && (1 == flag) ;index++)
	{
		Diff = str1[index]-str2[index];
		Diff = ABS(Diff);
		if((0 == Diff) || (DIFF == Diff))
		{
			//Nothing they are equal till now.
		}
		else
		{
			flag=0;
		}
	}
	if(1 == flag)
	{
		ret_val=EQUAL;
	}
	else
	{
		ret_val= NOT_EQUAL;
	}
	
	return (ret_val);	
}

Error_t String_Split(u8 *main_str,u8 *splited_str1,u32 *splited_number)
{
	Error_t error= OK;
	u16 index=0;
	u8 space_flag=0;
	if((NULL_PTR == main_str) || (NULL_PTR == splited_str1))
	{
		error = NULL;
	}
	else
	{
		while(main_str[index])
		{
			if(' ' == main_str[index])
			{
				space_flag=1;
				splited_str1[index]=0;
			}
			else
			{
				if(0 == space_flag)
				{
					splited_str1[index] = main_str[index];
				}
				else
				{
					*splited_number = (*splited_number * 10u) + (main_str[index] - '0');
				}	
			}
			index++;
		}
	}
	return (error);
}