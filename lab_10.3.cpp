#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <windows.h>

using namespace std;

struct Tovar {
    string name;
    string store;
    double price;
    int quantity;
    string unit;
};

void AddTovar(vector<Tovar>& tovars);
void RemoveTovar(vector<Tovar>& tovars);
void EditTovar(vector<Tovar>& tovars);
void SortTovars(vector<Tovar>& tovars, bool byName);
void PrintTovarByName(const vector<Tovar>& tovars);
void PrintTovarsByStore(const vector<Tovar>& tovars);
void SaveToFile(const vector<Tovar>& tovars, const string& filename);
void LoadFromFile(vector<Tovar>& tovars, const string& filename);
void PrintMenu();

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<Tovar> tovars;
    int choice;

    do {
        PrintMenu();
        cout << "Введіть номер дії: ";
        cin >> choice;

        switch (choice) {
        case 1:
            AddTovar(tovars);
            break;
        case 2:
            RemoveTovar(tovars);
            break;
        case 3:
            EditTovar(tovars);
            break;
        case 4:
            SortTovars(tovars, true);
            break;
        case 5:
            SortTovars(tovars, false);
            break;
        case 6:
            PrintTovarByName(tovars);
            break;
        case 7:
            PrintTovarsByStore(tovars);
            break;
        case 8: {
            string filename;
            cout << "Введіть ім'я файлу для збереження: ";
            cin >> filename;
            SaveToFile(tovars, filename);
            break;
        }
        case 9: {
            string filename;
            cout << "Введіть ім'я файлу для зчитування: ";
            cin >> filename;
            LoadFromFile(tovars, filename);
            break;
        }
        case 0:
            cout << "Завершення роботи програми.\n";
            break;
        default:
            cout << "Неправильний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 0);

    return 0;
}

void PrintMenu() {
    cout << "\nМеню:\n"
        << "1. Додати товар\n"
        << "2. Видалити товар\n"
        << "3. Редагувати товар\n"
        << "4. Сортувати за назвою товару\n"
        << "5. Сортувати за назвою магазину\n"
        << "6. Знайти товар за назвою\n"
        << "7. Знайти товари за назвою магазину\n"
        << "8. Зберегти у файл\n"
        << "9. Завантажити з файлу\n"
        << "0. Вихід\n";
}

void AddTovar(vector<Tovar>& tovars) {
    Tovar t;
    cin.ignore();
    cout << "Введіть назву товару: ";
    getline(cin, t.name);
    cout << "Введіть назву магазину: ";
    getline(cin, t.store);
    cout << "Введіть вартість товару: ";
    cin >> t.price;
    cout << "Введіть кількість товару: ";
    cin >> t.quantity;
    cin.ignore();
    cout << "Введіть одиницю вимірювання: ";
    getline(cin, t.unit);
    tovars.push_back(t);
}

void RemoveTovar(vector<Tovar>& tovars) {
    string name;
    cin.ignore();
    cout << "Введіть назву товару для видалення: ";
    getline(cin, name);

    auto it = remove_if(tovars.begin(), tovars.end(), [&name](const Tovar& t) {
        return t.name == name;
        });

    if (it != tovars.end()) {
        tovars.erase(it, tovars.end());
        cout << "Товар видалено.\n";
    }
    else {
        cout << "Товар не знайдено.\n";
    }
}

void EditTovar(vector<Tovar>& tovars) {
    string name;
    cin.ignore();
    cout << "Введіть назву товару для редагування: ";
    getline(cin, name);

    for (auto& t : tovars) {
        if (t.name == name) {
            cout << "Введіть нову назву товару: ";
            getline(cin, t.name);
            cout << "Введіть нову назву магазину: ";
            getline(cin, t.store);
            cout << "Введіть нову вартість товару: ";
            cin >> t.price;
            cout << "Введіть нову кількість товару: ";
            cin >> t.quantity;
            cin.ignore();
            cout << "Введіть нову одиницю вимірювання: ";
            getline(cin, t.unit);
            return;
        }
    }
    cout << "Товар не знайдено.\n";
}

void SortTovars(vector<Tovar>& tovars, bool byName) {
    if (byName) {
        sort(tovars.begin(), tovars.end(), [](const Tovar& a, const Tovar& b) {
            return a.name < b.name;
            });
        cout << "Список відсортовано за назвою товару.\n";
    }
    else {
        sort(tovars.begin(), tovars.end(), [](const Tovar& a, const Tovar& b) {
            return a.store < b.store;
            });
        cout << "Список відсортовано за назвою магазину.\n";
    }
}

void PrintTovarByName(const vector<Tovar>& tovars) {
    string name;
    cin.ignore();
    cout << "Введіть назву товару: ";
    getline(cin, name);

    for (const auto& t : tovars) {
        if (t.name == name) {
            cout << "Назва товару: " << t.name << "\n"
                << "Магазин: " << t.store << "\n"
                << "Ціна: " << t.price << " грн\n"
                << "Кількість: " << t.quantity << " (" << t.unit << ")\n";
            return;
        }
    }
    cout << "Товар не знайдено.\n";
}

void PrintTovarsByStore(const vector<Tovar>& tovars) {
    string store;
    cin.ignore();
    cout << "Введіть назву магазину: ";
    getline(cin, store);

    for (const auto& t : tovars) {
        if (t.store == store) {
            cout << "Назва товару: " << t.name << "\n"
                << "Магазин: " << t.store << "\n"
                << "Ціна: " << t.price << " грн\n"
                << "Кількість: " << t.quantity << " (" << t.unit << ")\n";
        }
    }
}

void SaveToFile(const vector<Tovar>& tovars, const string& filename) {
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cout << "Помилка відкриття файлу для запису.\n";
        return;
    }

    size_t size = tovars.size();
    fout.write(reinterpret_cast<const char*>(&size), sizeof(size));

    for (const auto& t : tovars) {
        size_t len;

        len = t.name.size();
        fout.write(reinterpret_cast<const char*>(&len), sizeof(len));
        fout.write(t.name.c_str(), len);

        len = t.store.size();
        fout.write(reinterpret_cast<const char*>(&len), sizeof(len));
        fout.write(t.store.c_str(), len);

        fout.write(reinterpret_cast<const char*>(&t.price), sizeof(t.price));
        fout.write(reinterpret_cast<const char*>(&t.quantity), sizeof(t.quantity));

        len = t.unit.size();
        fout.write(reinterpret_cast<const char*>(&len), sizeof(len));
        fout.write(t.unit.c_str(), len);
    }

    fout.close();
    cout << "Дані збережено у файл.\n";
}


void LoadFromFile(vector<Tovar>& tovars, const string& filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cout << "Помилка відкриття файлу для зчитування.\n";
        return;
    }

    size_t size;
    fin.read(reinterpret_cast<char*>(&size), sizeof(size));

    tovars.clear();
    for (size_t i = 0; i < size; ++i) {
        Tovar t;
        size_t len;

        fin.read(reinterpret_cast<char*>(&len), sizeof(len));
        t.name.resize(len);
        fin.read(&t.name[0], len);

        fin.read(reinterpret_cast<char*>(&len), sizeof(len));
        t.store.resize(len);
        fin.read(&t.store[0], len);

        fin.read(reinterpret_cast<char*>(&t.price), sizeof(t.price));
        fin.read(reinterpret_cast<char*>(&t.quantity), sizeof(t.quantity));

        fin.read(reinterpret_cast<char*>(&len), sizeof(len));
        t.unit.resize(len);
        fin.read(&t.unit[0], len);

        tovars.push_back(t);
    }

    fin.close();
    cout << "Дані завантажено з файлу.\n";
}