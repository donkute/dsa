#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

class Expression {
public:
    void infix_to_prefix();
    void prefix_to_postfix();
    void prefix_to_infix();
    void postfix_to_infix();
    void postfix_to_prefix();

private:
    int precedence(char op);
    bool is_operator(char ch);
};

int Expression::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

bool Expression::is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void Expression::infix_to_prefix() {
    string infix, prefix;
    cin >> infix;
    reverse(infix.begin(), infix.end());
    for (char& ch : infix) {
        if (ch == '(') ch = ')';
        else if (ch == ')') ch = '(';
    }
    stack<char> s;
    for (char ch : infix) {
        if (isalnum(ch)) prefix = ch + prefix;
        else if (ch == '(') s.push(ch);
        else if (ch == ')') {
            while (s.top() != '(') { prefix = s.top() + prefix; s.pop(); }
            s.pop();
        } else {
            while (!s.empty() && precedence(s.top()) > precedence(ch)) {
                prefix = s.top() + prefix; s.pop();
            }
            s.push(ch);
        }
    }
    while (!s.empty()) { prefix = s.top() + prefix; s.pop(); }
    cout << prefix << endl;
}

void Expression::prefix_to_postfix() {
    string pre;
    cin >> pre;
    stack<string> s;
    for (int i = pre.size() - 1; i >= 0; i--) {
        if (isalnum(pre[i])) s.push(string(1, pre[i]));
        else {
            string a = s.top(); s.pop();
            string b = s.top(); s.pop();
            s.push(a + b + pre[i]);
        }
    }
    cout << s.top() << endl;
}

void Expression::prefix_to_infix() {
    string pre;
    cin >> pre;
    stack<string> s;
    for (int i = pre.size() - 1; i >= 0; i--) {
        if (isalnum(pre[i])) s.push(string(1, pre[i]));
        else {
            string a = s.top(); s.pop();
            string b = s.top(); s.pop();
            s.push("(" + a + pre[i] + b + ")");
        }
    }
    cout << s.top() << endl;
}

void Expression::postfix_to_infix() {
    string post;
    cin >> post;
    stack<string> s;
    for (char ch : post) {
        if (isalnum(ch)) s.push(string(1, ch));
        else {
            string b = s.top(); s.pop();
            string a = s.top(); s.pop();
            s.push("(" + a + ch + b + ")");
        }
    }
    cout << s.top() << endl;
}

void Expression::postfix_to_prefix() {
    string post;
    cin >> post;
    stack<string> s;
    for (char ch : post) {
        if (isalnum(ch)) s.push(string(1, ch));
        else {
            string b = s.top(); s.pop();
            string a = s.top(); s.pop();
            s.push(ch + a + b);
        }
    }
    cout << s.top() << endl;
}

int main() {
    Expression e;
    int choice;
    do {
        cout << "\n1. Infix to Prefix\n2. Prefix to Postfix\n3. Prefix to Infix\n4. Postfix to Infix\n5. Postfix to Prefix\n6. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: e.infix_to_prefix(); break;
            case 2: e.prefix_to_postfix(); break;
            case 3: e.prefix_to_infix(); break;
            case 4: e.postfix_to_infix(); break;
            case 5: e.postfix_to_prefix(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid!\n";
        }
    } while (choice != 6);
    return 0;
}
