#include "methods.h"

using namespace std;

bool isBalanced(string expr)
{
	stack<char> s;
	char ch;

	for (int i = 0; i < expr.length(); i++)		// Traversing through the string
	{
		if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{')	// If the character is an opening bracket
		{
			s.push(expr[i]);
			continue;
		}

		switch (expr[i])		// If a closing bracket is encountered, the top of the stack is checked to see if it is a valid pair or not
		{
		case ')':
			ch = s.top();
			s.pop();
			if (ch == '{' || ch == '[')
				return false;
			break;
		case '}':
			ch = s.top();
			s.pop();
			if (ch == '(' || ch == '[')
				return false;
			break;
		case ']':
			ch = s.top();
			s.pop();
			if (ch == '(' || ch == '{')
				return false;
			break;
		default:
			break;
		}
	}

	return s.empty();	// After performing all checks, if the stack is empty, then return true. If not, that means there is an extra bracket and return false
}

bool isValid(string expr)
{
	if (!(isBalanced(expr)))	// Returning false if the brackets in the expression are not valid
		return false;

	string s = expr;
	while (s[0] == ' ' || s[0] == '\t')
	{
		s.erase(s.begin());
		
		if (s.length() == 0 || s.length() == 1 || s.length() == 2) // The expression is valid only if the length is a minimum of 3
			return false;
		if (s[0] == '+' || s[0] == '-' || s[0] == '/' || s[0] == '%' || s[0] == '*' || s[0] == '^') // If the expression starts with an operator
			return false;
	}
	
	for (int i = 1; i < s.length(); i++)
	{
		if (s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '%' || s[i] == '*' || s[i] == '^')
		{
			int j = i - 1;								// Checking if character before an operator is also an operator
			while (s[j] == ' ' || s[j] == '\t')
			{
				j--;
			}
			if (s[j] == '+' || s[j] == '-' || s[j] == '/' || s[j] == '%' || s[j] == '*' || s[j] == '^')
				return false;
			else
			{
				j = i + 1;								// Checking if the next character after an operator is a closing bracket or operator
				while (s[j] == ' ' || s[j] == '\t')
				{
					j++;
				}
				if (s[j] == ')' || s[j] == ']' || s[j] == '}' || s[j] == '+' || s[j] == '-' || s[j] == '/' || s[j] == '%' || s[j] == '*' || s[j] == '^')
					return false;
			}
				
		}
	}
	
	while (s.length() != 0)
	{
		string::iterator i = s.end();
		char end = *(i - 1);

		if (end == ')' || end == ']' || end == '}' || end == ' ' || end == '\t')	// If the last character is a bracket or space, move back one space
		{
			s.pop_back();
			continue;
		}
			
		if (end == '+' || end == '-' || end == '/' || end == '%' || end == '*' || end == '^')		// If the last character is an operator, the expression is invalid
			return false;
		else
			return true;
	}
}

int getPrecedence(char c)
{
	if (c == '+' || c == '-')
		return 0;
	if (c == '*' || c == '/' || c == '%')
		return 1;
	if (c == '^')
		return 2;
	return -1;
}

string infixToPostfix(string infix)
{
	if (!(isValid(infix)))
		return " ";

	for (int i = 0; i < infix.length(); i++) // Replacing other types of brackets to make the code simpler
	{
		if (infix[i] == '[' || infix[i] == '{')
			infix[i] = '(';
		if (infix[i] == ']' || infix[i] == '}')
			infix[i] = ')';
	}
	
	string postfix = " ";
	stack<char> s;

	for (int i = 0; i < infix.length(); i++)
	{
		if (infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '%' && infix[i] != '^' && infix[i] != ' ' && infix[i] != '\t' && infix[i] != '(' && infix[i] != ')')
			postfix += infix[i];
		else if (infix[i] == '(')
			s.push(infix[i]);
		else if (infix[i] == ')')
		{
			while (!(s.empty()))
			{
				postfix += s.top();
				s.pop();
				if (s.top() == '(')
				{
					s.pop();
					break;
				}
			}
		}
		else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '%' || infix[i] == '^')
		{
			if (s.empty())
				s.push(infix[i]);
			else
			{
				int pt = getPrecedence(s.top());
				int pe = getPrecedence(infix[i]);

				if (pe > pt)							// If precedence is greater
					s.push(infix[i]);
				else if (pe == pt && infix[i] == '^')	// If precedence is equal and the operator is '^'
					s.push(infix[i]);
				else									// If precendence is less than or equal, then pop and print till the precedence becomes greater and then push current value onto the stack
				{
					while (pe <= pt)	
					{
						postfix += s.top();
						s.pop();
						if (s.empty())
							break;
						pt = getPrecedence(s.top());
					}
					s.push(infix[i]);
				}
			}
		}
	}

	while (!s.empty())
	{
		postfix += s.top();
		s.pop();
	}

	return postfix;
}