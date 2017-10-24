#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <time.h>

#define SEPARATOR (char)'_'

#define MAX_SIZE 1000
#define MAX_WORD_COUNT 1000

int GLOBAL_COUNTER = 0;

char MATERIAL[MAX_WORD_COUNT][2][MAX_SIZE];

void init_source(char* path);

void init_source(char* path)
{
	GLOBAL_COUNTER = 0;
	FILE *sourceFile = fopen(path, "r"); // only for read
	char tmp_str[MAX_SIZE];

	while(1)
	{
		if(fgets(tmp_str, MAX_SIZE, sourceFile) == 0)
		{
			if(feof(sourceFile) == 0)
			{
				printf("Error open source.eng\n");
				fflush(stdout);
				break;
			}
			else
			{
				GLOBAL_COUNTER--; // удаляем одно лишнее прибавление счетчика
				MATERIAL[GLOBAL_COUNTER][1][strlen(MATERIAL[GLOBAL_COUNTER][1])] = tmp_str[strlen(tmp_str) - 1];
				MATERIAL[GLOBAL_COUNTER][1][strlen(MATERIAL[GLOBAL_COUNTER][1]) + 1] = '\0';
				break;
			}
		}
		else
		{
			for(int i = 0; i < (int)strlen(tmp_str); i++)
			{
				if(tmp_str[i] != SEPARATOR)
				{
					MATERIAL[GLOBAL_COUNTER][0][i] = tmp_str[i];
				}
				else
				{
					MATERIAL[GLOBAL_COUNTER][0][i] = '\0';

					for(int j = 0; j < (int)strlen(tmp_str) - i - 2; j++)
					{
						MATERIAL[GLOBAL_COUNTER][1][j] = tmp_str[i + j + 1];
						if(j + 1 == strlen(tmp_str) - i - 2)
						{
							MATERIAL[GLOBAL_COUNTER][1][j + 1] = '\0';
						}
					}

					break;
				}
			}
			GLOBAL_COUNTER++;
		}
	}
	fclose(sourceFile);
}

int main()
{
	setlocale(LC_ALL,"RUSSIAN");	// russification
	SetConsoleCP(1251);				// russification
	SetConsoleOutputCP(1251);		// russification

	init_source("source.eng");

	char input[MAX_SIZE];
	int word_number = 0;
	while(1)
	{
		srand((unsigned int)time(0));							// randomizing
		word_number = rand() % (GLOBAL_COUNTER + 1);	// randomizing

		printf("%s\n", MATERIAL[word_number][0]);
		fflush(stdout);
		gets(input);

		if(strcmp(input, "") == 0) printf("NO!!! ");
		else if(strstr(MATERIAL[word_number][1], input) == 0) printf("NO!!! ");
		else printf("ok! ");

		printf("(%s)\n\n", MATERIAL[word_number][1]);
		fflush(stdout);
	}

	return 0;
}
