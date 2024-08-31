#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

// Класс для хранения информации о компании
class Company
{
public:
    string name;     // название компании
    string owner;    // имя владельца компании
    string phone;    // номер телефона компании
    string address;  // адрес компании
    string activity; // род деятельности

    // Конструктор класса Company, который инициализирует все поля
    Company(string name, string owner, string phone, string address, string activity)
        : name(name), owner(owner), phone(phone), address(address), activity(activity) {}
};

// Класс Directory (Справочник), который будет содержать список компани и методы для работы с ними
class Directory
{
private:
    vector<Company> companies; // Вектор для хранения списка компаний

    // Метод для загрузки данных о компаниях из файла
    void loadFromFile(const string& filename)
    {
        ifstream file(filename); // Открываем файл для чтения
        if (file.is_open()) // проверяем, удалось ли откр файл
        {
                string name, owner, phone, address, activity;
                // Считываем данные из файла и добавляем компании в вектор
                while (file >> name >> owner >> phone >> address >> activity)
                {
                    companies.emplace_back(name, owner, phone, address, activity);
                }
                file.close(); // Закрываем файл после чтения
        }
    }

    // Мето для сохранения данных о компаниях в файл
    void saveToFile(const string& filename)
    {
        ofstream file(filename, ios::app); // открываем файл для записи в конец
        if (file.is_open()) // проверяем, удалось ли открыть файл
        {
            // проходим по вектору и записываем данные о каждой компании в файл
            for (const auto& company : companies)
            {
                file << company.name << " " << company.owner << " " << company.phone << " "
                     << company.address << " " << company.activity << endl;
            }
            file.close(); // закрываем файл после записи
        }
    }

public:
    // Конструктор класса Directory, который сохраняет данные в файл при завершении работы программы
    ~Directory()
    {
        saveToFile("directory.txt");
    }

    // Метод для добавления новой компании в справочник
    void addCompany(const Company& company)
    {
        companies.push_back(company); // добавляем компанию в вектор
    }

    // Метод для поиска компании по названию
    void searchByName(const string& name) const
    {
        // Проходим по всем компания и выводим информацию о тех, чье название совпадает с искомым
        for (const auto& company : companies)
        {
            if (company.name == name)
            {
                printCompany(company);
            }
        }
    }

    // Метод для поиска компании по владельцу
    void searchByOwner(const string& owner) const
    {
        // Проходим по всем компаниям и выводим информацию о тех, чей владелец совпадает с искомым
        for (const auto& company : companies)
        {
            if (company.owner == owner)
            {
                printCompany(company);
            }
        }
    }

    // Метод для поиска компании по номеру телефона
    void searchByPhone(const string& phone) const
    {
        // Проходим по всем компаниям и выводим информацию о тех, чей номер телефона совпадает с искомым
        for (const auto& company : companies)
        {
            if (company.phone == phone)
            {
                printCompany(company);
            }
        }
    }

    // Метод для поиска компании по роду деятельности
    void searchByActivity(const string& activity) const
    {
        // Проходим по всем компаниям и выводим инф о тех, чей род деятельности совпадает с искомым
        for (const auto& company : companies)
        {
            if (company.activity == activity)
            {
                printCompany(company);
            }
        }
    }

    // Метод для вывода информации обо всех компаниях в справочнике
    void printAllCompanies() const
    {
        // проходим по всем кмопаниям и выводим инф о каждой
        for (const auto& company : companies)
        {
            printCompany(company);
        }
    }

private:
    // вспомогательный метод для вывода инф о компании
    void printCompany(const Company& company) const
    {
        cout << "Name: " << company.name << "\nOwner: " << company.owner << "\nPhone: "
             << company.phone << "\nAddress: " << company.address << "\nActivity: "
             << company.activity << endl;
        cout << "-------------------------------" << endl;
    }
};


int main() {
    Directory directory; // создаем объект справочника, который автом загрузит данные из файла

    // Добавляем примеры компаний в справочник
    directory.addCompany(Company("Apple", "Tim Cook", "+1-800-275-2273", "Cupertino, CA", "Technology"));
    directory.addCompany(Company("Microsoft", "Satya Nadella", "+1-425-882-8080", "Redmond, WA", "Software"));

    // Выводим все компании, содержащиеся в справочнике
    cout << "All companies in the directory: " << endl;
    directory.printAllCompanies();

    // Поиск компании по владельцу
    cout << "\nSearch by owner 'Tim Cook':" << endl;
    directory.searchByOwner("Tim Cook");

    // Поиск компании по роду деятельности
    cout << "\nSearch by activity 'Technology':" << endl;
    directory.searchByActivity("Technology");

    return 0;
}
