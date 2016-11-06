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

void splitCharArrToStack(const char* str, char delim, DynamicStack<char*> &elems) {
	char buffer[10000];
	buffer[0] = 0;
	char test[10000];
	int index = 0;
	
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == delim && buffer[0] != 0)
		{
			for (int j = 0; j < strlen(buffer); j++)
			{

			}
			elems.Push(buffer);
			memset(buffer, 0, 10000);
			buffer[0] = 0;
			index = 0;
		}
		else
		{
			buffer[index] = str[i];
			++index;
		}
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

	double firstNum;
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
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " <FILENAME> <FILENAME>" << std::endl;
		return 1;
	}

	DynamicStack<char*> prefixExpressionInputStack;
	std::ifstream fileSigns(argv[1]);
	
	char operatorSign, sign;
	char signs[10000], operatorSigns[10000];
	double associativities[10000];
	float associativity;
	int currentIndex = 0;
	
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

	char prefixExpression[10000];
	int index = 0;
	char ch;
	fstream fileExpression(argv[2], fstream::in);

	if (fileExpression.is_open())
	{
		while (fileExpression >> noskipws >> ch) 
		{
			prefixExpression[index] = ch;
			++index;
		}
		fileExpression.close();
	}
	else
	{
		cout << "Unable to open file " << argv[2] << endl;
		return 1;
	}

	
	splitCharArrToStack(prefixExpression, ' ', prefixExpressionInputStack);

	int length = prefixExpressionInputStack.GetLength();
	cout << endl;
	for (int i = 0; i < length; i++)
	{
		cout << prefixExpressionInputStack.Top() << " ";
		prefixExpressionInputStack.Pop();
	}
	cout << endl;

	/*
	string postfixExprElement1, postfixExprElement2;
	string currentResultStackElement1, currentResultStackElement2;
	int lengthPrefixExpressionInputStack = prefixExpressionInputStack.GetLength();
	double currentResult;
	DynamicStack<string> postfixExpression;
	DynamicStack<string> currentResultStack;
	
	for (int i = 0; i < lengthPrefixExpressionInputStack; i++)
	{
		if (isOperator(prefixExpressionInputStack.Top(), currentIndex, signs))
		{
			postfixExprElement1 = postfixExpression.Top();      
			postfixExpression.Pop();
			postfixExprElement2 = postfixExpression.Top();
			postfixExpression.Pop();

			currentResultStackElement1 = currentResultStack.Top();
			currentResultStack.Pop();
			currentResultStackElement2 = currentResultStack.Top();
			currentResultStack.Pop();

			assert(istringstream(doOperation(currentResultStackElement2, currentResultStackElement1, prefixExpressionInputStack.Top(),
				currentIndex, signs, operatorSigns)) >> currentResult);
			currentResultStack.Push(std::to_string(currentResult));
			
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

	assert(postfixExpression.GetLength() == 1);

	cout << postfixExpression.Top() << endl;
	cout << currentResult << endl;*/
	
	system("pause");
}





