#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Record {
    int number;
    string name;
    string address;
    string date;

    bool operator<(const Record& other) const {
        return date < other.date;
    }
};

void createFile(const string& filename);
void viewFile(const string& filename);
void addRecord(const string& filename);
void linearSearch(const string& filename, const string& key);
void quickSort(vector<Record>& records, int low, int high);
int partition(vector<Record>& records, int low, int high);
void selectionSort(vector<Record>& records);
void binarySearch(const vector<Record>& records, const string& key);
void removeDuplicates(const string& filename);
void menu();

int main() {
    setlocale(LC_ALL, "Russian");
    menu();
    return 0;
}

void createFile(const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Не удалось создать файл." << endl;
        return;
    }
    int n;
    cout << "Введите количество записей для добавления: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        Record record;
        cout << "Введите номер: ";
        cin >> record.number;
        cout << "Введите ФИО: ";
        cin.ignore();
        getline(cin, record.name);
        cout << "Введите домашний адрес: ";
        getline(cin, record.address);
        cout << "Введите дату учета (гггг-мм-дд): ";
        getline(cin, record.date);
        file.write(reinterpret_cast<const char*>(&record.number), sizeof(record.number));
        size_t nameLength = record.name.size();
        file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        file.write(record.name.c_str(), nameLength);
        size_t addressLength = record.address.size();
        file.write(reinterpret_cast<const char*>(&addressLength), sizeof(addressLength));
        file.write(record.address.c_str(), addressLength);
        size_t dateLength = record.date.size();
        file.write(reinterpret_cast<const char*>(&dateLength), sizeof(dateLength));
        file.write(record.date.c_str(), dateLength);
    }
    file.close();
}

void viewFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Не удалось открыть файл." << endl;
        return;
    }
    Record record;
    while (file.read(reinterpret_cast<char*>(&record.number), sizeof(record.number))) {
        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        record.name.resize(nameLength);
        file.read(&record.name[0], nameLength);
        size_t addressLength;
        file.read(reinterpret_cast<char*>(&addressLength), sizeof(addressLength));
        record.address.resize(addressLength);
        file.read(&record.address[0], addressLength);
        size_t dateLength;
        file.read(reinterpret_cast<char*>(&dateLength), sizeof(dateLength));
        record.date.resize(dateLength);
        file.read(&record.date[0], dateLength);
        cout << "Номер: " << record.number << "\nФИО: " << record.name
             << "\nДомашний адрес: " << record.address << "\nДата учета: " << record.date << endl << endl;
    }
    file.close();
}

void addRecord(const string& filename) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file) {
        cerr << "Не удалось открыть файл." << endl;
        return;
    }
    Record record;
    cout << "Введите номер: ";
    cin >> record.number;
    cout << "Введите ФИО: ";
    cin.ignore();
    getline(cin, record.name);
    cout << "Введите домашний адрес: ";
    getline(cin, record.address);
    cout << "Введите дату учета (гггг-мм-дд): ";
    getline(cin, record.date);
    file.write(reinterpret_cast<const char*>(&record.number), sizeof(record.number));
    size_t nameLength = record.name.size();
    file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    file.write(record.name.c_str(), nameLength);
    size_t addressLength = record.address.size();
    file.write(reinterpret_cast<const char*>(&addressLength), sizeof(addressLength));
    file.write(record.address.c_str(), addressLength);
    size_t dateLength = record.date.size();
    file.write(reinterpret_cast<const char*>(&dateLength), sizeof(dateLength));
    file.write(record.date.c_str(), dateLength);
    file.close();
}

void linearSearch(const string& filename, const string& key) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Не удалось открыть файл." << endl;
        return;
    }
    Record record;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&record.number), sizeof(record.number))) {
        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        record.name.resize(nameLength);
        file.read(&record.name[0], nameLength);
        size_t addressLength;
        file.read(reinterpret_cast<char*>(&addressLength), sizeof(addressLength));
        record.address.resize(addressLength);
        file.read(&record.address[0], addressLength);
        size_t dateLength;
        file.read(reinterpret_cast<char*>(&dateLength), sizeof(dateLength));
        record.date.resize(dateLength);
        file.read(&record.date[0], dateLength);
        if (record.date == key) {
            cout << "Номер: " << record.number << "\nФИО: " << record.name
                 << "\nДомашний адрес: " << record.address << "\nДата учета: " << record.date << endl << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Запись не найдена." << endl;
    }
    file.close();
}

