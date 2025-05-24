#include <iostream>
#include <string>
using namespace std;

struct Appointment {
    string name;
    int start;  // minutes from 0:00, e.g., 9:30 = 570
    int end;    // minutes from 0:00
    Appointment* next;
};

class AppointmentList {
    Appointment* head;
    int dayStart;  // start time of schedule in minutes (e.g. 9:00 = 540)
    int dayEnd;    // end time of schedule in minutes (e.g. 17:00 = 1020)
public:
    AppointmentList(int start, int end) : head(nullptr), dayStart(start), dayEnd(end) {}

    // Helper to convert HH:MM to minutes from midnight
    int timeToMinutes(const string& time) {
        int h = stoi(time.substr(0, 2));
        int m = stoi(time.substr(3, 2));
        return h * 60 + m;
    }

    // Helper to convert minutes to HH:MM string
    string minutesToTime(int m) {
        int h = m / 60;
        int min = m % 60;
        char buf[6];
        sprintf(buf, "%02d:%02d", h, min);
        return string(buf);
    }

    void displayFreeSlots() {
        cout << "\nFree slots:\n";
        int prevEnd = dayStart;

        Appointment* curr = head;
        while (curr != nullptr) {
            if (curr->start > prevEnd) {
                cout << minutesToTime(prevEnd) << " - " << minutesToTime(curr->start) << "\n";
            }
            prevEnd = max(prevEnd, curr->end);
            curr = curr->next;
        }
        if (prevEnd < dayEnd) {
            cout << minutesToTime(prevEnd) << " - " << minutesToTime(dayEnd) << "\n";
        }
    }

    bool isSlotFree(int start, int end) {
        if (start < dayStart || end > dayEnd || start >= end) return false;
        Appointment* curr = head;
        while (curr != nullptr) {
            if (!(end <= curr->start || start >= curr->end)) {
                // overlap
                return false;
            }
            curr = curr->next;
        }
        return true;
    }

    void bookAppointment() {
        string name, startTime, endTime;
        cout << "Enter appointment name: ";
        cin >> name;
        cout << "Enter start time (HH:MM): ";
        cin >> startTime;
        cout << "Enter end time (HH:MM): ";
        cin >> endTime;

        int start = timeToMinutes(startTime);
        int end = timeToMinutes(endTime);

        if (!isSlotFree(start, end)) {
            cout << "Slot unavailable or invalid.\n";
            return;
        }

        Appointment* newAppt = new Appointment{name, start, end, nullptr};

        // Insert sorted by start time
        if (head == nullptr || head->start > start) {
            newAppt->next = head;
            head = newAppt;
        } else {
            Appointment* curr = head;
            while (curr->next != nullptr && curr->next->start < start) {
                curr = curr->next;
            }
            newAppt->next = curr->next;
            curr->next = newAppt;
        }
        cout << "Appointment booked successfully.\n";
    }

    void cancelAppointment() {
        string name;
        cout << "Enter appointment name to cancel: ";
        cin >> name;
        Appointment* curr = head;
        Appointment* prev = nullptr;

        while (curr != nullptr) {
            if (curr->name == name) {
                if (prev == nullptr) {
                    head = curr->next;
                } else {
                    prev->next = curr->next;
                }
                delete curr;
                cout << "Appointment canceled.\n";
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "Appointment not found.\n";
    }

    void displayAppointments() {
        cout << "\nAppointments:\n";
        if (!head) {
            cout << "No appointments scheduled.\n";
            return;
        }
        Appointment* curr = head;
        while (curr != nullptr) {
            cout << curr->name << ": " << minutesToTime(curr->start) << " - " << minutesToTime(curr->end) << "\n";
            curr = curr->next;
        }
    }

    // Sort list based on start time using data swapping
    void sortByTimeDataSwap() {
        if (!head || !head->next) return;
        bool swapped;
        do {
            swapped = false;
            Appointment* curr = head;
            while (curr->next != nullptr) {
                if (curr->start > curr->next->start) {
                    // swap data
                    swap(curr->name, curr->next->name);
                    swap(curr->start, curr->next->start);
                    swap(curr->end, curr->next->end);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
        cout << "Appointments sorted by time (data swap).\n";
    }

    // Sort list based on start time using pointer manipulation (bubble sort)
    void sortByTimePointer() {
        if (!head || !head->next) return;

        bool swapped;
        do {
            swapped = false;
            Appointment** curr = &head;
            while ((*curr)->next != nullptr) {
                if ((*curr)->start > (*curr)->next->start) {
                    Appointment* tmp = *curr;
                    *curr = (*curr)->next;
                    tmp->next = (*curr)->next;
                    (*curr)->next = tmp;
                    swapped = true;
                }
                curr = &(*curr)->next;
            }
        } while (swapped);

        cout << "Appointments sorted by time (pointer manipulation).\n";
    }

    ~AppointmentList() {
        Appointment* curr = head;
        while (curr != nullptr) {
            Appointment* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

int main() {
    // Define schedule day from 9:00 (540 mins) to 17:00 (1020 mins)
    AppointmentList appts(540, 1020);

    int choice;
    do {
        cout << "\nAppointment Management Menu:\n";
        cout << "1. Display free slots\n";
        cout << "2. Book appointment\n";
        cout << "3. Cancel appointment\n";
        cout << "4. Display all appointments\n";
        cout << "5. Sort appointments by time (data swap)\n";
        cout << "6. Sort appointments by time (pointer manipulation)\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: appts.displayFreeSlots(); break;
            case 2: appts.bookAppointment(); break;
            case 3: appts.cancelAppointment(); break;
            case 4: appts.displayAppointments(); break;
            case 5: appts.sortByTimeDataSwap(); break;
            case 6: appts.sortByTimePointer(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
