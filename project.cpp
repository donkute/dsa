#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

class Set {
    string arr[MAX];
    int size;

public:
    void read() {
        cout << "Enter number of elements: ";
        cin >> size;
        cout << "Enter names:\n";
        for (int i = 0; i < size; i++)
            cin >> arr[i];
    }

    void show() {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    Set intersection(Set& B) {
        Set result;
        result.size = 0;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < B.size; j++)
                if (arr[i] == B.arr[j])
                    result.arr[result.size++] = arr[i];
        return result;
    }

    Set set_union(Set& B) {
        Set result;
        result.size = size;
        for (int i = 0; i < size; i++)
            result.arr[i] = arr[i];
        for (int j = 0; j < B.size; j++) {
            bool found = false;
            for (int i = 0; i < size; i++)
                if (B.arr[j] == arr[i]) found = true;
            if (!found) result.arr[result.size++] = B.arr[j];
        }
        return result;
    }

    Set difference(Set& B) {
        Set result;
        result.size = 0;
        for (int i = 0; i < size; i++) {
            bool found = false;
            for (int j = 0; j < B.size; j++)
                if (arr[i] == B.arr[j]) found = true;
            if (!found) result.arr[result.size++] = arr[i];
        }
        return result;
    }
};

int main() {
    Set A, B, C;
    cout << "Enter Coding participants:\n"; A.read();
    cout << "Enter Project participants:\n"; B.read();
    cout << "Enter Mastermind participants:\n"; C.read();

    cout << "\nIntersection of Coding and Project:\n";
    A.intersection(B).show();

    cout << "Union of all events:\n";
    A.set_union(B).set_union(C).show();

    cout << "Coding but not Mastermind:\n";
    A.difference(C).show();

    cout << "Participants in all three:\n";
    A.intersection(B).intersection(C).show();

    return 0;
}
