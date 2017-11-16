#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>
#include<stdarg.h>
#include"sea_funk.h"


int shmain(int argc, char* argv[])
{
	srand(time(NULL));
	int field_user0[10][10] = { 0 };
	int(*ptr_fuser0)[10][10] = &field_user0;
	int field_user1[10][10] = { 0 };
	int(*ptr_fuser1)[10][10] = &field_user1;
	system("CLS");
	printf("Hello! This is Sea battle game.\n\n Lets start!\n");
	system("pause");
	char answ_u0[6] = { 0 };
	char answ_u1[6] = { 0 };
	while (true) // Sozdanie pol'a usera 0
	{
		system("CLS");
		getchar();
		printf("User one how would you like to create your field? (self/auto) ");
		fgets(answ_u0, 6, stdin);
		if (answ_u0[strlen(answ_u0) - 1] == 10)
		{
			answ_u0[strlen(answ_u0) - 1] = '\0';
		}

		if (strcmp(answ_u0, "self") == 0)
		{
			if (create_field(ptr_fuser0))
			{
				break;
			}
		}
		else if (strcmp(answ_u0, "auto") == 0)
		{
			if (create_field_auto(ptr_fuser0))
			{
				break;
			}
		}
		else
		{
			printf("Wrong enter...");
		}
		system("pause");
	}
	while (true)  // Sozdanie pol'a usera 1
	{
		system("CLS");
		getchar();
		printf("User two how would you like to create field? (self/auto/bot) ");
		fgets(answ_u1, 6, stdin);
		if (answ_u1[strlen(answ_u1) - 1] == 10)
		{
			answ_u1[strlen(answ_u1) - 1] = '\0';
		}
		if (strcmp(answ_u1, "self") == 0)
		{
			if (create_field(ptr_fuser1))
			{
				break;
			}
		}
		else if (strcmp(answ_u1, "auto") == 0)
		{
			if (create_field_auto(ptr_fuser1))
			{
				break;
			}
		}
		else if (strcmp(answ_u1, "bot") == 0)
		{
			if (create_field_auto(ptr_fuser1))
			{
				break;
			}
		}
		else
		{
			printf("Wrong enter...");
		}
		system("pause");
	}
	bool hit0 = true; // vozmozhnost' hoda igroka 0 
	bool hit1 = true; // vozmozhnost' hoda igroka 1
	int hit_u0 = 0;  // podschet popadanij igroka 0
	int hit_u1 = 0; // podschet popadanij igroka 1
	int count = 1; // podschet hodov igrokov
	char letters[11] = { 'A','B','C','D', 'E', 'F', 'G', 'H', 'I', 'J' };
	while (true)
	{
		int coll = 0;
		int row = 0;
		int *ptr_coll = &coll;
		int *ptr_row = &row;
		while (hit0 && hit_u0<20)
		{
			system("CLS");
			printf("First user turn\n\n Move: %d\n\n", count);
			print_field(ptr_fuser0, ptr_fuser1);
			if (coor(ptr_row, ptr_coll))
			{
				continue;
			}
			if (field_user1[row][coll] == 0)
			{
				field_user1[row][coll] += 1;
				count++;
				hit0 = false;
				hit1 = true;
			}
			else if (field_user1[row][coll] == 2)
			{
				field_user1[row][coll] += 1;
				count++;
				hit_u0++;
			}
			else
			{
				print_new_wind("You already shoot this place! ");
			}
		}
		if (strcmp(answ_u1, "bot") == 0)
		{
			while (hit1 && hit_u1<20)
			{
				system("CLS");
				printf("User two is hitting...\n\nMove: %d\n\n", count);
				//print_field(ptr_fuser0, ptr_fuser1);
				row = rand() % 10;
				coll = rand() % 10;
				if (field_user0[row][coll] == 0) // check hint
				{
					field_user0[row][coll] += 1;
					count++;
					print_field(ptr_fuser0, ptr_fuser1);
					printf("Coordinates %c-%d    MISS\n", letters[coll], row + 1);
					system("pause");
					hit1 = false;
					hit0 = true;
				}
				else if (field_user0[row][coll] == 2)
				{
					field_user0[row][coll] += 1;
					print_field(ptr_fuser0, ptr_fuser1);
					printf("Coordinates %c-%d    HIT\n", letters[coll], row + 1);
					system("pause");
					count++;
					hit_u1++;
				}
			}
		}
		else
		{
			print_new_wind("Wait for users to change...");
			while (hit1 && hit_u1<20)
			{
				system("CLS");
				printf("Second user turn\n\n Move: %d\n\n", count);
				print_field(ptr_fuser1, ptr_fuser0);
				if (coor(ptr_row, ptr_coll))
				{
					continue;
				}
				if (field_user0[row][coll] == 0)
				{
					field_user0[row][coll] += 1;
					count++;
					hit1 = false;
					hit0 = true;
				}
				else if (field_user0[row][coll] == 2)
				{
					field_user0[row][coll] += 1;
					count++;
					hit_u1++;
				}
				else
				{
					print_new_wind("You already shoot this place! ");
				}
			}
			if (hit_u0 == 20) // proverka na pobedu
			{
				printf("\n      User one win!\n\n");
				break;
			}
			else if (hit_u1 == 20) // proverka na pobedu
			{
				printf("\n      User two win!\n\n");
				break;
			}
			print_new_wind("Wait for users to change...");
		}		
	}

	system("pause");
	return 0;
}