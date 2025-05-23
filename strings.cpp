#include <iostream>
#include <string>
using namespace std;

class StringOps {
    string str;
public:
    void input() {
        cout << "Enter string: ";
        getline(cin, str);
    }

    void freqChar() {
        char ch; int count = 0;
        cout << "Char to find: "; cin >> ch;
        for (char c : str) if (c == ch) count++;
        cout << "Frequency: " << count << '\n';
    }

    void substring() {
        int start, len;
        cout << "Start pos and length: ";
        cin >> start >> len;
        if (start >= 0 && start < (int)str.size())
            cout << str.substr(start, len) << '\n';
        else
            cout << "Invalid start!\n";
    }

    void removeChar() {
        char ch; cout << "Char to remove: "; cin >> ch;
        string res = "";
        for (char c : str) if (c != ch) res += c;
        cout << res << '\n';
    }

    void replaceSub() {
        string oldS, newS;
        cout << "Replace substring: ";
        cin >> oldS;
        cout << "With: ";
        cin >> newS;
        size_t pos = str.find(oldS);
        if (pos != string::npos) {
            str.replace(pos, oldS.size(), newS);
            cout << str << '\n';
        } else cout << "Not found!\n";
    }

    void palindrome() {
        string rev = string(str.rbegin(), str.rend());
        cout << (str == rev ? "Palindrome\n" : "Not palindrome\n");
    }
};

int main() {
    StringOps s; s.input();
    int ch;
    do {
        cout << "1.Freq 2.Substr 3.Remove 4.Replace 5.Palindrome 6.Exit: ";
        cin >> ch; cin.ignore();
        switch (ch) {
            case 1: s.freqChar(); break;
            case 2: s.substring(); break;
            case 3: s.removeChar(); break;
            case 4: s.replaceSub(); break;
            case 5: s.palindrome(); break;
            case 6: cout << "Exit\n"; break;
            default: cout << "Invalid\n";
        }
    } while (ch != 6);
}
