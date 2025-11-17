#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <math.h>

struct date {
	int day;
	int month;
	int year;
};
typedef struct date Date;

struct employee {
	char surname[100];
	char name[100];
	char secondname[100];
	char post[100];
	double salary;
	Date birthdate;
};
typedef struct employee Emp;

void input_emp(Emp* A);
int calc_age(Date A);
double calc_av_salary(Emp employees[], int count);
void print_filtered_employees(Emp employees[], int count);
void print_employee(Emp A);
void print_all_employees(Emp employees[], int count);

int main()
{
	system("chcp 1251");
	Emp employees[100];
	int choice, count = 0;
	puts("_____СОТРУДНИКИ_____\n");
	do {
		puts("_____Меню_____\n");
		puts("1 - Добавить сотрудника\n");
		puts("2 - Вывести всех сотрудников\n");
		puts("3 - Вывести сотрудников с зарплатой выше средней и возрастом < 30 лет\n");
		puts("4 - Выйти\n");
		puts("Выберите действие:\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1: input_emp(&employees[count]); count += 1; break;
		case 2: print_all_employees(employees, count); break;
		case 3: print_filtered_employees(employees, count); break;
		case 4: break;
		}
	} while (choice != 4);
	return 0;
}

void input_emp(Emp* A) 
{
	puts("Введите фамилию:");
	scanf("%s", A->surname);
	puts("Введите имя:");
	scanf("%s", A->name);
	puts("Введите отчество:");
	scanf("%s", A->secondname);
	puts("Введите должность:");
	scanf("%s", A->post);
	puts("Введите зарплату:");
	scanf("%lf", &A->salary);
	puts("Введите дату рождения (день, месяц, год через пробел):");
	scanf("%d %d %d", &A->birthdate.day, &A->birthdate.month, &A->birthdate.year);
}

int calc_age(Date A)
{
	int age = 2025 - A.year;
	return age;
}

double calc_av_salary(Emp employees[], int count)
{
	if (count == 0) return 0;
	double total = 0;
	for (int i = 0; i < count; i++) {
		total += employees[i].salary;
	}
	return total / count;

}

void print_employee(Emp A)
{
	printf("Фамилия: %s\n", A.surname);
	printf("Имя: %s\n", A.name);
	printf("Отчество: %s\n", A.secondname);
	printf("Должность: %s\n", A.post);
	printf("Зарплата: %.2f\n", A.salary);
	printf("Дата рождения: %02d.%02d.%d\n",
		A.birthdate.day, A.birthdate.month, A.birthdate.year);
	printf("Возраст: %d лет\n", calc_age(A.birthdate));
	printf("------------------------\n");
}

void print_filtered_employees(Emp employees[], int count)
{
	if (count == 0) {
		printf("Нет данных о сотрудниках.\n");
		return;
	}

	double av_salary = calc_av_salary(employees, count);
	printf("Средняя зарплата: %.2f\n", av_salary);

	int found = 0;
	puts("Сотрудники с зарплатой выше средней и возрастом менее 30 лет:\n");
	puts("-------------------------------------------------------------\n");
	for (int i = 0; i < count; i++) {
		int age = calc_age(employees[i].birthdate);
		if (employees[i].salary > av_salary && age < 30) {
			print_employee(employees[i]);
			found = 1;
		}
	}
	if (!found) puts("Сотрудники не найдены.\n");
}

void print_all_employees(Emp employees[], int count) 
{
	if (count == 0) {
		printf("Нет данных о сотрудниках.\n");
		return;
	}

	printf("Все сотрудники:\n");
	puts("---------------\n");
	for (int i = 0; i < count; i++) {
		print_employee(employees[i]);
		puts("---------------\n");
	}
}