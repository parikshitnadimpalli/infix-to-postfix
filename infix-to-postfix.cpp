#include "methods.h"
using namespace std;

int main()
{
	cout << "\t\t\t|--------Infix to Postfix conversion using a stack--------|" << endl << endl;
	cout << "\t\tNOTE: You can use any type of brackets. Just be sure to properly balance them in your expression :)" << endl;

	string msg, postfix, infix;

	cout << endl << "Enter the infix expression to be converted: ";
	getline(cin, infix);
	postfix = infixToPostfix(infix);

	msg = postfix == " " || postfix == infix ? "Invalid infix expression entered!" : postfix; // Checking to see if user input is valid or not
	cout << endl << "The converted expression is:\n" << msg;

	return 0;
}