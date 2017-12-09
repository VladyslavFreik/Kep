/*24.	Підготувати дані, що містять інформацію про Автопродаж.Дані оформити у вигляді запису, що містить наступні поля :
?	 Марка автомобіля,
?	 Дата постачання,
?	 Кількість,
?	 Ціна закупки,
?	 Ціна продажу.
Кількість записів довільна.Створити програму запису підготовлених даних до зовнішнього файлу і програму обробки цього зовнішнього файлу, що виконує наступні операції :
-Виводить на екран введені дані
-Додає n записів в початок або кінець файлу;
-Видаляє всі дані про автомобілі, марку якого задано користувачем, і виводить на екран оновлений вміст файлу;
-Сортує дані автомобілів по даті постачання від найновіших до найстаріших;
-Список автомобілів, що найдовше продаються;
-Список найдорожчих автомобілів по закупочній ціні;
-Список трьох марок автомобілів, де закупочна ціна найбільше відрізняється від ціни продажу.*/

#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <conio.h>									
#include <stdlib.h>								
#include <locale>
#include <stdio.h>
#include <string.h> 
#include <iostream>
#include <cstdio>
#include <Windows.h>
#include <Wincon.h>


int e = 0;                        //поточна к-сть записів структури

struct Cars
{
	char car_brand[20];
	int day;
	int	month;
	int	year;
	int Count;
	double purchase_price;
	double selling_price;
};

Cars tva[100];                     
FILE *l;

int audit(char x[])
{
	int i, y;
	for (i = 0; i < strlen(x); i++)
		if (isdigit(x[i]) == 0)
		{
			printf("Помилка! Введені символи:\n");
			y = -1;
			system("pause");
			return y;
		}
		else
			y = atoi(x);
	return y;
}







void print_line()
{
	printf("\t|———————————————————————————————————————————————————————————————————————————————————|\n");


}


void print_head()
{
	printf("\n");
	printf("\t|———————————————————————————————————————————————————————————————————————————————————|\n");
	printf("\t|                                  АВТОПРОДАЖ                                       |\n");
	printf("\t|———————————————————————————————————————————————————————————————————————————————————|\n");
	printf("\t|  № |    Марка автомобіля |    Дата    | Кількість |  Ціна закупки |  Ціна продажу |\n");
	printf("\t|    |                     | постачання |           |               |               |\n");
	printf("\t|————|—————————————————————|————————————|———————————|———————————————|-——————————————|\n");
}



void scanning()
{
	FILE * l = fopen("avto.txt", "r+");
	do
	{
		fscanf(l, "%s %i %i %i %i %lf %lf", &tva[e].car_brand, &tva[e].day, &tva[e].month, &tva[e].year, &tva[e].Count, &tva[e].purchase_price, &tva[e].selling_price);
		e++;
	} while (!feof(l));
	fclose(l);
}



void output()
{

	system("cls");

	print_head();

	for (int i = 0; i < e; i++)

		printf("\t|  %-2i| %-20s| %02i/%02i/%-2i | %8i  | %12.2lf  | %12.2lf  |\n", i + 1, tva[i].car_brand, tva[i].day, tva[i].month, tva[i].year, tva[i].Count, tva[i].purchase_price, tva[i].selling_price);
	print_line();


}


void delete_car_brand()
{
	char nazz[25];

	printf("\n\tВведіть марку автомобіля яку хочете видалити: ");
	scanf("%s", nazz);
	system("cls");
	int i = 0;

	FILE* l = fopen("avto.txt", "r");

	do {
		fscanf(l, "%s %i %i %i %i %lf %lf", &tva[i].car_brand, &tva[i].day, &tva[i].month, &tva[i].year, &tva[i].Count, &tva[i].purchase_price, &tva[i].selling_price);
		i++;
	} while (!feof(l));

	e = i;
	

	int gg = 1;

	fclose(l);



	for (int j = 0; j < e; j++)
	{
	
		if (strcmp(tva[j].car_brand, nazz) == 0)
		{
			for (int i = j; i < e; i++)
			{
				strcpy(tva[i].car_brand, tva[i + 1].car_brand);
				tva[i].day = tva[i + 1].day;
				tva[i].month = tva[i + 1].month;
				tva[i].year = tva[i + 1].year;
				tva[i].Count = tva[i + 1].Count;
				tva[i].purchase_price = tva[i + 1].purchase_price;
				tva[i].selling_price = tva[i + 1].selling_price;
			}
			gg = 0;
			e -= 1;
		}
	}

	if (gg)
	{
		printf(" Такої назви не знайдено!\n");
		_getch();
		return;
	}

	l = fopen("avto.txt", "w");

	for (int i = 0; i < e; i++)
	{
		if (strcmp(tva[i].car_brand, nazz) != 0)
		{
			fprintf(l, "\n%s ", &tva[i].car_brand);
			fprintf(l, "%i ", tva[i].day);
			fprintf(l, "%i ", tva[i].month);
			fprintf(l, "%i ", tva[i].year);
			fprintf(l, "%i ", tva[i].Count);
			fprintf(l, "%lf ", tva[i].purchase_price);
			fprintf(l, "%lf", tva[i].selling_price);
		}
	}
	fclose(l);
}


