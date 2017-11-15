#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>
#include<stdarg.h>
#include"sea_funk.h"

void print_new_wind(char str[])
{
	system("CLS");
	printf("%s", str);
	system("pause");
}


bool coor(int *row, int *coll)
{
	char chcoll[3] = { 0 };
	getchar();
	printf("Choose coordinates (letter) ");
	fgets(chcoll, 3, stdin);
	if (chcoll[strlen(chcoll) - 1] == 10)
	{
		chcoll[strlen(chcoll) - 1] = '\0';
	}
	printf("Choose coordinates (num) ");
	scanf_s("%d", row);
	if (chcoll[0] < 65 || chcoll[0]>74 || *row < 1 || *row>10)
	{
		print_new_wind("Coordinates out of range.\n");
		return true;
	}
	else
	{
		*coll = chcoll[0] - 65;
		*row -= 1;
		return false;
	}
}


void print_field(int(*user_field)[10][10], int(*opponent_field)[10][10])
{
	printf("\n   A_ B_ C_ D_ E_ F_ G_ H_ I_ J_   #     A_ B_ C_ D_ E_ F_ G_ H_ I_ J_\n");
	for (int i = 0; i < 10; i++)
	{
		for (int two = 0; two < 2; two++) // First field(open)
		{
			if (two == 0)
			{
				printf("  |");
			}
			else
			{
				if (i < 9)
				{
					printf(" ");
				}
				printf("%d|", i + 1);
			}
			for (int ju = 0; ju < 10; ju++)
			{

				if ((*user_field)[i][ju] == 0)
				{
					if (two == 0)
					{
						printf("  ");
					}
					else
					{
						printf("__");
					}
				}
				else if ((*user_field)[i][ju] == 1)
				{
					printf("**");
				}
				else if ((*user_field)[i][ju] == 2)
				{
					printf("##");
				}
				else
				{
					if (two == 0)
					{
						printf("\\/");
					}
					else
					{
						printf("/\\");
					}
				}
				printf("|");
			}
			if (two == 0) // Second field (close)
			{
				printf("  #    |");
			}
			else
			{
				printf("  #  ");
				if (i < 9)
				{
					printf(" ");
				}
				printf("%d|", i + 1);
			}
			for (int jo = 0; jo < 10; jo++)
			{
				if ((*opponent_field)[i][jo] == 1)
				{
					printf("**");
				}
				else if ((*opponent_field)[i][jo] == 3)
				{
					if (two == 0)
					{
						printf("\\/");
					}
					else
					{
						printf("/\\");
					}
				}
				else
				{
					if (two == 0)
					{
						printf("  ");
					}
					else
					{
						printf("__");
					}
				}
				printf("|");
			}
			printf("\n");
		}
	}
	printf("\n\n");
}


bool check_one(int(*field)[10][10], int coll, int row)
{
	int beg_coll = 0;
	int end_coll = 0;
	int beg_row = 0;
	int end_row = 0;
	if (coll == 0)
	{
		beg_coll = 0;
		end_coll = 1;
	}
	else if (coll == 9)
	{
		beg_coll = 8;
		end_coll = 9;
	}
	else
	{
		beg_coll = coll - 1;
		end_coll = coll + 1;
	}
	if (row == 0)
	{
		beg_row = 0;
		end_row = 1;
	}
	else if (row == 9)
	{
		beg_row = 8;
		end_row = 9;
	}
	else
	{
		beg_row = row - 1;
		end_row = row + 1;
	}
	for (int i = beg_row; i <= end_row; i++)
	{
		for (int j = beg_coll; j <= end_coll; j++)
		{
			if ((*field)[i][j] != 0)
			{
				return false;
			}
			//(*field)[i][j] = 1;
		}
	}
	return true;
}


