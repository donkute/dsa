#include <iostream>
#include <string>
#define SIZE 20

using namespace std;

struct Order {
    string customerName;
    int orderNumber;
    string toppings;
    double cost;
    int quantity;
};

class Queue {
    Order orders[SIZE];
    int front, rear;

public:
    Queue() : front(-1), rear(-1) {}

    bool isFull() {
        return (rear + 1) % SIZE == front;
    }

    bool isEmpty() {
        return front == -1;
    }

    void addQ(const Order& order) {
        if (isFull()) {
            cout << "Queue is full. Cannot place more orders." << endl;
            return;
        }

        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % SIZE;
        }
        orders[rear] = order;
        cout << "Order placed successfully." << endl;
    }

    void deleteQ() {
        if (isEmpty()) {
            cout << "Queue is empty. No orders to serve." << endl;
            return;
        }

        cout << "Serving Order:" << endl;
        cout << "Customer Name: " << orders[front].customerName << endl;
        cout << "Order Number: " << orders[front].orderNumber << endl;
        cout << "Toppings: " << orders[front].toppings << endl;
        cout << "Cost: $" << orders[front].cost << endl;
        cout << "Quantity: " << orders[front].quantity << endl;

        if (front == rear) {
            // Only one order was in queue, now empty
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
    }

    void displayQ() {
        if (isEmpty()) {
            cout << "Queue is empty. No orders to display." << endl;
            return;
        }

        cout << "Current Orders in Queue:\n" << endl;
        int i = front;
        while (true) {
            cout << "Customer Name: " << orders[i].customerName << endl;
            cout << "Order Number: " << orders[i].orderNumber << endl;
            cout << "Toppings: " << orders[i].toppings << endl;
            cout << "Cost: $" << orders[i].cost << endl;
            cout << "Quantity: " << orders[i].quantity << endl;
            cout << endl;

            if (i == rear)
                break;
            i = (i + 1) % SIZE;
        }
    }
};

int main() {
    Queue q;
    int choice;

    do {
        cout << "\n*** Pizza Parlor ***";
        cout << "\n1. Place Order";
        cout << "\n2. Serve Order";
        cout << "\n3. Display Orders";
        cout << "\n4. Exit";
        cout << "\n\nEnter Choice: ";
        cin >> choice;
        cin.ignore();  // Clear newline from input buffer

        switch (choice) {
            case 1: {
                Order newOrder;
                cout << "Enter Customer Name: ";
                getline(cin, newOrder.customerName);

                cout << "Enter Order Number: ";
                cin >> newOrder.orderNumber;
                cin.ignore();

                cout << "Enter Toppings: ";
                getline(cin, newOrder.toppings);

                cout << "Enter Cost: ";
                cin >> newOrder.cost;

                cout << "Enter Quantity: ";
                cin >> newOrder.quantity;
                cin.ignore();

                q.addQ(newOrder);
                break;
            }

            case 2:
                q.deleteQ();
                break;

            case 3:
                q.displayQ();
                break;

            case 4:
                cout << "\nExiting Program...\n";
                break;

            default:
                cout << "\nInvalid Choice! Please enter a number between 1 and 4.\n";
        }

    } while (choice != 4);

    return 0;
}