int convert(int i)
{
	int full = tva[i].year * 10000 + tva[i].month * 100 + tva[i].day;


	return full;
}

void sort()
{
	int i = 0;

	FILE* l = fopen("avto.txt", "r");

	do {
		fscanf(l, "%s %i %i %i %i %lf %lf", &tva[i].car_brand, &tva[i].day, &tva[i].month, &tva[i].year, &tva[i].Count, &tva[i].purchase_price, &tva[i].selling_price);
		i++;
	} while (!feof(l));

	e = i;
	Cars p;

	int is = 0;
	do
	{
		is = 0;

		for (int i = 1; i < e; i++)
		{
			if (convert(i - 1) < convert(i))
			{
				strcpy(p.car_brand, tva[i].car_brand);
				strcpy(tva[i].car_brand, tva[i - 1].car_brand);
				strcpy(tva[i - 1].car_brand, p.car_brand);

				p.day = tva[i].day;
				tva[i].day = tva[i - 1].day;
				tva[i - 1].day = p.day;


				p.month = tva[i].month;
				tva[i].month = tva[i - 1].month;
				tva[i - 1].month = p.month;

				p.year = tva[i].year;
				tva[i].year = tva[i - 1].year;
				tva[i - 1].year = p.year;

				p.Count = tva[i].Count;
				tva[i].Count = tva[i - 1].Count;
				tva[i - 1].Count = p.Count;

				p.purchase_price = tva[i].purchase_price;
				tva[i].purchase_price = tva[i - 1].purchase_price;
				tva[i - 1].purchase_price = p.purchase_price;

				p.selling_price = tva[i].selling_price;
				tva[i].selling_price = tva[i - 1].selling_price;
				tva[i - 1].selling_price = p.selling_price;

				is = 1;
			}
		}
	} while (is);
}


void output_date_purchase()
{

	int i = e, r, naid, m;

	int j, k;
	for (int i = 1; i < e; i++)
		for (j = e - 1; j >= i; j--)
		{
			if (tva[j - 1].year > tva[j].year) std::swap(tva[j - 1], tva[j]);
		}
	for (int i = 1; i < e; i++)
		for (j = e - 1; j >= i; j--)
		{
			if (tva[j - 1].year == tva[j].year)
			{
				if (tva[j - 1].month > tva[j].month) std::swap(tva[j - 1], tva[j]);
			}
		}

	for (int i = 1; i < e; i++)
		for (j = e - 1; j >= i; j--)
		{
			if (tva[j - 1].year == tva[j].year)
			{
				if (tva[j - 1].month == tva[j].month)
				{
					if (tva[j - 1].day > tva[j].day) std::swap(tva[j - 1], tva[j]);
				}
			}
		}
	int kilk;
	printf("Введіть яку кількість машин що найдовше продаються потрібно вивести - ");
	scanf("%i", &kilk);
	print_head();

	for (int i = 0; i < kilk; i++)
	{
		printf("\t|  %-2i| %-20s| %02i/%02i/%-2i | %8i  | %12.2lf  | %12.2lf  |\n", i + 1, tva[i].car_brand, tva[i].day, tva[i].month, tva[i].year, tva[i].Count, tva[i].purchase_price, tva[i].selling_price);
	}
	print_line();
	_getch();

}






