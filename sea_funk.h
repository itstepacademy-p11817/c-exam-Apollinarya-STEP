#pragma once

void print_new_wind(char str[]); // Vyvod soobshenija v ochishennom ("novom") pole


bool coor(int *row, int *coll); // Poluchenie coordinat ot pol'zovatel'a (row, coll) Vozvrashaet true, esli coordinaty vne granic; Vozvrashaet false, esli coordinaty zapisany


void print_field(int(*user_field)[10][10], int(*opponent_field)[10][10]); // Vyvodit dva pol'a: otkrytoe samogo igroka i zakrytoe protivnika


bool check_one(int(*field)[10][10], int coll, int row); // Proverka razmeshenija odinochnogo korablika; Vozvrashaet true, esli proverka uspeshna i false esli neuspeshna


bool check_big(int(*field)[10][10], int coll, int row, char dir[], int lenfig); // Proverka razmeshenija dlinnyh korablikov; Vozvrashaet true, esli proverka uspeshna i false esli neuspeshna


bool create_field(int(*field)[10][10]); // Sozdanie pol'a pol'zovatelem // Vozvrashaet true esli vse korabliki razmesheny i false pri vvedenii cancel(0)(obnul'aet pole)


bool create_field_auto(int(*field)[10][10]); //Avtomaticheskoe sozdanie pol'a // Vozvrashaet true esli vse korabliki razmesheny i false, esli est' propushennye korabli(obnul'aet pole)