/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Stanislav Zmiycharov
* @idnumber 61883
* @task 1
* @compiler VC
*
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include <stdlib.h>
#include "DynamicStack.h"

using namespace std;

void splitStringToStack(const string &s, char delimeter, DynamicStack<string> &elems) {
	stringstream ss;
	ss.str(s);
	string item;

	while (getline(ss, item, delimeter)) {
		elems.Push(item);
	}
}

bool isOperator(string c, int length, char signs[10000])
{
	for (int i = 0; i < length; i++)
	{
		if (signs[i] == c[0])
		{
			return true;
		}
	}

	return false;
}

string doOperation(string firstOperand, string secondOperand, string operationChar, int length, char signs[10000], char actualOperators[10000])
{
	if (operationChar.length() > 1)
	{
		cerr << "Expected char(symbol), got '" << operationChar << "' (string) instead!\n";
		exit(EXIT_FAILURE);
	}

	char operation;
	for (int i = 0; i < length; i++)
	{
		if (signs[i] == operationChar[0])
		{
			operation = actualOperators[i];
			break;
		}
	}

	double firstNum;
	assert(istringstream(firstOperand) >> firstNum);

	double secondNum;
	assert(istringstream(secondOperand) >> secondNum);

	if (firstNum == 0 && operation == '/')
	{
		cerr << "Devision by zero error!\n";
		exit(EXIT_FAILURE);
	}

	switch (operation)
	{
		case '*':
			return to_string(secondNum * firstNum); break;
		case '/':
			return to_string(secondNum / firstNum); break;
		case '+':
			return to_string(secondNum + firstNum); break;
		case '-':
			return to_string(secondNum - firstNum); break;
		default:
			cerr << "Illegal operation description for '" << operationChar[0] << "' !\n";
			exit(EXIT_FAILURE);
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] << " <FILENAME> <FILENAME>" << "\n";
		system("pause");
		exit(EXIT_FAILURE);
	}

	DynamicStack<string> prefixExpressionInputStack;
	ifstream fileSigns(argv[1]);
	ifstream fileExpression(argv[2]);

	char sign, actualOperator;
	char signs[10000], actualOperators[10000];
	double associativities[10000];
	double associativity;
	int currentIndex = 0;
	
	if (fileSigns.is_open())
	{
		while (fileSigns >> sign >> actualOperator >> associativity)
		{
			signs[currentIndex] = sign;
			actualOperators[currentIndex] = actualOperator;
			associativities[currentIndex] = associativity;
			++currentIndex;
		}

		fileSigns.close();
	}
	else
	{
		cerr << "Unable to open file " << argv[1] << "\n";
		exit(EXIT_FAILURE);
	}

	string prefixExpression;

	if (fileExpression.is_open())
	{
		getline(fileExpression, prefixExpression);
		fileExpression.close();
	}
	else
	{
		cerr << "Unable to open file " << argv[2] << "\n";
		exit(EXIT_FAILURE);
	}

	splitStringToStack(prefixExpression, ' ', prefixExpressionInputStack);

	string postfixExprElement1, postfixExprElement2;
	string currentResultStackElement1, currentResultStackElement2;
	int lengthPrefixExpressionInputStack = prefixExpressionInputStack.GetLength();
	double currentResult;
	DynamicStack<string> postfixExpression;
	DynamicStack<string> currentResultStack;
	
	for (int i = 0; i < lengthPrefixExpressionInputStack; i++)
	{
		if (prefixExpressionInputStack.isEmpty())
		{
			cerr << "Error\n";
			exit(EXIT_FAILURE);
		}

		if (isOperator(prefixExpressionInputStack.Top(), currentIndex, signs))
		{
			if (postfixExpression.GetLength() < 2)
			{
				cerr << "Error\n";
				exit(EXIT_FAILURE);
			}

			postfixExprElement1 = postfixExpression.Top();      
			postfixExpression.Pop();
			postfixExprElement2 = postfixExpression.Top();
			postfixExpression.Pop();

			currentResultStackElement1 = currentResultStack.Top();
			currentResultStack.Pop();
			currentResultStackElement2 = currentResultStack.Top();
			currentResultStack.Pop();

			assert(istringstream(doOperation(currentResultStackElement2, currentResultStackElement1, prefixExpressionInputStack.Top(),
				currentIndex, signs, actualOperators)) >> currentResult);
			currentResultStack.Push(to_string(currentResult));
			
			postfixExprElement2 += " " + prefixExpressionInputStack.Top();
			prefixExpressionInputStack.Pop();
			postfixExpression.Push(postfixExprElement1 + " " + postfixExprElement2);
		}
		else
		{
			currentResultStack.Push(prefixExpressionInputStack.Top());

			postfixExpression.Push(prefixExpressionInputStack.Top());
			prefixExpressionInputStack.Pop();
		}
	}

	string postfixExpressionResult = postfixExpression.Top();
	postfixExpression.Pop();

	if (!postfixExpression.isEmpty())
	{
		cerr << "Error\n";
		exit(EXIT_FAILURE);
	}

	cout << postfixExpressionResult << "\n";
	cout.precision(5);	
	cout << fixed << currentResult << "\n";
	
	system("pause");
}





