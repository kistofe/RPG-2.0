#include <stdio.h>

int isupper(char letter)
{
	if (letter >= 65 && letter <= 90)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int toupper(char letter)
{
	if (letter >= 97 && letter <= 122)
	{
		letter -= 32;
		return letter;
	}
	else
	{
		return letter;
	}
}

char* capitalize(char* str)
{
	int index = 0;
	while (str[index] != '\0')
	{
		if (!isupper(str[0]))
		{
			str[0] = toupper(str[0]);
		}
		else if (str[index - 1] == 32 && !isupper(str[index]))
		{
			str[index] = toupper(str[index]);
		}
		index++;
	}
	return str;
}

