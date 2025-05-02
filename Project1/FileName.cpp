#include <iostream>
#include <vector>
#include <list>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;

struct ComputingCenter {
    int labID;
    string proctype;
    int ramsize;
    int disksize;
    string montype;

    void print() const {
        cout << "Номер лаборатории: " << labID << endl;
        cout << "Тип процессора: " << proctype << endl;
        cout << "Объем ОЗУ (ГБ): " << ramsize << endl;
        cout << "Емкость диска (ГБ): " << disksize << endl;
        cout << "Тип монитора: " << montype << endl;
        cout << "--------------------------" << endl;
    }

    void input() {
        cout << "Номер лаборатории: ";
        while (!(cin >> labID)) {
            cin.clear();
            cin.ignore();
            cout << "Ошибка! Введите целое число: ";
        }

        cout << "Тип процессора: ";
        cin >> proctype;

        cout << "Объем ОЗУ (ГБ): ";
        while (!(cin >> ramsize) || ramsize <= 0) {
            cin.clear();
            cin.ignore();
            cout << "Ошибка! Введите положительное число: ";
        }

        cout << "Емкость диска (ГБ): ";
        while (!(cin >> disksize) || disksize <= 0) {
            cin.clear();
            cin.ignore();
            cout << "Ошибка! Введите положительное число: ";
        }

        cout << "Тип монитора: ";
        cin >> montype;
        cin.ignore();
    }
};

template<typename C>
void printcomp(const C& computer) {
    if (computer.empty()) {
        cout << "Список пуст!" << endl;
        return;
    }
    for (const auto& comp : computer) {
        comp.print();
    }
}

template<typename C>
void addcomputer(C& computer) {
    int count;
    cout << "Сколько компьютеров надо добавить?: ";
    while (!(cin >> count) || count <= 0) {
        cin.clear();
        cin.ignore();
        cout << "Ошибка! Введите положительное число: ";
    }
    cin.ignore(1000, '\n');

    int pos;
    while (true) {
        cout << "Добавить в начало (1) или в конец (2)? ";
        if (cin >> pos && (pos == 1 || pos == 2)) break;
        cout << "Ошибка ввода! Пожалуйста, введите 1 или 2.\n";
        cin.clear();
        cin.ignore();
    }
    cin.ignore(1000, '\n');

    for (int i = 0; i < count; i++) {
        ComputingCenter comp;
        cout << "Ввод данных для компьютера №:" << i + 1 << endl;
        comp.input();
        if (pos == 1) {
            computer.insert(computer.begin(), comp);
        }
        else {
            computer.push_back(comp);
        }
    }
    cout << "\nУспешно добавлено " << count << " компьютеров!" << endl;
}

template<typename C>
void search(const C& computer) {
    int ram;
    cout << "Введите объем ОЗУ для поиска (ГБ): ";
    while (!(cin >> ram) || ram <= 0) {
        cin.clear();
        cin.ignore();
        cout << "Ошибка! Введите положительное число: ";
    }
    cin.ignore(1000, '\n');

    bool found = false;
    for (const auto& comp : computer) {
        if (comp.ramsize == ram) {
            comp.print();
            found = true;
        }
    }

    if (!found) {
        cout << "Компьютеры с таким объемом ОЗУ не найдены." << endl;
    }
}


template<typename C>
void sort(C& computer) {
    if (computer.empty()) {
        cout << "Контейнер пуст, сортировка не требуется." << endl;
        return;
    }

    for (auto it1 = computer.begin(); it1 != computer.end(); ++it1) {
        auto min_it = it1;
        for (auto it2 = it1; it2 != computer.end(); ++it2) {
            if (it2->labID < min_it->labID) {
                min_it = it2;
            }
        }
        if (it1 != min_it) {
            swap(*it1, *min_it);
        }
    }

    cout << "Сортировка завершена!" << endl;
}

template<typename C>
bool filesave(const C& computers, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return false;
    }
    for (const auto& comp : computers) {
        file << comp.labID << " " << comp.proctype << " "
            << comp.ramsize << " " << comp.disksize << " " << comp.montype << endl;
    }
    file.close();
    cout << "Данные сохранены в файл: " << filename << endl;
    return true;
}

