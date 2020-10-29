#include <iostream>
#include "class_list.h"
#include <string>




struct DATE
{
	int Day;
	int Month;
	int Year;
	DATE() {}
	bool operator==(const DATE& Date)
	{
		if (Day == Date.Day && Month == Date.Month && Year == Date.Year)
			return true;
		return false;
	}
	bool operator<(const DATE& Date)
	{
		if (Year < Date.Year)
			return true;
		if (Year == Date.Year && Month < Date.Month)
			return true;
		if (Year == Date.Year && Month == Date.Month && Day < Date.Day)
			return true;
		return false;
	}
};

struct INITIALS
{
	std::string FirstName;
	std::string LastName;
	std::string Patronymic;
	INITIALS() {}
	bool operator==(const INITIALS& Init)
	{
		if (FirstName == Init.FirstName && LastName == Init.LastName && Patronymic == Init.Patronymic)
			return true;
		return false;
	}
	std::string ToString()
	{
		return FirstName + LastName + Patronymic;
	}
};

struct NOTE
{
	INITIALS Initials;
	std::string PhoneNumber;
	DATE BirthdayDate;
	NOTE() {}
	bool operator==(const NOTE& Note)
	{
		if (Initials == Note.Initials && BirthdayDate == Note.BirthdayDate)
			return true;
		return false;
	}
};

DATE StringToDate(std::string Data)
{
	DATE Date;
	Date.Day = atoi(Data.substr(0, Data.find_first_of('.')).c_str());
	Data.erase(0, Data.find_first_of('.') + 1);
	Date.Month = atoi(Data.substr(0, Data.find_first_of('.')).c_str());
	Data.erase(0, Data.find_first_of('.') + 1);
	Date.Year = atoi(Data.c_str());
	return Date;
}

INITIALS EnterInitials()
{
	std::string Data;
	INITIALS Initials;
	std::cout << "\nВведите Имя:\n";
	std::cin >> Data;
	Initials.FirstName = Data;
	std::cout << "\nВведите Фамилию:\n";
	std::cin >> Data;
	Initials.LastName = Data;
	std::cout << "\nВведите Отчество:\n";
	std::cin >> Data;
	Initials.Patronymic = Data;
	return Initials;
}

std::string NOTEToString(NOTE Note)
{
	return "Фио: " + Note.Initials.FirstName + ' ' + Note.Initials.LastName + ' ' + Note.Initials.Patronymic + '\n'
		+ "Дата рождения: " + std::to_string(Note.BirthdayDate.Day) + '.' + std::to_string(Note.BirthdayDate.Month) + '.' + std::to_string(Note.BirthdayDate.Year) + '\n'
		+ "Номер телефона: " +  Note.PhoneNumber;
}

void sort(list<NOTE>& Notebook, int SelectedMode)
{
	switch (SelectedMode)
	{
	case 1:
		for (list<NOTE>::const_iterator it1 = Notebook.begin(); ++it1 != Notebook.end();)
			for (list<NOTE>::const_iterator it2 = it1; it2 != Notebook.end(); ++it2)
				if ((*(--it2)).Initials.ToString() < (*(it2)).Initials.ToString())
					std::swap(it1, it2);
		break;
	case 2:
		for (list<NOTE>::const_iterator it1 = Notebook.begin(); ++it1 != Notebook.end();)
			for (list<NOTE>::const_iterator it2 = it1; it2 != Notebook.end(); ++it2)
				if ((*(--it2)).BirthdayDate < (*(it2)).BirthdayDate)
					std::swap(it1, it2);
		break;
	case 3:
		for (list<NOTE>::const_iterator it1 = Notebook.begin(); ++it1 != Notebook.end();)
			for (list<NOTE>::const_iterator it2 = it1; it2 != Notebook.end(); ++it2)
				if ((*(--it2)).PhoneNumber < (*(it2)).PhoneNumber)
					std::swap(it1, it2);
		break;
	}
}

int main()
{
	setlocale(0, "ru");
	list<NOTE> Notebook;
	int SelectedMode = 1;

	while (SelectedMode)
	{
		for (list<NOTE>::const_iterator it = Notebook.begin(); it != Notebook.end(); ++it)
			std::cout << '\n' + NOTEToString(*it) + '\n';
		std::cout << "Введите 1, чтобы добавить запись;\nВведите 2, чтобы удалить запись;\nВведите 3, чтобы отсортировать записи по полю;\nВведите 0, чтобы выйти:\n";
		//std::cin.ignore('\n');
		std::cin >> SelectedMode;
		switch (SelectedMode)
		{
		case 1:
		{
			std::string Data;
			Notebook.push_back(NOTE());
			Notebook.back().Initials = EnterInitials();
			std::cout << "\nВведите дату рождения (ДД.ММ.ГГГГ):\n";
			std::cin >> Data;
			Notebook.back().BirthdayDate = StringToDate(Data);
			std::cout << "\nВведите номер телефона (все цифры подряд):\n";
			std::cin >> Data;
			Notebook.back().PhoneNumber = Data;
			break;
		}
		case 2:
		{
			std::cout << "\nВведите параметры поиска:\n";
			std::string Data;
			NOTE Note;
			Note.Initials = EnterInitials();
			std::cout << "\nВведите дату рождения (ДД.ММ.ГГГГ):\n";
			std::cin >> Data;
			Note.BirthdayDate = StringToDate(Data);
			list<NOTE>::iterator it = Notebook.find(Note);
			if (it != nullptr) //?????
				Notebook.erase(it);
			break;
		}
		case 3:
		{
			std::cout << "Поле сортировки: 1 - ФИО; 2 - дата рождения; 3 - телефон\n";
			std::cin >> SelectedMode;
			sort(Notebook, SelectedMode);
			break;
		}
		}
	}	
	system("pause");
	return 0;
}