void input_start(int n)
{
	int j;
	char day[100], month[100], year[100], Count[100], purchase_price[100], selling_price[100];

	for (int j = 0; j < n; j++)
	{
		printf("Введіть марку автомобіля:\n");
		scanf("%s", tva[j].car_brand);
	da:system("cls");
		printf("Введіть день постачання:\n");
		scanf("%s", day);
		audit(day);
		if (atoi(day) > 0 && atoi(day) <= 31)
		{
			tva[j].day = atoi(day);
		}
		else
		{
			goto da;
		}
	mo:system("cls");
		printf("Введіть місяць постачання(числом):\n");
		scanf("%s", month);
		audit(month);
		if (atoi(month) > 0 && atoi(month) <= 12)
		{
			tva[j].month = atoi(month);
		}
		else
		{
			goto mo;
		}
	yea:system("cls");
		printf("Введіть рік постачання:\n");
		scanf("%s", year);
		audit(year);
		if (atoi(year) > 1960 && atoi(year) <= 2017)
		{
			tva[j].year = atoi(year);
		}
		else
		{
			goto yea;
		}

	Co: system("cls");
		printf("Введіть кількість:\n");
		scanf("%s", Count);
		audit(Count);
		if (atoi(Count) > 0)
		{
			tva[j].Count = atoi(Count);
		}
		else
		{
			goto Co;
		}

	pur:system("cls");
		printf("Введіть ціну закупки:\n");
		scanf("%s", purchase_price);
		audit(purchase_price);
		if (atoi(purchase_price) > 0)
		{
			tva[j].purchase_price = atoi(purchase_price);
		}
		else
		{
			goto pur;
		}

	sell:system("cls");
		printf("Введіть ціну продажу:\n");
		scanf("%s", selling_price);
		audit(selling_price);
		if (atoi(selling_price) > 0)
		{
			tva[j].selling_price = atoi(selling_price);
		}
		else
		{
			goto sell;
		}

	}
	FILE* l = fopen("avto.txt", "r");
	int e = n;
	do {
		fscanf(l, "%s %i %i %i %i %lf %lf", &tva[e].car_brand, &tva[e].day, &tva[e].month, &tva[e].year, &tva[e].Count, &tva[e].purchase_price, &tva[e].selling_price);
		e++;
	} while (!feof(l));
	fclose(l);

	l = fopen("avto.txt", "w");
	for (int j = 0; j < e; j++)
	{
		fprintf(l, "\n%s ", &tva[j].car_brand);
		fprintf(l, "%i ", tva[j].day);
		fprintf(l, "%i ", tva[j].month);
		fprintf(l, "%i ", tva[j].year);
		fprintf(l, "%i ", tva[j].Count);
		fprintf(l, "%lf ", tva[j].purchase_price);
		fprintf(l, "%lf", tva[j].selling_price);
	}
	fclose(l);
}



void input_end(int n)
{
	char day[100], month[100], year[100], Count[100], purchase_price[100], selling_price[100];
	int i = 0;
	FILE* l = fopen("avto.txt", "r");

	do
	{
		fscanf(l, "%s %i %i %i %i %lf %lf", &tva[i].car_brand, &tva[i].day, &tva[i].month, &tva[i].year, &tva[i].Count, &tva[i].purchase_price, &tva[i].selling_price);
		i++;
	} while (!feof(l));

	fclose(l);

	l = fopen("avto.txt", "a+");

	for (int j = e; j < e + n; j++)
	{
		printf("Введіть марку автомобіля:\n");
		scanf("%s", tva[j].car_brand);

	da:system("cls");
		printf("Введіть день постачання:\n");
		scanf("%s", day);
		audit(day);

		if (atoi(day) > 0 && atoi(day) <= 31)
		{
			tva[j].day = atoi(day);
		}
		else
		{
			goto da;
		}

	mo:system("cls");
		printf("Введіть місяць постачання(числом):\n");
		scanf("%s", month);
		audit(month);
		if (atoi(month) > 0 && atoi(month) <= 12)
		{
			tva[j].month = atoi(month);
		}
		else
		{
			goto mo;
		}

	yea:system("cls");
		printf("Введіть рік постачання:\n");
		scanf("%s", year);
		audit(year);
		if (atoi(year) > 1960 && atoi(year) <= 2017)
		{
			tva[j].year = atoi(year);
		}
		else
		{
			goto yea;
		}

	Co: system("cls");
		printf("Введіть кількість:\n");
		scanf("%s", Count);
		audit(Count);
		if (atoi(Count) > 0)
		{
			tva[j].Count = atoi(Count);
		}
		else
		{
			goto Co;
		}

	pur:system("cls");
		printf("Введіть ціну закупки:\n");
		scanf("%s", purchase_price);
		audit(purchase_price);
		if (atoi(purchase_price) > 0)
		{
			tva[j].purchase_price = atoi(purchase_price);
		}
		else
		{
			goto pur;
		}

	sell:system("cls");
		printf("Введіть ціну продажу:\n");
		scanf("%s", selling_price);
		audit(selling_price);
		if (atoi(selling_price) > 0)
		{
			tva[j].selling_price = atoi(selling_price);
		}
		else
		{
			goto sell;
		}


		fprintf(l, "\n%s ", &tva[j].car_brand);
		fprintf(l, "%i ", tva[j].day);
		fprintf(l, "%i ", tva[j].month);
		fprintf(l, "%i ", tva[j].year);
		fprintf(l, "%i ", tva[j].Count);
		fprintf(l, "%lf ", tva[j].purchase_price);
		fprintf(l, "%lf", tva[j].selling_price);


		system("cls");
	}
	fclose(l);
}

