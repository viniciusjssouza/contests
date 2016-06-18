/********************************************************************
* UVA 631 - Microzoft Calendar
*
* Autor: Vinicius J. S. Souza
* Data: 19/12/2009
* Tecnincas: ad-hoc
********************************************************************/
#include<iostream>
#include<cstdlib>
#include<string>
#include<cmath>

#define FIRST_YEAR 1600

using namespace std;

int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char months[5][15] = { "Sun", "Water", "Forest", "Mountains", "Money"};
char weeks[6][15] = { "First", "Second", "Third", "Fourth", "Fifth", "Sixth"};
char periodos[2][10] = {"Gill", "Bates"};

int inicio = 0;

bool isLeapYear(int ano)
{
   if ((ano%4) == 0 && (ano % 100) != 0) return true;
   if ((ano%400) == 0) return true;
   return false;
}

int dateToDays(int dia, int mes, int ano)
{
   int total= 0;
   for (int i= FIRST_YEAR; i < ano; i++)
   {
      if (isLeapYear(i)) 
	 total += 366;
      else
	 total += 365;
   }
   for (int i = 1; i < mes; i++)
   {
      if (i == 2 && isLeapYear(ano))
	 total += daysInMonth[2]+1;
      else
	 total += daysInMonth[i];
   }
   return (total+dia);
}

int updateYears(int &dias)
{
   int year = 1;
   while(true)
   {
      if (isLeapYear(year))
      {
	 if (dias <= 366) break;
	 dias -= 366;
      }
      else
      {
	 if (dias <= 365) break;
	 dias -= 365;
      }
      year++;
   }
   return year;
}

void calculValues(int dias, bool down, int year)
{
   int day = 0, month, week, per;
   if (dias <= 180)
      month = ((dias-1) / 36);
   else
      month = (dias-181) / 36.0;	 
   per = (dias-1) / 180;
   int monthDay = (dias % 36);
   if (!monthDay) monthDay = 36;
   week = (monthDay-1) / 6;	 
   day = (dias % 6);
   if (!day) day = 6;
   if (!down)
      printf("%s-%s-%s-%d-%dbd\n", periodos[per], months[month], weeks[week], day, year);
   else
      printf("%s-%s-%s-%d-%d\n", periodos[per], months[month], weeks[week], day, year);
}

int main()
{
   string input;
   inicio = dateToDays(25, 06, 1998);
   while (true)
   {
      getline(cin, input);
      if (input == "END")
	 break;
      if (!isdigit(input[0]))
      {
	 printf("Enter date in old format\n");
	 continue;
      }
      int dia, mes, ano;
      sscanf(input.c_str(), "%d-%d-%d", &ano, &mes, &dia);
      bool down = true;
	
      int dias = dateToDays(dia, mes, ano) - inicio;
      if (dias < 0)
      {
	 down = false;
	 dias = -dias;
	 int year = updateYears(dias);
	 if (isLeapYear(year))
	    dias = 367 - dias;
	 else
	    dias = 366 - dias;
	 if (dias > 360)
	 {
	    printf("Feast %d-%dbd\n", (dias-360), year);
	    continue;
	 }
	 calculValues(dias, down, year);
      }
      else
      {
	 dias++;
	 int year = updateYears(dias);
	 if (dias > 360)
	 {
	    printf("Feast %d-%d\n", (dias-360), year);
	    continue;
	 }
	 calculValues(dias, down, year);
      }
   }
}  
