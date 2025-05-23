#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Array {
    int a[20], n;
public:
    void readUser() {
        cout << "Enter size: "; cin >> n;
        cout << "Enter elements: ";
        for (int i = 0; i < n; i++) cin >> a[i];
    }

    void readRandom() {
        cout << "Enter size: "; cin >> n;
        srand(time(0));
        for (int i = 0; i < n; i++) a[i] = rand() % 100;
    }

    void display() {
        for (int i = 0; i < n; i++) cout << a[i] << " ";
        cout << endl;
    }

    void selectionSort() {
        for (int i = 0; i < n - 1; i++) {
            int min = i;
            for (int j = i + 1; j < n; j++)
                if (a[j] < a[min]) min = j;
            swap(a[i], a[min]);
        }
        cout << "Selection Sort: "; display();
    }

    void bubbleSort() {
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < n - i - 1; j++)
                if (a[j] > a[j + 1]) swap(a[j], a[j + 1]);
        cout << "Bubble Sort: "; display();
    }

    void insertionSort() {
        for (int i = 1; i < n; i++) {
            int key = a[i], j = i - 1;
            while (j >= 0 && a[j] > key) a[j + 1] = a[j--];
            a[j + 1] = key;
        }
        cout << "Insertion Sort: "; display();
    }

    void shellSort() {
        for (int gap = n / 2; gap > 0; gap /= 2)
            for (int i = gap; i < n; i++) {
                int temp = a[i], j = i;
                while (j >= gap && a[j - gap] > temp) {
                    a[j] = a[j - gap];
                    j -= gap;
                }
                a[j] = temp;
            }
        cout << "Shell Sort: "; display();
    }

    int partition(int low, int high) {
        int pivot = a[high], i = low - 1;
        for (int j = low; j < high; j++)
            if (a[j] < pivot) swap(a[++i], a[j]);
        swap(a[i + 1], a[high]);
        return i + 1;
    }

    void quickSort(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }
    }

    void radixSort() {
        int max = *max_element(a, a + n);
        for (int exp = 1; max / exp > 0; exp *= 10) {
            int output[20], count[10] = {0};
            for (int i = 0; i < n; i++) count[(a[i] / exp) % 10]++;
            for (int i = 1; i < 10; i++) count[i] += count[i - 1];
            for (int i = n - 1; i >= 0; i--)
                output[--count[(a[i] / exp) % 10]] = a[i];
            for (int i = 0; i < n; i++) a[i] = output[i];
        }
        cout << "Radix Sort: "; display();
    }

    void topScores() {
        bubbleSort();  // sort ascending
        cout << "Top 5 Scores: ";
        for (int i = n - 1; i >= max(0, n - 5); i--) cout << a[i] << " ";
        cout << endl;
    }

    int size() { return n; }
};

int main() {
    Array arr;
    int ch;
    do {
        cout << "\n1.User Input  2.Random  3.Selection  4.Bubble  5.Insertion  6.Shell  7.Quick  8.Radix  9.Top 5  10.Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: arr.readUser(); cout << "Array: "; arr.display(); break;
            case 2: arr.readRandom(); cout << "Array: "; arr.display(); break;
            case 3: arr.selectionSort(); break;
            case 4: arr.bubbleSort(); break;
            case 5: arr.insertionSort(); break;
            case 6: arr.shellSort(); break;
            case 7: arr.quickSort(0, arr.size() - 1); cout << "Quick Sort: "; arr.display(); break;
            case 8: arr.radixSort(); break;
            case 9: arr.topScores(); break;
            case 10: cout << "Exit.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (ch != 10);
    return 0;
}
