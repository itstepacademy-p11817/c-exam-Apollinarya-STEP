#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>
#include<stdarg.h>
#include"sea_funk.h"


int main(int argc, char* argv[])
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
	int coor_ind[4][2] = { 0 };
	int ind = 0;
	int last_good_hit[2] = { 0 };
	bool good_hint = false;
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
			row = rand() % 10;
			coll = rand() % 10;
			while (hit1 && hit_u1<20)
			{
				if (good_hint)
				{
					row = coor_ind[ind][0];
					coll = coor_ind[ind][1];
				}
				else
				{
					if (ind == 4)
					{
						ind = 0;
						row = rand() % 10;
						coll = rand() % 10;
					}
					ind++;
					row = coor_ind[ind][0];
					coll = coor_ind[ind][1];
					
				}
				if (row > 9 || row < 0)
				{
					row = last_good_hit[0];
				}
				if (coll > 9 || coll < 0)
				{
					coll = last_good_hit[0];
				}// get row and coll
				if (field_user0[row][coll] == 0) // check hint
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
					last_good_hit[0] = row;
					last_good_hit[1] = coll;
					coor_ind[0][0] = row - 1;
					coor_ind[0][1] = coll;
					coor_ind[1][0] = row;
					coor_ind[1][1] = coll + 1;
					coor_ind[2][0] = row + 1;
					coor_ind[2][1] = coll;
					coor_ind[3][0] = row;
					coor_ind[3][1] = coll - 1;
					good_hint = true;
				}
				else
				{
					good_hint = false;
					ind == 4;
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
			if (hit_u0 == 20)
			{
				printf("\n      User one win!\n\n");
				break;
			}
			else if (hit_u1 == 20)
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