template<typename C>
bool fileread(C& computer, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Ошибка открытия файла!" << endl;
        return false;
    }
    computer.clear();
    ComputingCenter comp;
    while (file >> comp.labID >> comp.proctype >> comp.ramsize >> comp.disksize >> comp.montype) {
        computer.push_back(comp);
    }
    file.close();
    cout << "Данные загружены из файла: " << filename << endl;
    return true;
}

template<typename C>
void mergecont(C& main, C& addit) {
    if (addit.empty()) {
        cout << "Дополнительный контейнер пуст!" << endl;
        return;
    }
    int choice;
    while (true) {
        cout << "Добавить в начало (1) или в конец (2)? ";
        if (cin >> choice && (choice == 1 || choice == 2)) break;
        cout << "Ошибка ввода! Пожалуйста, введите 1 или 2.\n";
        cin.clear();
        cin.ignore();
    }
    cin.ignore();

    if (choice == 1) {
        main.insert(main.begin(), addit.begin(), addit.end());
    }
    else {
        main.insert(main.end(), addit.begin(), addit.end());
    }
    cout << "Контейнеры успешно объединены!" << endl;
}

void clearScreen() {
    system("cls");
}

void showMainMenu(const string& ctype) {
    clearScreen();
    cout << "=== ВЫЧИСЛИТЕЛЬНЫЙ ЦЕНТР (" << ctype << ") ===" << endl;
    cout << "1. Добавить компьютер(ы)" << endl;
    cout << "2. Найти компьютеры по ОЗУ" << endl;
    cout << "3. Сортировать по номеру лаборатории" << endl;
    cout << "4. Вывести все компьютеры" << endl;
    cout << "5. Сохранить в файл" << endl;
    cout << "6. Загрузить из файла" << endl;
    cout << "7. Работа с дополнительным контейнером" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

template<typename C>
void containerMenu(C& computer, C& addcomp, const string& ctype) {
    while (true) {
        showMainMenu(ctype);

        int choice;
        if (!(cin >> choice)) {
            cout << "Ошибка ввода! Пожалуйста, введите число.\n";
            cin.clear();
            cin.ignore();
            continue;
        }
        cin.ignore();

        switch (choice) {
        case 1: addcomputer(computer); break;
        case 2: search(computer); break;
        case 3: sort(computer); break;
        case 4: printcomp(computer); break;
        case 5: {
            string filename;
            cout << "Введите имя файла: ";
            getline(cin, filename);
            filesave(computer, filename);
            break;
        }
        case 6: {
            string filename;
            cout << "Введите имя файла: ";
            getline(cin, filename);
            fileread(computer, filename);
            break;
        }
        case 7: {
            cout << "1. Добавить в дополнительный контейнер" << endl;
            cout << "2. Объединить контейнеры" << endl;
            cout << "0. Назад" << endl;
            cout << "Выберите действие: ";

            int subChoice;
            if (!(cin >> subChoice)) {
                cout << "Ошибка ввода!\n";
                cin.clear();
                cin.ignore();
                break;
            }
            cin.ignore();

            if (subChoice == 1) {
                addcomputer(addcomp);
            }
            else if (subChoice == 2) {
                mergecont(computer, addcomp);
            }
            break;
        }
        case 0: return;
        default:
            cout << "Неверный выбор! Пожалуйста, выберите пункт из меню.\n";
        }

        cout << "\nНажмите Enter для продолжения...";
        cin.get();
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    while (true) {
        cout << "Выберите тип контейнера:" << endl;
        cout << "1. vector" << endl;
        cout << "2. list" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор: ";

        if (!(cin >> choice)) {
            cout << "Ошибка ввода! Пожалуйста, введите число.\n";
            cin.clear();
            cin.ignore();
            continue;
        }
        cin.ignore();

        if (choice == 1) {
            vector<ComputingCenter> computer;
            vector<ComputingCenter> addcomp;
            containerMenu(computer, addcomp, "vector");
        }
        else if (choice == 2) {
            list<ComputingCenter> computer;
            list<ComputingCenter> addcomp;
            containerMenu(computer, addcomp, "list");
        }
        else if (choice == 0) {
            break;
        }
        else {
            cout << "Неверный выбор! Пожалуйста, выберите 1, 2 или 0.\n";
        }
    }

    return 0;
}