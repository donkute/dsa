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
        cout << "\n";
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
    Set coding, project, mastermind;

    cout << "Enter Coding participants:\n"; 
    coding.read();

    cout << "Enter Project participants:\n"; 
    project.read();

    cout << "Enter Mastermind participants:\n"; 
    mastermind.read();

    cout << "\nParticipants in both Coding and Project:\n";
    coding.intersection(project).show();

    cout << "Participants in Coding or Project or Mastermind:\n";
    coding.set_union(project).set_union(mastermind).show();

    cout << "Participants in Coding but NOT in Mastermind:\n";
    coding.difference(mastermind).show();

    cout << "Participants in all three events:\n";
    coding.intersection(project).intersection(mastermind).show();

    return 0;
}
