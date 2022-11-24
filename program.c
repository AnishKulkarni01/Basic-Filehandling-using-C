//FILE HANDLING ASSIGNMENT
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
/*
ANISH KULKARNI : 2020A7PS0975P
This code consists of a menu which has 3 options for the user. The menu keeps on running till the user doesnt exit using option 4.
The data for this file handling program is taken from a csv file.
*/

/*
For course name enter one of these :
m1
thermo
workshop
bio
cp
trw
biolab
chemlab
phylab
meow
m2
es
eg
genchem
oop
dd
dicso
lics
m3
appphil
bizcom
*/

void printmenu(char **Menu)
{

  printf("\n\nMain Menu\n");

  for (int i = 0; i < 4; i++)
  {
    printf("%s \n", Menu[i]);
  }
}

int getCredits(char *course)
{
  if (strcasecmp(course, "workshop") == 0 || strcasecmp(course, "trw") == 0)
    return 2;
  else if (strcasecmp(course, "biolab") == 0 || strcasecmp(course, "phylab") == 0 || strcasecmp(course, "chemlab") == 0)
    return 1;
  else if (strcasecmp(course, "oop") == 0 || strcasecmp(course, "dd") == 0 || strcasecmp(course, "cp") == 0)
    return 4;
  return 3;
}

int getGp(char *course)
{
  if (strcasecmp(course, "A") == 0)
    return 10;
  else if (strcasecmp(course, "A-") == 0)
    return 9;
  else if (strcasecmp(course, "B") == 0)
    return 8;
  else if (strcasecmp(course, "B-") == 0)
    return 7;
  else if (strcasecmp(course, "C") == 0)
    return 6;
  else if (strcasecmp(course, "C-") == 0)
    return 5;
  else if (strcasecmp(course, "D") == 0)
    return 4;
  return 0;
}


int main()
{ 
  int stop=0;
  double cg = 0;
  int sum1 = 0;
  int units1 = 0;
  char line[100];
  char course[22][30];
  char marks[22][30];
  char grade[22][30];
  char cname[30];
  char cgrade[3];
  char cmarks[5];

  FILE *fp = fopen("data.csv", "r");
  if (fp == NULL)
  {
    printf("Unable to open file");
    exit(0);
  }

  char *token;
  int i = 0;
  while (fgets(line, sizeof(line), fp))
  {
    token = strtok(line, ",");

    strcpy(cname, token);
    // printf("\n%s",cname);
    token = strtok(NULL, ",");
    strcpy(cmarks, token);
    //printf("\n%s",cmarks);
    token = strtok(NULL, ",");
    strcpy(cgrade, token);
    //printf("\n%s",cgrade);
    token = strtok(NULL, ",");
    strcpy(course[i], cname);
    strcpy(grade[i], cgrade);
    strcpy(marks[i], cmarks);
    // printf("\n%s %s %s",course[i],grade[i],marks[i]);
    i++;
  }

  char *Menu[4];
  Menu[0] = "1. Check grades/marks of a course";
  Menu[1] = "2. Check mgpa";
  Menu[2] = "3. Check cgpa";
  Menu[3] = "4. Exit";

  int sem;
  while (true)
  {
    printmenu(Menu);
    printf("\nSelect option number\n");
    int opt;
    int inpn;
    scanf("%d", &opt);
    switch (opt)
    {

    case 1:
      printf("Enter course name\n");
      char inps[30];
      scanf("%s", &inps);
      printf("\nSelect no: 1.See marks  2.See grade  3.See both\n\n");

      scanf("%d", &inpn);
      int index = 0;
      for (int i = 0; i < 20; i++)
      {
        if (strcasecmp(inps, course[i]) == 0)
          index = i;
      }
      switch (inpn)
      {
      case 1:
        printf("Marks : %s\n", marks[index]);
        break;
      case 2:
        printf("Grade : %s\n", grade[index]);
        break;
      case 3:
        printf("Marks : %s\nGrade: %s\n", marks[index], grade[index]);
        break;
      default:
        printf("invalid input");
        break;
      }

      break;

    case 2: //printf("%d",getGp(grade[16])*getCredits(course[16]));
      printf("Enter semester number(1 or 2 or 3)\n");

      scanf("%d", &sem);

      // printf("%lf",calculatesg(course,grade,sem));
      double sg = 0;
      int sum = 0;
      int units = 0;
      if (sem == 1)
      {
        for (int i = 0; i < 9; i++)
        {
          sum += getCredits(course[i]) * getGp(grade[i]);
          units += getCredits(course[i]);
          //printf("%d %d\n",sum,units);
        }
      }
      else if (sem == 2)
      {
        for (int i = 9; i < 14; i++)
        {
          sum += getCredits(course[i]) * getGp(grade[i]);
          units += getCredits(course[i]);
        }
      }
      else if (sem == 3)
      {
        for (int i = 14; i < 21; i++)
        {
          sum += getCredits(course[i]) * getGp(grade[i]);
          units += getCredits(course[i]);
        }
      }
      sg = 1.0 * sum / units;
      printf("MGPA : %lf", sg);
      break;

    case 3:

      for (int i = 0; i < 21; i++)
      {

        sum1 += getCredits(course[i]) * getGp(grade[i]);
        units1 += getCredits(course[i]);
        //printf("%d %d\n",sum,units);
      }

      cg = 1.0 * sum1 / units1;
      printf("CGPA : %lf", cg);

      break;

    case 4:
       stop=1;
      break;

    default:
    printf("invalid input");
    stop=1;
      break;

      
    }
    if(stop==1)break;
  }
  return 0;
}