void quickSort(vector<Record>& records, int low, int high) {
    if (low < high) {
        int pi = partition(records, low, high);
        quickSort(records, low, pi - 1);
        quickSort(records, pi + 1, high);
    }
}

int partition(vector<Record>& records, int low, int high) {
    Record pivot = records[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (records[j] < pivot) {
            ++i;
            swap(records[i], records[j]);
        }
    }
    swap(records[i + 1], records[high]);
    return i + 1;
}

void selectionSort(vector<Record>& records) {
    int n = records.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (records[j] < records[min_idx]) {
                min_idx = j;
            }
        }
        swap(records[min_idx], records[i]);
    }
}

void binarySearch(const vector<Record>& records, const string& key) {
    int left = 0, right = records.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (records[mid].date == key) {
            cout << "Номер: " << records[mid].number << "\nФИО: " << records[mid].name
                 << "\nДомашний адрес: " << records[mid].address << "\nДата учета: " << records[mid].date << endl << endl;
            return;
        }
        if (records[mid].date < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    cout << "Запись не найдена." << endl;
}

void removeDuplicates(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Не удалось открыть файл." << endl;
        return;
    }
    vector<Record> records;
    Record record;
    while (file.read(reinterpret_cast<char*>(&record.number), sizeof(record.number))) {
        size_t nameLength;
        file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        record.name.resize(nameLength);
        file.read(&record.name[0], nameLength);
        size_t addressLength;
        file.read(reinterpret_cast<char*>(&addressLength), sizeof(addressLength));
        record.address.resize(addressLength);
        file.read(&record.address[0], addressLength);
        size_t dateLength;
        file.read(reinterpret_cast<char*>(&dateLength), sizeof(dateLength));
        record.date.resize(dateLength);
        file.read(&record.date[0], dateLength);
        records.push_back(record);
    }
    file.close();

    sort(records.begin(), records.end(), [](const Record& a, const Record& b) {
        return a.name < b.name || (a.name == b.name && a.address < b.address);
    });

    auto last = unique(records.begin(), records.end(), [](const Record& a, const Record& b) {
        return a.name == b.name && a.address == b.address;
    });
    records.erase(last, records.end());

    ofstream outFile(filename, ios::binary | ios::trunc);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }
    for (const auto& rec : records) {
        outFile.write(reinterpret_cast<const char*>(&rec.number), sizeof(rec.number));
        size_t nameLength = rec.name.size();
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        outFile.write(rec.name.c_str(), nameLength);
        size_t addressLength = rec.address.size();
        outFile.write(reinterpret_cast<const char*>(&addressLength), sizeof(addressLength));
        outFile.write(rec.address.c_str(), addressLength);
        size_t dateLength = rec.date.size();
        outFile.write(reinterpret_cast<const char*>(&dateLength), sizeof(dateLength));
        outFile.write(rec.date.c_str(), dateLength);
    }
    outFile.close();
}

