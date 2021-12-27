#include "Worth.h"

int _count_elem;
int print_menu(int key)
{
	string menu[]{ "\t\t\tВыберите пункт меню:", "\t\t\t1.Вывести содержимое сейфа на экран.", "\t\t\t2.Вывести общую сумму.",
				   "\t\t\t3.Вывести самую маленькую сумму." , "\t\t\t4.Вывод суммы по каждому виду ценности с указанием доли от общего богатства.",
				   "\t\t\t5.Вывести содержимое сейфа в файл.", "\t\t\t7.Закончить работу с программой." };
	int _count_elem = sizeof(menu) / sizeof(string);
	if (key != 1)
		for (int i = 0; i < _count_elem; i++)
		{
			cout << menu[i] << endl;
		}
	return _count_elem - 1;
}

Safe new_class()
{
	string user_choise;
	cout << "Ручное создание сейфа (Manual) или из файла (File) ?" << endl;
	getline(cin, user_choise);
	if (user_choise == "Manual")
	{
		cout << "Введите число элементов: \n>";
		cin >> _count_elem;
		Safe _MySafe(_count_elem);
		cin >> _MySafe;
		return _MySafe;
	}
	else if (user_choise == "File")
	{
		string in_file_name;
		cout << "\nВведите название файла для ввода (Пример: F:\\temp\\hello.txt): \n ";
		cin >> in_file_name;
		ifstream F;
		F.open(in_file_name);
		if (F)
		{
			F >> _count_elem;
			Safe _MySafe(_count_elem);
			F >> _MySafe;
			return _MySafe;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int count_elem = print_menu(1), variant = 0;
	string user_choise;
	Safe MySafe(new_class());
	do
	{
		print_menu(0);
	bad_inp:
		try {
			cin >> variant;
		}
		catch (...) {
			cout << "Ошибка ввода, повторите попытку: " << endl;
			goto bad_inp;
		}
		switch (variant)
		{
		case 1: cout << MySafe;
			break;
		case 2: cout << MySafe.total_amount() << endl;
			break;
		case 3: cout << MySafe.smallest_amount() << endl;
			break;
		case 4:
		{
			int a, c;
			double b, d;
			tie(a, b, c, d) = MySafe.share_of_total_amount();
			cout << "Золото: " << a << " Доля золота: " << b << " Акции: " << c << " Доля акций: " << d << endl;
		}
		break;
		case 5:
		{
			string in_file_name;
			cout << "\nВведите название файла для вывода (Пример: F:\\temp\\bye.txt): \n ";
			cin >> in_file_name;
			ofstream F;
			F.open(in_file_name);
			F << MySafe;
		}
		break;
		default:
			break;
		}
	} while (variant != count_elem);
	return 0;
}