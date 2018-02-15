// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

/******************************************************************************
Insoo Rhee 301075548 ira3@sfu.ca
Assignment 3.
Qeustion 2.
Arithmetic process using two stacks
*******************************************************************************/
#include <iostream>
#include <string>
#include <stack>

using namespace std;

enum operators
{
	dollar_sign = 0,
	ineq,
	sum_sub,
	mult_div,
};

void check_expression(string &e, stack<double> &valStk, stack<string> &opStk);
void doOp(stack<double> &valStk, stack<string> &opStk);
void repeatOps(string &refOp, stack<double> &valStk, stack<string> &opStk);
int main()
{
	stack<double> val[30];
	stack<string> op[30];
	string expression = "1 + 2 - 3 * 4 / 5";
	cout << "\"" << expression << "\"" << endl;
	check_expression(expression, val[0], op[0]);

	expression = "12 - 3 * 2 + 7";
	cout << "\"" << expression << "\"" << endl;
	check_expression(expression, val[1], op[1]);

	expression = "14 / 4 - 3 * 2 + 7";
	cout << "\"" << expression << "\"" << endl;
	check_expression(expression, val[2], op[2]);

	return 0;
}
void check_expression(string &e, stack<double> &valStk, stack<string> &opStk)
{
	string parse;
	const int MAX = e.length();
	int inc = 0;
	string del = " ";
	int add;
	bool Positive = true;
	int newNegativeNumber;

	while (inc < MAX)
	{
		add = e.find(del);
		if (add == -1)
		{
			break;
		}
		parse = e.substr(0, e.find(del));
		if (parse.compare("*") == 0 || parse.compare("/") == 0)
		{
			if (!opStk.empty())
			{
				repeatOps(parse, valStk, opStk);
			}
			opStk.push(parse);
		}
		else if (parse.compare("+") == 0) // +
		{
			if (!opStk.empty())
			{
				repeatOps(parse, valStk, opStk);
			}
			opStk.push(parse);
		}
		else if (parse.compare("-") == 0)
		{
			parse = "+";
			if (!opStk.empty())
			{
				repeatOps(parse, valStk, opStk);
			}
			opStk.push(parse);

			cout << "1"<< opStk.top() << endl;
			Positive = false;
		}
		else if (parse.compare(">=") == 0 || parse.compare("<=") == 0) // -
		{
			if (!opStk.empty())
			{
				repeatOps(parse, valStk, opStk);
			}
			opStk.push(parse);
		}
		else if (Positive == true) // Summation
		{
			valStk.push(stoi(parse));
			Positive = true;
		}
		else if (Positive == false)// Subtract
		{
			valStk.push(stoi(parse)*(-1));
			Positive = true;
		}

		e = e.substr(e.find(del) + 1, e.length());
		inc += add;
	}
	valStk.push(stoi(e));
	parse = "$";
	repeatOps(parse, valStk, opStk);

	cout << valStk.top() << endl;
}
void doOp(stack<double> &valStk, stack<string> &opStk)
{
	double y = valStk.top();
	valStk.pop();
	double x = valStk.top();
	valStk.pop();
	string op = opStk.top();
	opStk.pop();
	double ans;
	if (op.compare("*") == 0)
	{
		ans = x * y;
		valStk.push(ans);
		cout << "*" << ans << endl;
	}
	else if (op.compare("/") == 0)
	{
		ans = x / y;
		valStk.push(ans);
		cout << "/" << ans << endl;
	}
	else if (op.compare("+") == 0)
	{
		ans = x + y;
		valStk.push(ans);
		cout << "+" << ans << endl;
	}
	else if (op.compare(">=") == 0)
	{
		valStk.push(ans);
	}
	else if (op.compare("<=") == 0)
	{
		valStk.push(ans);
	}
}
void repeatOps(string &refOp, stack<double> &valStk, stack<string> &opStk)
{
	int refInt;
	if (refOp.compare("*") == 0)
	{
		refInt = mult_div;
	}
	else if (refOp.compare("/") == 0)
	{
		refInt = mult_div;
	}
	else if (refOp.compare("+") == 0)
	{
		refInt = sum_sub;
	}
	else if (refOp.compare(">=") == 0)
	{
		refInt = ineq;
	}
	else if (refOp.compare("<=") == 0)
	{
		refInt = ineq;
	}
	else if (refOp.compare("$") == 0)
	{
		refInt = dollar_sign;
	}

	int opInt;
	string opStkTop = opStk.top();
	if (opStkTop.compare("*") == 0)
	{
		opInt = mult_div;
	}
	else if (opStkTop.compare("/") == 0)
	{
		opInt = mult_div;
	}
	else if (opStkTop.compare("+") == 0)
	{
		opInt = sum_sub;
	}
	else if (opStkTop.compare(">=") == 0)
	{
		opInt = ineq;
	}
	else if (opStkTop.compare("<=") == 0)
	{
		opInt = ineq;
	}
	else if (opStkTop.compare("$") == 0)
	{
		opInt = dollar_sign;
	}

	while (valStk.size() > 1 && refInt <= opInt)
	{
		doOp(valStk, opStk);
		if (opStk.empty())
		{
			break;
		}
		string opStkTop = opStk.top();
		if (opStkTop.compare("*") == 0)
		{
			opInt = mult_div;
		}
		else if (opStkTop.compare("/") == 0)
		{
			opInt = mult_div;
		}
		else if (opStkTop.compare("+") == 0)
		{
			opInt = sum_sub;
		}
		else if (opStkTop.compare(">=") == 0)
		{
			opInt = ineq;
		}
		else if (opStkTop.compare("<=") == 0)
		{
			opInt = ineq;
		}
		else if (opStkTop.compare("$") == 0)
		{
			opInt = dollar_sign;
		}
	}
}