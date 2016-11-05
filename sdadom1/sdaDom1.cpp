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

	string t1, t2;

	int lengthprefixExpressionInputStack = prefixExpressionInputStack.GetLength();
	
	DynamicStack<string> postfixExpression;
	string currentElement;
	DynamicStack<string> currentResultStack;
	double currentResult = -999999999;
	double helper;
	string h1, h2;
	cout << "helper: ";
	for (int i = 0; i < lengthprefixExpressionInputStack; i++)
	{
		if (isOperator(prefixExpressionInputStack.Peek(), currentIndex, signs))
		{
			t1 = postfixExpression.Peek();      
			postfixExpression.Pop();
			t2 = postfixExpression.Peek();
			postfixExpression.Pop();

			h1 = currentResultStack.Peek();
			currentResultStack.Pop();
			h2 = currentResultStack.Peek();
			currentResultStack.Pop();

			assert(istringstream(doOperation(h2, h1, prefixExpressionInputStack.Peek(),
				currentIndex, signs, operatorSigns)) >> helper);
			cout << helper << " ";
			currentResultStack.Push(std::to_string(helper));

			/*if (currentResult == -999999999)
			{
				assert(istringstream(doOperation(t1, t2, prefixExpressionInputStack.Peek(),
					currentIndex, signs, operatorSigns)) >> currentResult);
				cout << currentResult << " ";
			}
			else
			{
				assert(istringstream(doOperation(t2, std::to_string(currentResult), prefixExpressionInputStack.Peek(),
					currentIndex, signs, operatorSigns)) >> currentResult);
				cout << currentResult << " ";
			}*/
			
			t2 += " " + prefixExpressionInputStack.Peek();
			prefixExpressionInputStack.Pop();
			postfixExpression.Push(t1 + " " + t2);
		}
		else
		{
			currentResultStack.Push(prefixExpressionInputStack.Peek());

			postfixExpression.Push(prefixExpressionInputStack.Peek());
			prefixExpressionInputStack.Pop();
		}
	}
	cout << endl;
	
	DynamicStack<string> prefixExpressionStack;
	split(postfixExpression.Peek(), ' ', prefixExpressionInputStack);

	int prefixExpressionInputStackLength = prefixExpressionInputStack.GetLength();
	DynamicStack<string> finalStack;
	for (int i = 0; i < prefixExpressionInputStackLength; i++)
	{
		finalStack.Push(prefixExpressionInputStack.Peek());
		prefixExpressionInputStack.Pop();
	}
	
	int finstacklength = finalStack.GetLength();
	DynamicStack<string> result;

	for (int i = 0; i < finstacklength; i++)
	{
		if (isOperator(finalStack.Peek(), currentIndex, signs))
		{
			string num1 = result.Peek();
			result.Pop();
			string num2 = result.Peek();
			result.Pop();
			string operation = finalStack.Peek();
			finalStack.Pop();
			result.Push(doOperation(num1, num2, operation, currentIndex, signs, operatorSigns));
		}
		else
		{
			result.Push(finalStack.Peek());
			finalStack.Pop();
		}
	}

	assert(result.GetLength() == 1);
	assert(postfixExpression.GetLength() == 1);

	cout << postfixExpression.Peek() << endl;
	
	double finalResult;
	assert(istringstream(result.Peek()) >> finalResult);
	
	//round up double to 5 decimal places
	finalResult = round(finalResult * 100000.0) / 100000.0;

	cout << finalResult << endl;

	postfixExpression.Pop();
	result.Pop();

	system("pause");
}





