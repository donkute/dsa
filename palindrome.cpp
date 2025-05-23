#include <iostream>
#include <string>
#include <stack>
#include <cctype>  // for isalpha and tolower
using namespace std;

class PalindromeChecker {
public:
    void printReverse(const string& str);
    bool isPalindrome(const string& str);
};

void PalindromeChecker::printReverse(const string& str) {
    stack<char> charStack;

    // Push only alphabetic lowercase characters into stack
    for (char c : str) {
        if (isalpha(c)) {
            charStack.push(tolower(c));
        }
    }

    cout << "Original string: ";
    for (char c : str) {
        if (isalpha(c)) cout << c;
    }
    cout << "\nReversed string: ";
    while (!charStack.empty()) {
        cout << charStack.top();
        charStack.pop();
    }
    cout << endl;
}

bool PalindromeChecker::isPalindrome(const string& str) {
    stack<char> charStack;

    // Push alphabetic lowercase characters into stack
    for (char c : str) {
        if (isalpha(c)) {
            charStack.push(tolower(c));
        }
    }

    // Compare characters in original string with those popped from stack
    for (char c : str) {
        if (isalpha(c)) {
            if (charStack.top() != tolower(c)) return false;
            charStack.pop();
        }
    }

    return true;
}

int main() {
    PalindromeChecker checker;
    string input;

    cout << "Enter a string to check if it's a palindrome: ";
    getline(cin, input);

    checker.printReverse(input);

    if (checker.isPalindrome(input)) {
        cout << "\nThe string is a palindrome." << endl;
    } else {
        cout << "\nThe string is not a palindrome." << endl;
    }

    return 0;
}