void output_purchase_price()
{

	int i = e, r, naid, m;

	for (int i = 1; i < e; i++)
		for (m = e - 1; m >= i; m--)
		{
			if (tva[m - 1].purchase_price < tva[m].purchase_price) std::swap(tva[m - 1], tva[m]);
		}
	printf("Введіть кількість автомобілів - ");
	scanf("%i", &naid);

	print_head();

	for (int i = 0; i < naid; i++)
	{
		printf("\t|  %-2i| %-20s| %02i/%02i/%-2i | %8i  | %12.2lf  | %12.2lf  |\n", i + 1, tva[i].car_brand, tva[i].day, tva[i].month, tva[i].year, tva[i].Count, tva[i].purchase_price, tva[i].selling_price);
	}
	print_line();
	_getch();

}




void output_purchase_selling()
{

	int i = e, r, naid, m;

	for (int i = 1; i < e; i++)
		for (m = e - 1; m >= i; m--)
		{
			if ((tva[m].selling_price - tva[m].purchase_price) >(tva[m - 1].selling_price - tva[m - 1].purchase_price)) std::swap(tva[m - 1], tva[m]);
		}

	print_head();

	for (int i = 0; i < 3; i++)
	{
		printf("\t|  %-2i| %-20s| %02i/%02i/%-2i | %8i  | %12.2lf  | %12.2lf  |\n", i + 1, tva[i].car_brand, tva[i].day, tva[i].month, tva[i].year, tva[i].Count, tva[i].purchase_price, tva[i].selling_price);
	}
	print_line();
	_getch();

}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int q, n;
	char w[10];


	scanning();
a:system("cls");
	printf("\n");
	printf("\n                                     Програма керування базою даних\n");
	printf("\n                                                Автопродаж \n");
	printf("\n\t1.Вивести на екран всі дані ---------------------------------------------------------------------------- 1\n");
	printf("\n\t2.Додати запис в кінець або початок файлу -------------------------------------------------------------- 2\n");
	printf("\n\t3.Видалити дані про марку автомобіля ------------------------------------------------------------------- 3\n");
	printf("\n\t4.Сортує дані автомобілів по даті постачання від найновіших до найстаріших ----------------------------- 4\n");
	printf("\n\t5.Список автомобілів, що найдовше продаються ----------------------------------------------------------- 5\n");
	printf("\n\t6.Список найдорожчих автомобілів по закупочній ціні ---------------------------------------------------- 6\n");
	printf("\n\t7.Список трьох марок автомобілів, де закупочна ціна найбільше відрізняється від ціни продажу------------ 7\n");
	printf("\n\t0.Кінець виконання програми  --------------------------------------------------------------------------- 0\n");
	printf("\n\tВведіть число ---- ");


	scanf("%i", &q);


	switch (q)
	{

	case 1:
	{
		system("cls");
		output();
		system("pause");
		system("cls");
		goto a;
	}

	case 2:
	{
		while (true)
		{
			system("cls");
			printf("Кількість елементів - ");
			scanf("%i", &n);
			printf("В початок/1 або в кінець/2  = ");
		km:scanf("%s", w);
			audit(w);
			system("cls");

			if (atoi(w) == 2)
			{
				input_end(n);
				system("cls");
				e = 0;
				scanning();
				output();
				system("pause");
				system("cls");
				goto a;
			}
			char h[10];
			if (atoi(w) == 1)
			{
				input_start(n);
				system("cls");
				output();
				system("pause");
				system("cls");
				goto a;
			}

			else
			{

				printf("Ви ввели неправильні дані\n");
				printf("Ви хочете повторити введення  Так - 1/Ні - *\n");
				scanf("%s", h);
				audit(h);
				if (atoi(h) != 1)
				{
					break;
				}
			}

		}
		goto a;
	}
	case 3:
	{
		while (true)
		{
			system("cls");
			output();
			delete_car_brand();
			output();
			_getch();
			system("cls");

			printf("Ви хочете повторити видалення  Так - 1/Ні - *\n");
			char h[2];
			scanf("%s", h);
			audit(h);

			if (atoi(h) != 1)
			{
				break;
			}
			system("cls");
		}
		goto a;
	}
	case 4:
	{
		system("cls");
		sort();
		output();
		system("pause");
		system("cls");
		goto a;
	}

	case 5:
	{
		system("cls");
		output_date_purchase();
		goto a;
	}

	case 6:
	{
		system("cls");
		output_purchase_price();
		goto a;
	}

	case 7:
	{
		system("cls");
		output_purchase_selling();
		goto a;
	}
	case 0:
	{

		break;
	}

	default: system("cls");
		printf("Ви ввели неправильне число повторіть спробу\n");
		_getch();
		goto a;

	}


	return 0;
}