void menu() {
    string filename = "records.dat";
    while (true) {
        cout << "1. Создать файл\n"
             << "2. Просмотреть файл\n"
             << "3. Добавить запись\n"
             << "4. Линейный поиск\n"
             << "5. Сортировка (Прямой выбор)\n"
             << "6. Сортировка (Quicksort)\n"
             << "7. Бинарный поиск\n"
             << "8. Удалить повторяющиеся записи\n"
             << "9. Выход\n"
             << "Выберите действие: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                createFile(filename);
                break;
            case 2:
                viewFile(filename);
                break;
            case 3:
                addRecord(filename);
                break;
            case 4: {
                string key;
                cout << "Введите дату для поиска (гггг-мм-дд): ";
                cin >> key;
                linearSearch(filename, key);
                break;
            }
            case 5: {
                ifstream file(filename, ios::binary);
                if (!file) {
                    cerr << "Не удалось открыть файл." << endl;
                    break;
                }
                vector<Record> records;
                Record record;
                while (file.read(reinterpret_cast<char*>(&record.number), sizeof(record.number))) {
                    size_t nameLength;
                    file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
                    record.name.resize(nameLength);
                    file.read(&record.name[0], nameLength);
                    size_t addressLength;
                    file.read(reinterpret_cast<char*>(&addressLength), sizeof(addressLength));
                    record.address.resize(addressLength);
                    file.read(&record.address[0], addressLength);
                    size_t dateLength;
                    file.read(reinterpret_cast<char*>(&dateLength), sizeof(dateLength));
                    record.date.resize(dateLength);
                    file.read(&record.date[0], dateLength);
                    records.push_back(record);
                }
                file.close();
                selectionSort(records);
                ofstream outFile(filename, ios::binary | ios::trunc);
                if (!outFile) {
                    cerr << "Не удалось открыть файл для записи." << endl;
                    break;
                }
                for (const auto& rec : records) {
                    outFile.write(reinterpret_cast<const char*>(&rec.number), sizeof(rec.number));
                    size_t nameLength = rec.name.size();
                    outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
                    outFile.write(rec.name.c_str(), nameLength);
                    size_t addressLength = rec.address.size();
                    outFile.write(reinterpret_cast<const char*>(&addressLength), sizeof(addressLength));
                    outFile.write(rec.address.c_str(), addressLength);
                    size_t dateLength = rec.date.size();
                    outFile.write(reinterpret_cast<const char*>(&dateLength), sizeof(dateLength));
                    outFile.write(rec.date.c_str(), dateLength);
                }
                outFile.close();
                cout << "Сортировка завершена." << endl;
                break;
            }
            case 6: {
                ifstream file(filename, ios::binary);
                if (!file) {
                    cerr << "Не удалось открыть файл." << endl;
                    break;
                }
                vector<Record> records;
                Record record;
                while (file.read(reinterpret_cast<char*>(&record.number), sizeof(record.number))) {
                    size_t nameLength;
                    file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
                    record.name.resize(nameLength);
                    file.read(&record.name[0], nameLength);
                    size_t addressLength;
                    file.read(reinterpret_cast<char*>(&addressLength), sizeof(addressLength));
                    record.address.resize(addressLength);
                    file.read(&record.address[0], addressLength);
                    size_t dateLength;
                    file.read(reinterpret_cast<char*>(&dateLength), sizeof(dateLength));
                    record.date.resize(dateLength);
                    file.read(&record.date[0], dateLength);
                    records.push_back(record);
                }
                file.close();
                quickSort(records, 0, records.size() - 1);
                ofstream outFile(filename, ios::binary | ios::trunc);
                if (!outFile) {
                    cerr << "Не удалось открыть файл для записи." << endl;
                    break;
                }
                for (const auto& rec : records) {
                    outFile.write(reinterpret_cast<const char*>(&rec.number), sizeof(rec.number));
                    size_t nameLength = rec.name.size();
                    outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
                    outFile.write(rec.name.c_str(), nameLength);
                    size_t addressLength = rec.address.size();
                    outFile.write(reinterpret_cast<const char*>(&addressLength), sizeof(addressLength));
                    outFile.write(rec.address.c_str(), addressLength);
                    size_t dateLength = rec.date.size();
                    outFile.write(reinterpret_cast<const char*>(&dateLength), sizeof(dateLength));
                    outFile.write(rec.date.c_str(), dateLength);
                }
                outFile.close();
                cout << "Сортировка завершена." << endl;
                break;
            }
            case 7: {
                ifstream file(filename, ios::binary);
                if (!file) {
                    cerr << "Не удалось открыть файл." << endl;
                    break;
                }
                vector<Record> records;
                Record record;
                while (file.read(reinterpret_cast<char*>(&record.number), sizeof(record.number))) {
                    size_t nameLength;
                    file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
                    record.name.resize(nameLength);
                    file.read(&record.name[0], nameLength);
                    size_t addressLength;
                    file.read(reinterpret_cast<char*>(&addressLength), sizeof(addressLength));
                    record.address.resize(addressLength);
                    file.read(&record.address[0], addressLength);
                    size_t dateLength;
                    file.read(reinterpret_cast<char*>(&dateLength), sizeof(dateLength));
                    record.date.resize(dateLength);
                    file.read(&record.date[0], dateLength);
                    records.push_back(record);
                }
                file.close();
                sort(records.begin(), records.end());
                string key;
                cout << "Введите дату для поиска (гггг-мм-дд): ";
                cin >> key;
                binarySearch(records, key);
                break;
            }
            case 8:
                removeDuplicates(filename);
                cout << "Удаление завершено." << endl;
                break;
            case 9:
                return;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }
}