bool check_big(int(*field)[10][10], int coll, int row, char dir[], int lenfig)
{
	int beg_coll = 0;
	int end_coll = 0;
	int beg_row = 0;
	int end_row = 0;
	if (strcmp(dir, "up") == 0)
	{
		if (row - lenfig < 0)
		{
			return false;
		}
		else
		{
			beg_row = row - (lenfig + 1);
			end_row = row + 1;
		}
		beg_coll = coll - 1;
		end_coll = coll + 1;
	}
	else if (strcmp(dir, "down") == 0)
	{
		if (row + lenfig > 9)
		{
			return false;
		}
		else
		{
			beg_row = row - 1;
			end_row = row + (lenfig + 1);
		}
		beg_coll = coll - 1;
		end_coll = coll + 1;
	}
	else if (strcmp(dir, "left") == 0)
	{
		beg_row = row - 1;
		end_row = row + 1;
		if (coll - lenfig < 0)
		{
			return false;
		}
		else
		{
			beg_coll = coll - (lenfig + 1);
			end_coll = coll + 1;
		}
	}
	else
	{
		beg_row = row - 1;
		end_row = row + 1;
		if (coll + lenfig > 9)
		{
			return false;
		}
		else
		{
			end_coll = coll + (lenfig + 1);
			beg_coll = coll - 1;
		}
	}
	// Proverka vyhoda za pole proverochnyh granic
	if (beg_coll < 0)
	{
		beg_coll = 0;
	}
	if (end_coll > 9)
	{
		end_coll = 9;
	}
	if (beg_row < 0)
	{
		beg_row = 0;
	}
	if (end_row > 9)
	{
		end_row = 9;
	}

	for (int i = beg_row; i <= end_row; i++)
	{
		for (int j = beg_coll; j <= end_coll; j++)
		{
			if ((*field)[i][j] != 0)
			{
				return false;
			}
			//(*field)[i][j] = 1;
		}
	}
	return true;
}


bool create_field(int(*field)[10][10])
{
	int fig_mass[4] = { 4, 3, 2, 1 };
	int figure = 0;
	while (true)
	{
		system("CLS");
		printf("\n   A_ B_ C_ D_ E_ F_ G_ H_ I_ J_    You need to place this figures: \n");
		for (int i = 0; i < 10; i++)
		{
			for (int two = 0; two < 2; two++) // First field(open)
			{
				if (two == 0)
				{
					printf("  |");
				}
				else
				{
					if (i < 9)
					{
						printf(" ");
					}
					printf("%d|", i + 1);
				}
				for (int ju = 0; ju < 10; ju++) //Cikle for rows
				{

					if ((*field)[i][ju] == 0)
					{
						if (two == 0)
						{
							printf("  ");
						}
						else
						{
							printf("__");
						}
					}
					else if ((*field)[i][ju] == 1)
					{
						printf("**");
					}
					else if ((*field)[i][ju] == 2)
					{
						printf("##");
					}
					else
					{
						if (two == 0)
						{
							printf("\\/");
						}
						else
						{
							printf("/\\");
						}
					}
					printf("|");

				}// End of cikle
				printf("  ");
				if (i == 1)
				{
					for (int j = 0; j < fig_mass[0]; j++)
					{
						printf("##   ");
					}
				}
				else if (i == 3)
				{
					for (int j = 0; j < fig_mass[1]; j++)
					{
						printf("## ##   ");
					}
				}
				else if (i == 5)
				{
					for (int j = 0; j < fig_mass[2]; j++)
					{
						printf("## ## ##   ");
					}
				}
				else if (i == 7)
				{
					for (int j = 0; j < fig_mass[3]; j++)
					{
						printf("## ## ## ##   ");
					}
				}
				if (i == 9 && two == 1)
				{
					printf("Choose figure 1x%d, 2x%d, 3x%d, 4x%d (0-cancel) ", fig_mass[0], fig_mass[1], fig_mass[2], fig_mass[3]);
					scanf_s("%d", &figure);
				}
				printf("\n");
			}
		}
		if (figure == 0)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					(*field)[i][j] = 0;
				}
			}
			return false;
		}
		if (figure < 1 || figure >4)
		{
			print_new_wind("No such figure! Try again\n");
			continue;
		}
		if (fig_mass[figure - 1] == 0)
		{
			print_new_wind("You have placed all such figures, choose another one.\n");
			continue;
		}

		int coll = 0;
		int row = 0;
		int *ptr_coll = &coll;
		int *ptr_row = &row;
		if (coor(ptr_row, ptr_coll))
		{
			continue;
		}
		//printf("%d , %d", coll, row);
		if ((*field)[row][coll] == 0)
		{
			if (figure == 1)
			{
				if (check_one(field, coll, row))// one ship
				{
					(*field)[row][coll] = 2;
					fig_mass[0] -= 1;
				}
				else
				{
					print_new_wind("This coordinates are unacceptable, try another one.\n");
					continue;
				}
			}
			else if (figure > 1)
			{
				figure--;
				char dir[10] = { 0 };
				printf("Choose direction (up/down/left/right) ");
				getchar();
				fgets(dir, 10, stdin);
				if (dir[strlen(dir) - 1] == 10)
				{
					dir[strlen(dir) - 1] = '\0';
				}
				if (strcmp(dir, "up") == 0 || strcmp(dir, "down") == 0 || strcmp(dir, "left") == 0 || strcmp(dir, "right") == 0)
				{
					if (check_big(field, coll, row, dir, figure))
					{
						if (strcmp(dir, "up") == 0)
						{
							for (int i1 = row; i1 >= row - figure; i1--)
							{
								(*field)[i1][coll] = 2;
							}
						}
						else if (strcmp(dir, "down") == 0)
						{
							for (int i1 = row; i1 <= row + figure; i1++)
							{
								(*field)[i1][coll] = 2;
							}
						}
						else if (strcmp(dir, "left") == 0)
						{
							for (int i1 = coll; i1 >= coll - figure; i1--)
							{
								(*field)[row][i1] = 2;
							}
						}
						else
						{
							for (int i1 = coll; i1 <= coll + figure; i1++)
							{
								(*field)[row][i1] = 2;
							}
						}
						fig_mass[figure] -= 1;
					}
					else
					{
						print_new_wind("This coordinates are unacceptable, try another one.\n");
						continue;
					}
				}
				else
				{
					print_new_wind("Wrong direction, try another one.\n");
					continue;
				}
			}
		}

		system("pause");
		if (fig_mass[0] + fig_mass[1] + fig_mass[2] + fig_mass[3] == 0)
		{
			return true;
		}
	}
}


