#include <iostream>
using namespace std;

class Node {
    string name, phone;
    int key;
public:
    Node() { key = 0; }
    friend class HashTable;
};

int hashFunc(string s) {
    int sum = 0;
    for (char c : s) sum += c;
    return sum % 100;
}

class HashTable {
    Node data[100];
    int size = 100;
public:
    void create(string name, string phone) {
        int key = hashFunc(name), idx = key % size;
        for (int i = 0; i < size; i++) {
            if (data[idx].key == 0) {
                data[idx].key = key;
                data[idx].name = name;
                data[idx].phone = phone;
                cout << "Record added!\n";
                return;
            }
            idx = (idx + 1) % size;
        }
        cout << "Table Full!\n";
    }

    void search(string name) {
        int key = hashFunc(name), idx = key % size;
        for (int i = 0; i < size; i++) {
            if (data[idx].key == key && data[idx].name == name) {
                cout << "Found: " << data[idx].name << " - " << data[idx].phone << endl;
                return;
            }
            idx = (idx + 1) % size;
        }
        cout << "Record not found!\n";
    }

    void update(string name) {
        int key = hashFunc(name), idx = key % size;
        for (int i = 0; i < size; i++) {
            if (data[idx].key == key && data[idx].name == name) {
                cout << "New phone: ";
                cin >> data[idx].phone;
                cout << "Record updated!\n";
                return;
            }
            idx = (idx + 1) % size;
        }
        cout << "Record not found!\n";
    }

    void remove(string name) {
        int key = hashFunc(name), idx = key % size;
        for (int i = 0; i < size; i++) {
            if (data[idx].key == key && data[idx].name == name) {
                data[idx].key = 0;
                data[idx].name = data[idx].phone = "";
                cout << "Record deleted!\n";
                return;
            }
            idx = (idx + 1) % size;
        }
        cout << "Record not found!\n";
    }

    void display() {
        cout << "\n--- Telephone Book ---\n";
        for (int i = 0; i < size; i++)
            if (data[i].key != 0)
                cout << data[i].name << " - " << data[i].phone << endl;
    }
};

int main() {
    HashTable book;
    int choice;
    string name, phone;

    while (true) {
        cout << "\n1.Create 2.Display 3.Search 4.Update 5.Delete 6.Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: cout << "Name: "; cin >> name;
                    cout << "Phone: "; cin >> phone;
                    book.create(name, phone); break;
            case 2: book.display(); break;
            case 3: cout << "Name: "; cin >> name;
                    book.search(name); break;
            case 4: cout << "Name: "; cin >> name;
                    book.update(name); break;
            case 5: cout << "Name: "; cin >> name;
                    book.remove(name); break;
            case 6: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
