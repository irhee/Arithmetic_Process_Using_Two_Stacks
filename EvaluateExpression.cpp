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

void check_expression(string &e);
void doOp(stack<double> &valStk, stack<string> &opStk, double &ineq_double, string &ineq_string);
void repeatOps(string &refOp, stack<double> &valStk, stack<string> &opStk, double &ineq_double, string& ineq_string);
int main()
{
	string expression;
	expression = "1 + 2 - 3 * 4 / 5";
	cout << "\"" << expression << "\"" << endl;
	check_expression(expression);

	expression = "12 - 3 * 2 + 7";
	cout << "\"" << expression << "\"" << endl;
	check_expression(expression);

	expression = "14 <= 4 - 3 * 2 + 7";
	cout << "\"" << expression << "\"" << endl;
	check_expression(expression);

	expression = "14 <= 4 - 3 * 2 + 7 <= 16";
	cout << "\"" << expression << "\"" << endl;
	check_expression(expression);

	expression = "1 * 4 / 100 + 3 * 2 + 7";
	cout << "\"" << expression << "\"" << endl;
	check_expression(expression);

	expression = "19 >= 0 + 10 - 4 / 4 <= 8 * 7";
	cout << "\"" << expression << "\"" << endl;
	check_expression(expression);
	while (1)
	{
		cout << "Enter your expression: ";
		getline(cin, expression);
		check_expression(expression);
	}

	return 0;
}
void check_expression(string &e)
{
	//***************************
	//inside while loop for parsing the arithematic equation	
	const int MAX = e.length();
	int inc = 0;
	string parse;
	string del = " ";
	int add;
	stack<double> valStk;
	stack<string> opStk;
	//***************************
	//checking the inequality sign
	bool inq_true_false = false;
	bool bad_expression_counter = false;
	bool go_to = true;
	double inq_double;
	string inq_string;
	bool Positive = true;
	int newNegativeNumber;
	//***************************

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
				repeatOps(parse, valStk, opStk, inq_double, inq_string);
			}
			opStk.push(parse);
		}
		else if (parse.compare("+") == 0)
		{
			if (!opStk.empty())
			{
				repeatOps(parse, valStk, opStk, inq_double, inq_string);
			}
			opStk.push(parse);
		}
		else if (parse.compare("-") == 0)
		{
			Positive = false;
			parse = "+";

			if (!opStk.empty())
			{
				repeatOps(parse, valStk, opStk, inq_double, inq_string);
			}
			opStk.push(parse);
		}
		else if (parse.compare(">=") == 0 || parse.compare("<=") == 0)
		{

			if (bad_expression_counter)
			{
				cout << "BadExpression exception" << endl;
				go_to = false;
				break;
			}

			if (!opStk.empty())
			{
				repeatOps(parse, valStk, opStk, inq_double, inq_string);
			}
			inq_true_false = true;
			bad_expression_counter = true;
			opStk.push(parse);
		}
		else // Summation Subtraction
		{
			if (Positive == true)
			{
				valStk.push(stod(parse));
				Positive = true;
			}
			else
			{
				double a = stod(parse);
				valStk.push(a * (-1.0));
				Positive = true;
			}
		}
		e = e.substr(e.find(del) + 1, e.length());
		inc += add;
	}
	if (go_to)
	{
		if (Positive == true)
		{
			valStk.push(stod(e));
			Positive = true;
		}
		else
		{
			double a = stod(e);
			valStk.push(a * (-1.0));
			Positive = true;
		}

		parse = "$";
		repeatOps(parse, valStk, opStk, inq_double, inq_string);

		if (inq_true_false)
		{
			bad_expression_counter++;
			if (inq_string.compare(">=") == 0)
			{
				if (valStk.top() >= inq_double)
				{
					cout << "true." << endl;
				}
				else
				{
					cout << "false." << endl;
				}
			}
			else
			{
				if (valStk.top() <= inq_double)
				{
					cout << "true." << endl;
				}
				else
				{
					cout << "false." << endl;
				}
			}
		}
		else
		{
			cout << valStk.top() << endl;
		}
	}
}
void doOp(stack<double> &valStk, stack<string> &opStk, double &ineq_double, string &ineq_string)
{
	string op = opStk.top();
	opStk.pop();
	double ans;
	double x;
	double y;
	if (op.compare(">=") == 0)
	{
		ineq_string = ">=";
		ineq_double = valStk.top();
		valStk.pop();
	}
	else if (op.compare("<=") == 0)
	{
		ineq_string = "<=";
		ineq_double = valStk.top();
		valStk.pop();
	}
	else
	{
		x = valStk.top();
		valStk.pop();
		y = valStk.top();
		valStk.pop();
	}

	if (op.compare("*") == 0)
	{
		ans = y * x;
		valStk.push(ans);
	}
	else if (op.compare("/") == 0)
	{
		ans = y / x;
		valStk.push(ans);
	}
	else if (op.compare("+") == 0)
	{
		ans = y + x;
		valStk.push(ans);
	}
}
void repeatOps(string &refOp, stack<double> &valStk, stack<string> &opStk, double &ineq_double, string& ineq_string)
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
	if (opStk.empty())
	{

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

	while (valStk.size() > 1 && refInt <= opInt)
	{
		doOp(valStk, opStk, ineq_double, ineq_string);
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