#include<iostream>
#include<stdlib.h>
#include<ctime>
using namespace std;

class array 
{
    private:
        int a[20];
        int n;
    public:
        void readrandom();
        void readarray();
        void display();
        void selectionsort();
        void bubblesort();
        void insertionsort();
        void shellsort();
        void quicksort(int low, int high);
        void radixsort();
        void score();
        int partition(int low, int high);
        int getSize() const;
};

void array::readarray()
{
    cout<<"\nEnter Size: ";
    cin>>n;
    cout<<"Enter Elements: ";
    for(int i=0; i<n; i++)
        cin>>a[i];
}

void array::readrandom()
{
    cout<<"\nEnter Size: ";
    cin>>n;

    srand(time(0));

    for(int i=0; i<n; i++)
        a[i]=rand()%100;
}

void array::display()
{
    for(int i=0; i<n; i++)
        cout<<a[i]<<"\t";
}

void array::selectionsort()
{
    for(int i=0; i<n-1; i++)
    {
        int minIndex = i;
        for(int j=i+1; j<n; j++)
        {
            if(a[j] < a[minIndex])
                minIndex = j;
        }
        if(minIndex != i)
        {
            int temp = a[i];
            a[i] = a[minIndex];
            a[minIndex] = temp;
        }
    }
    cout << "Array after Selection Sort: ";
    display();
}

void array::bubblesort()
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-1-i; j++)
        {
            if(a[j] > a[j+1])
            {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
    cout << "Array after Bubble Sort: ";
    display();
}

void array::insertionsort()
{
    for(int i=1; i<n; i++)
    {
        int key = a[i];
        int j = i - 1;

        while(j >= 0 && a[j] > key)
        {
            a[j+1] = a[j];
            j = j - 1;
        }
        a[j+1] = key;
    }
    cout << "Array after Insertion Sort: ";
    display();
}

void array::shellsort()
{
    for(int gap = n/2; gap > 0; gap /= 2)
    {
        for(int i = gap; i < n; i++)
        {
            int key = a[i];
            int j = i;

            while(j >= gap && a[j - gap] > key)
            {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = key;
        }
    }
    cout << "Array after Shell Sort: ";
    display();
}

int array::partition(int low, int high)
{
    int pivot = a[high];  // Choose the last element as pivot
    int i = low - 1;  // Index of smaller element

    for(int j = low; j < high; j++)  // Traverse through all elements
    {
        if(a[j] < pivot)  // If the current element is smaller than the pivot
        {
            i++;  // Increment index of smaller element
            // Swap elements
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    // Swap the pivot element with the element at index i+1
    int temp = a[i+1];
    a[i+1] = a[high];
    a[high] = temp;

    return i+1;  // Return the pivot index
}

void array::quicksort(int low, int high)
{
    if(low < high)
    {
        // Partition the array into two subarrays and get the pivot index
        int pi = partition(low, high);

        // Recursively sort the subarrays
        quicksort(low, pi - 1);
        quicksort(pi + 1, high);
    }
}

int array::getSize() const {
    return n;
}

void array::radixsort()
{
    int maxElem = a[0];
    // Find the maximum element
    for(int i = 1; i < n; i++)
    {
        if(a[i] > maxElem)
            maxElem = a[i];
    }

    // Apply counting sort for every digit (LSD approach)
    for(int exp = 1; maxElem/exp > 0; exp *= 10)
    {
        int output[n];  // Output array to store sorted elements
        int count[10] = {0};  // Count array for each digit (0-9)

        // Store count of occurrences in count[]
        for(int i = 0; i < n; i++)
            count[(a[i]/exp) % 10]++;

        // Change count[i] to store actual position of this digit in output[]
        for(int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        // Build the output array
        for(int i = n - 1; i >= 0; i--)
        {
            output[count[(a[i]/exp) % 10] - 1] = a[i];
            count[(a[i]/exp) % 10]--;
        }

        // Copy the sorted output[] into a[]
        for(int i = 0; i < n; i++)
            a[i] = output[i];
    }
    cout << "Array after Radix Sort: ";
    display();
}

void array::score()
{
    for(int i = 0; i < n-1; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            if(a[j] < a[j+1])
            {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    cout << "Top 5 Scores: ";
    for(int i = 0; i < 5 && i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout <<"\n"<<endl;
}

int main()
{
    array A;
    int x;
    
    do {
    cout<<"***Select An Option***";
    cout<<"\n1. User Elements";
    cout<<"\n2. Random Elements";
    cout<<"\n3. Selection Sort";
    cout<<"\n4. Bubble Sort";
    cout<<"\n5. Insertion Sort";
    cout<<"\n6. Shell Sort";
    cout<<"\n7. Quick Sort";
    cout<<"\n8. Radix Sort";
    cout<<"\n9. Display Top 5 Scores";
    cout<<"\n10. Exit";
    cout<<"\n\nEnter Choice: ";
    cin>>x;

    switch(x)
    {
        case 1: A.readarray();
        cout<<"Current Array Is: ";
        A.display();
        cout<<"\n\n";
        break;

        case 2: A.readrandom();
        cout<<"Current Array Is: ";
        A.display();
        cout<<"\n\n";
        break;

        case 3: A.selectionsort();
        cout<<"\n\n";
        break;

        case 4: A.bubblesort();
        cout<<"\n\n";
        break;

        case 5: A.insertionsort();
        cout<<"\n\n";
        break;

        case 6: A.shellsort();
        cout<<"\n\n";
        break;

        case 7:
         A.quicksort(0, A.getSize() - 1);  
        cout << "Array after Quick Sort: ";
        A.display();
        cout<<"\n\n";
        break;

        case 8: A.radixsort();
        cout<<"\n\n";
        break;

        case 9: A.score();
        break;

        case 10: cout<<"\nExiting Program!";
        break;

        default: cout<<"Invalid Choice!\n\n";
    }
    } while(x != 10);

    return 0;
}




