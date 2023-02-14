#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extract_num(char *word)
{
	char *end_word;
	int num = strtol(word, &end_word, 10);
	if (num != 0 && *end_word == '\0')
		return num;
	return 0;
}

int main()
{
	char str[256];
	char delim[] = " \n,.:;";
	fgets(str, 256, stdin);
	
	char *word = strtok(str, delim);
	int sum = 0;
	do
	{
		if (NULL == word)
			break;
		sum += extract_num(word);
		word = strtok(NULL, delim);
	} while (1);
	
	printf("Sum: %d\n", sum);
}