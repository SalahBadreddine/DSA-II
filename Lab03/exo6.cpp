#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool checkExpression (const string& expression)  {
    int n = expression.length();
    stack<char> opening;
    for (int i=0; i<n; i++) {
        if (expression[i] == '[' || expression[i] == '(') {
            opening.push(expression[i]);
        } else if (expression[i] == ']') {
            char last_open = opening.top();
            opening.pop();
            if (last_open != '[') {
                return false;
            }
        } else if (expression[i] == ')') {
            char last_open = opening.top();
            opening.pop();
            if (last_open != '(') {
                return false;
            }
        }
    }
    // Check if the stack is empty 
    if (!opening.empty()){
        return false;
    }
    return true;
}

int main() 
{
    string Trueexpression = "((x+5) * y) = [(23+y)*7]";
    string Wronexpression1 = "((x+5) * y = [(23+y)*7]";
    string Wronexpression2 = "((x+5) * y = [(23+y)*7]";
    cout << (checkExpression(Trueexpression) ? "Yes" : "No") << endl;
    cout << (checkExpression(Wronexpression1) ? "Yes" : "No") << endl;
    cout << (checkExpression(Wronexpression2) ? "Yes" : "No") << endl;
    return 0;
}