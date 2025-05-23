#include <iostream>
using namespace std;

class Polynomial {
    int terms[100][2];  // [][0] = coefficient, [][1] = exponent
    int count;

public:
    void read() {
        cout << "Enter number of terms: ";
        cin >> count;
        cout << "Enter coefficients and exponents in descending order of exponents:\n";
        for (int i = 0; i < count; i++) {
            cin >> terms[i][0] >> terms[i][1];
        }
    }

    void display() {
        for (int i = 0; i < count; i++) {
            cout << terms[i][0] << "x^" << terms[i][1];
            if (i != count - 1) cout << " + ";
        }
        cout << "\n";
    }

    void add(Polynomial &p2) {
        int i = 0, j = 0, k = 0;
        int result[200][2];

        while (i < count && j < p2.count) {
            if (terms[i][1] > p2.terms[j][1]) {
                result[k][0] = terms[i][0];
                result[k][1] = terms[i][1];
                i++;
            } else if (terms[i][1] < p2.terms[j][1]) {
                result[k][0] = p2.terms[j][0];
                result[k][1] = p2.terms[j][1];
                j++;
            } else { // same exponent
                int sumCoeff = terms[i][0] + p2.terms[j][0];
                if (sumCoeff != 0) {
                    result[k][0] = sumCoeff;
                    result[k][1] = terms[i][1];
                } else {
                    k--; // skip zero coefficient
                }
                i++; j++;
            }
            k++;
        }

        while (i < count) {
            result[k][0] = terms[i][0];
            result[k][1] = terms[i][1];
            i++; k++;
        }

        while (j < p2.count) {
            result[k][0] = p2.terms[j][0];
            result[k][1] = p2.terms[j][1];
            j++; k++;
        }

        cout << "Resulting Polynomial: ";
        for (int idx = 0; idx < k; idx++) {
            cout << result[idx][0] << "x^" << result[idx][1];
            if (idx != k - 1) cout << " + ";
        }
        cout << "\n";
    }
};

int main() {
    Polynomial p1, p2;
    int choice;

    do {
        cout << "\nMenu:\n1. Read Polynomials\n2. Display Polynomials\n3. Add Polynomials\n4. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Read Polynomial 1:\n";
                p1.read();
                cout << "Read Polynomial 2:\n";
                p2.read();
                break;

            case 2:
                cout << "Polynomial 1: ";
                p1.display();
                cout << "Polynomial 2: ";
                p2.display();
                break;

            case 3:
                p1.add(p2);
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
