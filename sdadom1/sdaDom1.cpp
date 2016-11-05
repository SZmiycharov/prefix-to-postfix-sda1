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

using namespace std;

bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return true;
	return false;
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cerr << "Usage: " << argv[0] << " <FILENAME> <EXPRESSION>" << std::endl;
		return 1;

	}

	std::ifstream myfile(argv[1]);

	char associativity, sign;
	float number;
	int currentIndex = 0;
	char signs[100];
	char associativities[100];
	float numbers[100];

	if (myfile.is_open())
	{
		while (myfile >> sign >> associativity >> number)
		{
			cout << "sign: " << sign << ";";
			cout << " associativity: " << associativity;
			cout << " number: " << number << ";" << "\n";

			signs[currentIndex] = sign;
			associativities[currentIndex] = associativity;
			numbers[currentIndex] = number;
			++currentIndex;
		}

		myfile.close();
	}
	else
	{
		cout << "Unable to open file " << argv[1] << endl;
		return 1;
	}

	//for (int i = 0; i < currentIndex; ++i)
	//{
	//	cout << signs[i] << " ";
	//	cout << associativities[i] << " ";
	//	cout << numbers[i] << endl;
	//}

	/*cout << endl;

	for (int i = 2; i < argc; i++)
	{
		cout << argv[i] << " ";
	}
	cout << endl;*/


	/*string prefix;
	cin >> prefix;

	DynamicStack<string> st;
	string t1, t2;

	int l = prefix.length();
	for (int i = l - 1; i >= 0; i--)
	{
		if (isOperator(prefix[i]))
		{
			t1 = st.Peek();      
			st.Pop();
			t2 = st.Peek();      
			st.Pop();
			t2 += prefix[i];
			st.Push(t1 + t2);
		}
		else
		{
			t1 = "";
			t1 += prefix[i];
			st.Push(t1);
		}
	}

	string postfix = st.Peek();      
	st.Pop();
	cout << postfix << endl;*/

	system("pause");
}