bool create_field_auto(int(*field)[10][10])
{
	int fig_mass[4] = { 4, 3, 2, 1 };
	int figure_val[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
	int fig_ind = 0;
	int figure = 0;
	while (true)
	{
		figure = figure_val[fig_ind];
		fig_ind++;
		while (true)
		{
			int coll = 0;
			int row = 0;
			coll = rand() % 10;
			row = rand() % 10;
			if ((*field)[row][coll] == 0)
			{
				if (figure == 1)
				{
					if (check_one(field, coll, row))
					{
						(*field)[row][coll] = 2;
						fig_mass[0] -= 1;
						break;
					}
					else
					{
						continue;
					}
				}
				else if (figure > 1)
				{
					int fig_len = figure - 1;
					char dir_val[4][10] = { "up", "down", "left", "right" };
					int dir_ind = rand() % 4;
					if (strcmp(dir_val[dir_ind], "up") == 0 || strcmp(dir_val[dir_ind], "down") == 0 || strcmp(dir_val[dir_ind], "left") == 0 || strcmp(dir_val[dir_ind], "right") == 0)
					{
						if (check_big(field, coll, row, dir_val[dir_ind], fig_len))
						{
							if (strcmp(dir_val[dir_ind], "up") == 0)
							{
								for (int i1 = row; i1 >= row - fig_len; i1--)
								{
									(*field)[i1][coll] = 2;
								}
							}
							else if (strcmp(dir_val[dir_ind], "down") == 0)
							{
								for (int i1 = row; i1 <= row + fig_len; i1++)
								{
									(*field)[i1][coll] = 2;
								}
							}
							else if (strcmp(dir_val[dir_ind], "left") == 0)
							{
								for (int i1 = coll; i1 >= coll - fig_len; i1--)
								{
									(*field)[row][i1] = 2;
								}
							}
							else
							{
								for (int i1 = coll; i1 <= coll + fig_len; i1++)
								{
									(*field)[row][i1] = 2;
								}
							}
							fig_mass[fig_len] -= 1;
							break;
						}
						else
						{
							continue;
						}
					}
					else
					{
						continue;
					}
				}
			}
		}
		if (fig_ind == 10 && fig_mass[0] + fig_mass[1] + fig_mass[2] + fig_mass[3] != 0)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					(*field)[i][j] = 0;
				}
			}
			return false;
		}
		if (fig_mass[0] + fig_mass[1] + fig_mass[2] + fig_mass[3] == 0)
		{
			return true;
		}
	}
}