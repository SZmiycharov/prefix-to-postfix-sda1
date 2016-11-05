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
* @compiler GCC
*
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <map>
#include "DynamicStack.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <assert.h>

using namespace std;

double cint(double x){
	if (modf(x, 0) >= .5)
		return x >= 0 ? ceil(x) : floor(x);
	else
		return x<0 ? ceil(x) : floor(x);
}

double round(double r, unsigned places){
	double off = pow(10, places);
	return cint(r*off) / off;
}

void split(const std::string &s, char delim, DynamicStack<string> &elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.Push(item);
	}
}

bool isOperator(string c, int length, char signs[100])
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

string doOperation(string firstOperand, string secondOperand, string operationChar, int length, char signs[100], char operatorSigns[100])
{
	char operation;
	for (int i = 0; i < length; i++)
	{
		if (signs[i] == operationChar[0])
		{
			operation = operatorSigns[i];
			break;
		}
	}

	double firstNum = 0;
	assert(istringstream(firstOperand) >> firstNum);

	double secondNum;
	assert(istringstream(secondOperand) >> secondNum);

	switch (operation)
	{
		case '*':
			return std::to_string(secondNum * firstNum); break;
		case '/':
			return std::to_string(secondNum / firstNum); break;
		case '+':
			return std::to_string(secondNum + firstNum); break;
		case '-':
			return std::to_string(secondNum - firstNum); break;
	}
}

int main(int argc, char* argv[])
{
	DynamicStack<string> prefixExpressionInputStack;
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <FILENAME> <FILENAME>" << std::endl;
		return 1;
	}

	std::ifstream fileSigns(argv[1]);
	std::ifstream fileExpression(argv[2]);

	char operatorSign, sign;
	float associativity;
	int currentIndex = 0;
	char signs[100];
	char operatorSigns[100];
	double associativities[100];

	if (fileSigns.is_open())
	{
		while (fileSigns >> sign >> operatorSign >> associativity)
		{
			signs[currentIndex] = sign;
			operatorSigns[currentIndex] = operatorSign;
			associativities[currentIndex] = associativity;
			++currentIndex;
		}

		fileSigns.close();
	}
	else
	{
		cout << "Unable to open file " << argv[1] << endl;
		return 1;
	}

	string prefixExpression;

	if (fileExpression.is_open())
	{
		getline(fileExpression, prefixExpression);
		fileExpression.close();
	}
	else
	{
		cout << "Unable to open file " << argv[2] << endl;
		return 1;
	}

	split(prefixExpression, ' ', prefixExpressionInputStack);

	string postfixExprElement1, postfixExprElement2;
	string currentResultStackElement1, currentResultStackElement2;

	int lengthPrefixExpressionInputStack = prefixExpressionInputStack.GetLength();
	DynamicStack<string> postfixExpression;
	DynamicStack<string> currentResultStack;
	double currentResult;
	

	for (int i = 0; i < lengthPrefixExpressionInputStack; i++)
	{
		if (isOperator(prefixExpressionInputStack.Peek(), currentIndex, signs))
		{
			postfixExprElement1 = postfixExpression.Peek();      
			postfixExpression.Pop();
			postfixExprElement2 = postfixExpression.Peek();
			postfixExpression.Pop();

			currentResultStackElement1 = currentResultStack.Peek();
			currentResultStack.Pop();
			currentResultStackElement2 = currentResultStack.Peek();
			currentResultStack.Pop();

			assert(istringstream(doOperation(currentResultStackElement2, currentResultStackElement1, prefixExpressionInputStack.Peek(),
				currentIndex, signs, operatorSigns)) >> currentResult);
			currentResultStack.Push(std::to_string(currentResult));
			
			postfixExprElement2 += " " + prefixExpressionInputStack.Peek();
			prefixExpressionInputStack.Pop();
			postfixExpression.Push(postfixExprElement1 + " " + postfixExprElement2);
		}
		else
		{
			currentResultStack.Push(prefixExpressionInputStack.Peek());

			postfixExpression.Push(prefixExpressionInputStack.Peek());
			prefixExpressionInputStack.Pop();
		}
	}

	assert(postfixExpression.GetLength() == 1);

	cout << postfixExpression.Peek() << endl;
	cout << currentResult << endl;
	
	system("pause");
}





