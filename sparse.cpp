#include<iostream>
using namespace std;

class Sparse
{
    private:
    int mat[100][100], row, column, i, j;
    int sparse[100][3];

    public:
        void read();
        void create();
        void display();
        void add(Sparse &mat2);
        void simpleTranspose();
        void fastTranspose();
};

void Sparse::read()
{
    cout << "\nEnter the no. of Rows: ";
    cin >> row;
    cout << "Enter the no. of Columns: ";
    cin >> column;

    cout << "Enter a Sparse Matrix: ";
    for(i=0; i<row; i++)
    {
        for(j=0; j<column; j++)
        {
            cin >> mat[i][j];
        }
    }
    create();
}

void Sparse::create()
{
    int k=1;
    for(i=0; i<row; i++)
    {
        for(j=0; j<column; j++)
        {
            if(mat[i][j] != 0)
            {
                sparse[k][0] = i;
                sparse[k][1] = j;
                sparse[k][2] = mat[i][j];
                k++;
            }
        }
    }
    sparse[0][0] = row;
    sparse[0][1] = column;
    sparse[0][2] = k-1;
}

void Sparse::display()
{
    cout << "\nThe Matrix is:\n";
    for(i=0; i<row; i++)
    {
        for(j=0; j<column; j++)
        {
            cout << "\t" << mat[i][j];
        }
        cout << "\n";
    }

    cout << "\nTriplet Representation: ";
    cout << "\n" << "Row" << "\t\tColumn" << "\t\tElement\n";
    for(int i=0; i<=sparse[0][2]; i++)
    {
        cout << sparse[i][0] << "\t\t" << sparse[i][1] << "\t\t" << sparse[i][2] << "\n";
    }
}

void Sparse::add(Sparse &mat2)
{
    int l1, l2, i = 1, j = 1, k = 1;
    int result[100][3];

    l1 = sparse[0][2];
    l2 = mat2.sparse[0][2];

    result[0][0] = sparse[0][0];
    result[0][1] = sparse[0][1];
    result[0][2] = 0;

    while(i <= l1 && j <= l2)
    {
        if(sparse[i][0] == mat2.sparse[j][0])
        {
            if(sparse[i][1] == mat2.sparse[j][1])
            {
                result[k][0] = sparse[i][0];
                result[k][1] = sparse[i][1];
                result[k][2] = sparse[i][2] + mat2.sparse[j][2];
                i++;
                j++;
                k++;
            }
            else if(sparse[i][1] < mat2.sparse[j][1])
            {
                result[k][0] = sparse[i][0];
                result[k][1] = sparse[i][1];
                result[k][2] = sparse[i][2];
                i++;
                k++;
            }
            else
            {
                result[k][0] = mat2.sparse[j][0];
                result[k][1] = mat2.sparse[j][1];
                result[k][2] = mat2.sparse[j][2];
                j++;
                k++;
            }
        }
        else if(sparse[i][0] < mat2.sparse[j][0])
        {
            result[k][0] = sparse[i][0];
            result[k][1] = sparse[i][1];
            result[k][2] = sparse[i][2];
            i++;
            k++;
        }
        else
        {
            result[k][0] = mat2.sparse[j][0];
            result[k][1] = mat2.sparse[j][1];
            result[k][2] = mat2.sparse[j][2];
            j++;
            k++;
        }
    }

    while(i <= l1)
    {
        result[k][0] = sparse[i][0];
        result[k][1] = sparse[i][1];
        result[k][2] = sparse[i][2];
        i++;
        k++;
    }

    while(j <= l2)
    {
        result[k][0] = mat2.sparse[j][0];
        result[k][1] = mat2.sparse[j][1];
        result[k][2] = mat2.sparse[j][2];
        j++;
        k++;
    }

    result[0][2] = k - 1;

    cout << "\nAddition of SpMat-1 & SpMat-2:";
    cout << "\n" << "Row" << "\t\tColumn" << "\t\tElement\n";
    for(int i = 0; i < k; i++) 
    {
        cout << result[i][0] << "\t\t" << result[i][1] << "\t\t" << result[i][2] << "\n";
    }
}


void Sparse::simpleTranspose() 
{
    int st[100][3], k = 1;
    st[0][0] = sparse[0][1];
    st[0][1] = sparse[0][0];
    st[0][2] = sparse[0][2];

    for (int z = 0; z < sparse[0][1]; z++) 
    {
        for (i = 1; i <= sparse[0][2]; i++) 
        {
            if (sparse[i][1] == z)
            {
                st[k][0] = sparse[i][1];
                st[k][1] = sparse[i][0];
                st[k][2] = sparse[i][2];
                k++;
            }
        }
    }

    cout << "\nSimple Transposed Sparse Matrix-1:";
    cout << "\n" << "Row" << "\t\tColumn" << "\t\tElement\n";
    for (int i = 0; i < k; i++) 
    {
        cout << st[i][0] << "\t\t" << st[i][1] << "\t\t" << st[i][2] << "\n";
    }
}

void Sparse::fastTranspose() {
    int loc, i, col_no;
    int result[100][3];

    int total[sparse[0][1]], index[sparse[0][1] + 1];

    for (i = 0; i < sparse[0][1]; i++) {
        total[i] = 0;
    }

    for (i = 1; i <= sparse[0][2]; i++) {
        col_no = sparse[i][1];
        total[col_no]++;
    }

    index[0] = 1; 
    for (i = 1; i <= sparse[0][1]; i++) {
        index[i] = index[i - 1] + total[i - 1];
    }

    result[0][0] = sparse[0][1];
    result[0][1] = sparse[0][0];
    result[0][2] = sparse[0][2];

    for (i = 1; i <= sparse[0][2]; i++) {
        col_no = sparse[i][1];
        loc = index[col_no];
        result[loc][0] = sparse[i][1];
        result[loc][1] = sparse[i][0];
        result[loc][2] = sparse[i][2];
        index[col_no]++;
    }

    cout << "\nFast Transposed Sparse Matrix-1:";
    cout << "\n" << "Row" << "\t\tColumn" << "\t\tElement\n";
    for (i = 0; i <= sparse[0][2]; i++) {
        cout << result[i][0] << "\t\t" << result[i][1] << "\t\t" << result[i][2] << "\n";
    }
}

int main()
{
    Sparse Sp1, Sp2;
    int x;
    
    do {
        cout << "\n***Select An Option***";
        cout << "\n1. Read Sparse Matrix-1";
        cout << "\n2. Display Sparse Matrix-1";
        cout << "\n3. Addition Of SpMat-1 and SpMat-2";
        cout << "\n4. Simple Transpose (Sparse Matrix-1)";
        cout << "\n5. Fast Transpose (Sparse Matrix-1)";
        cout << "\n6. Exit";
        cout << "\n\nEnter Choice: ";
        cin >> x;

        switch(x)
        {
            case 1: 
                Sp1.read();
                break;

            case 2: 
                Sp1.display();
                break;

            case 3:
                Sp2.read();
                Sp2.display();
                Sp1.add(Sp2);
                break;

            case 4: 
                Sp1.simpleTranspose();
                break;

            case 5:
                Sp1.fastTranspose();
                break;

            case 6: 
                cout << "\nExiting Program!";
                break;

            default: 
                cout << "Invalid Choice!\n\n";
        }
    } while(x != 6);

    return 0;
}



