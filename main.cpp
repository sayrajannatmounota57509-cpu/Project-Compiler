#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;

int main() {
    ifstream file("hello.txt");

    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    set<string> keywords = {
        "int", "float", "double", "char", "void",
        "if", "else", "while", "for", "return",
        "using", "namespace", "include", "const",
        "bool", "true", "false"
    };

    char ch;
    string token;

    while (file.get(ch)) {

        // Ignore whitespace
        if (ch == ' ' || ch == '\n' || ch == '\t' ||
            ch == '\r') {
            continue;
        }

        // Check for identifier or keyword
        if ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') || ch == '_') {

            token = ch;

            while (file.peek() != EOF) {
                char next = file.peek();

                if ((next >= 'A' && next <= 'Z') ||
                    (next >= 'a' && next <= 'z') ||
                    (next >= '0' && next <= '9') ||
                    next == '_') {

                    file.get(ch);
                    token += ch;
                } else {
                    break;
                }
            }

            if (keywords.count(token))
                cout << token << " : Keyword" << endl;
            else
                cout << token << " : Identifier" << endl;
        }

        // Check for numeric constants
        else if (ch >= '0' && ch <= '9') {

            token = ch;

            while (file.peek() != EOF) {
                char next = file.peek();

                if ((next >= '0' && next <= '9') ||
                    next == '.') {

                    file.get(ch);
                    token += ch;
                } else {
                    break;
                }
            }

            cout << token << " : Constant" << endl;
        }

        // Check for string constants
        else if (ch == '"') {

            token = "\"";

            while (file.get(ch)) {
                token += ch;

                if (ch == '"')
                    break;
            }

            cout << token << " : Constant (String)" << endl;
        }

        // Check for punctuation and operators
        else {
            if (ch == '<' && file.peek() == '<') {
                file.get(ch);
                cout << "<< : Operator" << endl;
            }

            else if (ch == '+' || ch == '-' ||
                     ch == '*' || ch == '/' ||
                     ch == '=' || ch == '<' ||
                     ch == '>' || ch == '%') {

                cout << ch << " : Operator" << endl;
            }

            else {
                cout << ch << " : Punctuation" << endl;
            }
        }
    }

    file.close();
    return 0;
}
