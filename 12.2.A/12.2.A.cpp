#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Kurs { I = 1, II, III, IV, V, VI };
enum Spec { ME, MF, FI, INF, KN };

struct Student {
    char prizv[64];
    int kurs;
    Spec spec;
    int mark_physics;
    int mark_math;
    int mark_informatics; 
};

void input_students_to_file(const char* fname);
void print_students_from_file(const char* fname);
void calculate_marks(const char* fname, int& count5, int& count4, int& count3);
double calculate_percentage(const char* fname);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char fname[256];
    char choice;

    do {
        cout << "\nМеню:\n";
        cout << "1 - Введення даних та запис у файл\n";
        cout << "2 - Відображення даних з файлу\n";
        cout << "3 - Підрахунок оцінок з інформатики\n";
        cout << "4 - Обчислення відсотка студентів із високими оцінками\n";
        cout << "0 - Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case '1':
            cout << "Введіть ім'я файлу: ";
            cin >> fname;
            input_students_to_file(fname);
            break;

        case '2':
            cout << "Введіть ім'я файлу: ";
            cin >> fname;
            print_students_from_file(fname);
            break;

        case '3': {
            cout << "Введіть ім'я файлу: ";
            cin >> fname;
            int count5, count4, count3;
            calculate_marks(fname, count5, count4, count3);
            cout << "Оцінки з інформатики:\n";
            cout << "5: " << count5 << "\n4: " << count4 << "\n3: " << count3 << endl;
            break;
        }

        case '4': {
            cout << "Введіть ім'я файлу: ";
            cin >> fname;
            double percent = calculate_percentage(fname);
            cout << "Відсоток студентів із оцінками >= 4 з фізики і математики: " << percent << "%\n";
            break;
        }

        case '0':
            cout << "Завершення програми.\n";
            break;

        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != '0');

    return 0;
}

void input_students_to_file(const char* fname) {
    ofstream fout(fname, ios::binary);
    if (!fout) {
        cerr << "Помилка відкриття файлу для запису.\n";
        return;
    }

    char choice;
    do {
        Student student;
        cout << "\nВведіть дані студента:\n";
        cout << "Прізвище: ";
        cin >> student.prizv;

        cout << "Курс (1-6): ";
        while (!(cin >> student.kurs) || student.kurs < 1 || student.kurs > 6) {
            cout << "Невірне введення. Введіть курс від 1 до 6: ";
            cin.clear();
            cin.sync();
        }

        int spec;
        cout << "Спеціальність (0 - ME, 1 - MF, 2 - FI, 3 - INF, 4 - KN): ";
        while (!(cin >> spec) || spec < 0 || spec > 4) {
            cout << "Невірне введення. Введіть спеціальність від 0 до 4: ";
            cin.clear();
            cin.sync();
        }
        student.spec = static_cast<Spec>(spec);

        cout << "Оцінка з фізики: ";
        while (!(cin >> student.mark_physics) || student.mark_physics < 0 || student.mark_physics > 5) {
            cout << "Невірне введення. Введіть оцінку від 0 до 5: ";
            cin.clear();
            cin.sync();
        }

        cout << "Оцінка з математики: ";
        while (!(cin >> student.mark_math) || student.mark_math < 0 || student.mark_math > 5) {
            cout << "Невірне введення. Введіть оцінку від 0 до 5: ";
            cin.clear();
            cin.sync();
        }

        cout << "Оцінка з інформатики: ";
        while (!(cin >> student.mark_informatics) || student.mark_informatics < 0 || student.mark_informatics > 5) {
            cout << "Невірне введення. Введіть оцінку від 0 до 5: ";
            cin.clear();
            cin.sync();
        }

        fout.write(reinterpret_cast<char*>(&student), sizeof(Student));

        cout << "Додати ще одного студента? (Y/N): ";
        cin >> choice;

    } while (choice == 'Y' || choice == 'y');

    fout.close();
}

void print_students_from_file(const char* fname) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cerr << "Помилка відкриття файлу для читання.\n";
        return;
    }

    Student student;
    cout << "----------------------------------------------------------------------------------\n";
    cout << "| Прізвище       | Курс | Спеціальність   | Фізика | Математика | Інформатика     |\n";
    cout << "----------------------------------------------------------------------------------\n";

    while (fin.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        cout << "| " << setw(14) << left << student.prizv
            << "| " << setw(4) << student.kurs
            << "| " << setw(15);

        switch (student.spec) {
        case ME: cout << "Math & Econ"; break;
        case MF: cout << "Labour Ed"; break;
        case FI: cout << "Phys & Info"; break;
        case INF: cout << "Informatics"; break;
        case KN: cout << "Comp Sci"; break;
        }

        cout << "| " << setw(7) << student.mark_physics
            << "| " << setw(11) << student.mark_math
            << "| " << setw(11) << student.mark_informatics << "        |\n";
    }

    cout << "----------------------------------------------------------------------------------\n";
    fin.close();
}

void calculate_marks(const char* fname, int& count5, int& count4, int& count3) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cerr << "Помилка відкриття файлу для читання.\n";
        return;
    }

    count5 = count4 = count3 = 0;
    Student student;

    while (fin.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.mark_informatics == 5) count5++;
        else if (student.mark_informatics == 4) count4++;
        else if (student.mark_informatics == 3) count3++;
    }

    fin.close();
}

double calculate_percentage(const char* fname) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cerr << "Помилка відкриття файлу для читання.\n";
        return 0.0;
    }

    int total = 0, count = 0;
    Student student;

    while (fin.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        total++;
        if (student.mark_physics >= 4 && student.mark_math >= 4) {
            count++;
        }
    }

    fin.close();
    return total > 0 ? static_cast<double>(count) / total * 100 : 0.0;
}
