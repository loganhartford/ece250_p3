#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "Classifier.hpp"

int main()
{
	Classifier classifier;
	string command_line, command, argument;

	while (getline(cin, command_line))
	{
		istringstream command_stream(command_line);
		command_stream >> command;

		if (command == "LOAD")
		{
			command_stream >> argument;
			classifier.load(argument);
			cout << "success" << endl;
		}
		else if (command == "INSERT")
		{
			string classification;
			if (getline(command_stream >> ws, classification))
			{
				cout << classifier.insert(classification) << endl;
			}
		}
		else if (command == "CLASSIFY")
		{
			string input, output;
			if (getline(command_stream >> ws, input))
			{
				cout << classifier.classify(input) << endl;
			}
		}
		else if (command == "ERASE")
		{
			string classification;
			if (getline(command_stream >> ws, classification))
			{
				cout << classification << endl;
			}
		}
		else if (command == "PRINT")
		{
			classifier.print();
		}
		else if (command == "EMPTY")
		{
			cout << "empty " << endl;
		}
		else if (command == "CLEAR")
		{
			cout << "success" << endl;
		}
		else if (command == "SIZE")
		{
			cout << "number of classifications is " << endl;
		}
		else if (command == "EXIT")
		{
			break;
		}
	}

	return 0;
}
