#include <iostream>
using namespace std;

class SparseMatrix {
    int rows, cols, nonZero;
    int triplet[100][3]; // row, col, value

public:
    void read() {
        cout << "Enter rows and columns: ";
        cin >> rows >> cols;
        cout << "Enter matrix elements:\n";

        nonZero = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int val; 
                cin >> val;
                if (val != 0) {
                    triplet[nonZero][0] = i;
                    triplet[nonZero][1] = j;
                    triplet[nonZero][2] = val;
                    nonZero++;
                }
            }
        }
    }

    void display() {
        cout << "\nTriplet form:\nRow\tCol\tVal\n";
        for (int i = 0; i < nonZero; i++) {
            cout << triplet[i][0] << "\t" << triplet[i][1] << "\t" << triplet[i][2] << "\n";
        }
    }

    void add(SparseMatrix &b) {
        if (rows != b.rows || cols != b.cols) {
            cout << "Matrices dimensions do not match!\n";
            return;
        }

        int i = 0, j = 0;
        int result[200][3]; // store sum triplets
        int k = 0;

        while (i < nonZero && j < b.nonZero) {
            if (triplet[i][0] < b.triplet[j][0] || 
                (triplet[i][0] == b.triplet[j][0] && triplet[i][1] < b.triplet[j][1])) {
                result[k][0] = triplet[i][0];
                result[k][1] = triplet[i][1];
                result[k][2] = triplet[i][2];
                i++; k++;
            } else if (triplet[i][0] > b.triplet[j][0] || 
                       (triplet[i][0] == b.triplet[j][0] && triplet[i][1] > b.triplet[j][1])) {
                result[k][0] = b.triplet[j][0];
                result[k][1] = b.triplet[j][1];
                result[k][2] = b.triplet[j][2];
                j++; k++;
            } else {
                // same position
                int summed = triplet[i][2] + b.triplet[j][2];
                if (summed != 0) {
                    result[k][0] = triplet[i][0];
                    result[k][1] = triplet[i][1];
                    result[k][2] = summed;
                    k++;
                }
                i++; j++;
            }
        }

        // copy remaining elements
        while (i < nonZero) {
            result[k][0] = triplet[i][0];
            result[k][1] = triplet[i][1];
            result[k][2] = triplet[i][2];
            i++; k++;
        }
        while (j < b.nonZero) {
            result[k][0] = b.triplet[j][0];
            result[k][1] = b.triplet[j][1];
            result[k][2] = b.triplet[j][2];
            j++; k++;
        }

        cout << "\nSum matrix in triplet form:\nRow\tCol\tVal\n";
        for (int x = 0; x < k; x++) {
            cout << result[x][0] << "\t" << result[x][1] << "\t" << result[x][2] << "\n";
        }
    }
};

int main() {
    SparseMatrix A, B;
    cout << "Enter first matrix:\n";
    A.read();

    cout << "Enter second matrix:\n";
    B.read();

    cout << "\nFirst matrix:";
    A.display();

    cout << "\nSecond matrix:";
    B.display();

    cout << "\nAdding matrices:";
    A.add(B);

    return 0;
}
