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
        cerr << "�� ������� ������� ����." << endl;
        return;
    }
    int n;
    cout << "������� ���������� ������� ��� ����������: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        Record record;
        cout << "������� �����: ";
        cin >> record.number;
        cout << "������� ���: ";
        cin.ignore();
        getline(cin, record.name);
        cout << "������� �������� �����: ";
        getline(cin, record.address);
        cout << "������� ���� ����� (����-��-��): ";
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
        cerr << "�� ������� ������� ����." << endl;
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
        cout << "�����: " << record.number << "\n���: " << record.name
             << "\n�������� �����: " << record.address << "\n���� �����: " << record.date << endl << endl;
    }
    file.close();
}

void addRecord(const string& filename) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file) {
        cerr << "�� ������� ������� ����." << endl;
        return;
    }
    Record record;
    cout << "������� �����: ";
    cin >> record.number;
    cout << "������� ���: ";
    cin.ignore();
    getline(cin, record.name);
    cout << "������� �������� �����: ";
    getline(cin, record.address);
    cout << "������� ���� ����� (����-��-��): ";
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
        cerr << "�� ������� ������� ����." << endl;
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
            cout << "�����: " << record.number << "\n���: " << record.name
                 << "\n�������� �����: " << record.address << "\n���� �����: " << record.date << endl << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "������ �� �������." << endl;
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
            cout << "�����: " << records[mid].number << "\n���: " << records[mid].name
                 << "\n�������� �����: " << records[mid].address << "\n���� �����: " << records[mid].date << endl << endl;
            return;
        }
        if (records[mid].date < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    cout << "������ �� �������." << endl;
}

void removeDuplicates(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "�� ������� ������� ����." << endl;
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
        cerr << "�� ������� ������� ���� ��� ������." << endl;
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
        cout << "1. ������� ����\n"
             << "2. ����������� ����\n"
             << "3. �������� ������\n"
             << "4. �������� �����\n"
             << "5. ���������� (������ �����)\n"
             << "6. ���������� (Quicksort)\n"
             << "7. �������� �����\n"
             << "8. ������� ������������� ������\n"
             << "9. �����\n"
             << "�������� ��������: ";
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
                cout << "������� ���� ��� ������ (����-��-��): ";
                cin >> key;
                linearSearch(filename, key);
                break;
            }
            case 5: {
                ifstream file(filename, ios::binary);
                if (!file) {
                    cerr << "�� ������� ������� ����." << endl;
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
                    cerr << "�� ������� ������� ���� ��� ������." << endl;
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
                cout << "���������� ���������." << endl;
                break;
            }
            case 6: {
                ifstream file(filename, ios::binary);
                if (!file) {
                    cerr << "�� ������� ������� ����." << endl;
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
                    cerr << "�� ������� ������� ���� ��� ������." << endl;
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
                cout << "���������� ���������." << endl;
                break;
            }
            case 7: {
                ifstream file(filename, ios::binary);
                if (!file) {
                    cerr << "�� ������� ������� ����." << endl;
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
                cout << "������� ���� ��� ������ (����-��-��): ";
                cin >> key;
                binarySearch(records, key);
                break;
            }
            case 8:
                removeDuplicates(filename);
                cout << "�������� ���������." << endl;
                break;
            case 9:
                return;
            default:
                cout << "�������� �����. ���������� �����." << endl;
        }
    }
}
