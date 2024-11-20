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
        cout << "������ ����� 䳿: ";
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
            cout << "������ ��'� ����� ��� ����������: ";
            cin >> filename;
            SaveToFile(tovars, filename);
            break;
        }
        case 9: {
            string filename;
            cout << "������ ��'� ����� ��� ����������: ";
            cin >> filename;
            LoadFromFile(tovars, filename);
            break;
        }
        case 0:
            cout << "���������� ������ ��������.\n";
            break;
        default:
            cout << "������������ ����. ��������� �� ���.\n";
        }
    } while (choice != 0);

    return 0;
}

void PrintMenu() {
    cout << "\n����:\n"
        << "1. ������ �����\n"
        << "2. �������� �����\n"
        << "3. ���������� �����\n"
        << "4. ��������� �� ������ ������\n"
        << "5. ��������� �� ������ ��������\n"
        << "6. ������ ����� �� ������\n"
        << "7. ������ ������ �� ������ ��������\n"
        << "8. �������� � ����\n"
        << "9. ����������� � �����\n"
        << "0. �����\n";
}

void AddTovar(vector<Tovar>& tovars) {
    Tovar t;
    cin.ignore();
    cout << "������ ����� ������: ";
    getline(cin, t.name);
    cout << "������ ����� ��������: ";
    getline(cin, t.store);
    cout << "������ ������� ������: ";
    cin >> t.price;
    cout << "������ ������� ������: ";
    cin >> t.quantity;
    cin.ignore();
    cout << "������ ������� ����������: ";
    getline(cin, t.unit);
    tovars.push_back(t);
}

void RemoveTovar(vector<Tovar>& tovars) {
    string name;
    cin.ignore();
    cout << "������ ����� ������ ��� ���������: ";
    getline(cin, name);

    auto it = remove_if(tovars.begin(), tovars.end(), [&name](const Tovar& t) {
        return t.name == name;
        });

    if (it != tovars.end()) {
        tovars.erase(it, tovars.end());
        cout << "����� ��������.\n";
    }
    else {
        cout << "����� �� ��������.\n";
    }
}

void EditTovar(vector<Tovar>& tovars) {
    string name;
    cin.ignore();
    cout << "������ ����� ������ ��� �����������: ";
    getline(cin, name);

    for (auto& t : tovars) {
        if (t.name == name) {
            cout << "������ ���� ����� ������: ";
            getline(cin, t.name);
            cout << "������ ���� ����� ��������: ";
            getline(cin, t.store);
            cout << "������ ���� ������� ������: ";
            cin >> t.price;
            cout << "������ ���� ������� ������: ";
            cin >> t.quantity;
            cin.ignore();
            cout << "������ ���� ������� ����������: ";
            getline(cin, t.unit);
            return;
        }
    }
    cout << "����� �� ��������.\n";
}

void SortTovars(vector<Tovar>& tovars, bool byName) {
    if (byName) {
        sort(tovars.begin(), tovars.end(), [](const Tovar& a, const Tovar& b) {
            return a.name < b.name;
            });
        cout << "������ ����������� �� ������ ������.\n";
    }
    else {
        sort(tovars.begin(), tovars.end(), [](const Tovar& a, const Tovar& b) {
            return a.store < b.store;
            });
        cout << "������ ����������� �� ������ ��������.\n";
    }
}

void PrintTovarByName(const vector<Tovar>& tovars) {
    string name;
    cin.ignore();
    cout << "������ ����� ������: ";
    getline(cin, name);

    for (const auto& t : tovars) {
        if (t.name == name) {
            cout << "����� ������: " << t.name << "\n"
                << "�������: " << t.store << "\n"
                << "ֳ��: " << t.price << " ���\n"
                << "ʳ������: " << t.quantity << " (" << t.unit << ")\n";
            return;
        }
    }
    cout << "����� �� ��������.\n";
}

void PrintTovarsByStore(const vector<Tovar>& tovars) {
    string store;
    cin.ignore();
    cout << "������ ����� ��������: ";
    getline(cin, store);

    for (const auto& t : tovars) {
        if (t.store == store) {
            cout << "����� ������: " << t.name << "\n"
                << "�������: " << t.store << "\n"
                << "ֳ��: " << t.price << " ���\n"
                << "ʳ������: " << t.quantity << " (" << t.unit << ")\n";
        }
    }
}

void SaveToFile(const vector<Tovar>& tovars, const string& filename) {
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cout << "������� �������� ����� ��� ������.\n";
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
    cout << "��� ��������� � ����.\n";
}


void LoadFromFile(vector<Tovar>& tovars, const string& filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cout << "������� �������� ����� ��� ����������.\n";
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
    cout << "��� ����������� � �����.\n";
}