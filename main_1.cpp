#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
	// Trie trie;
	string command_line, command, argument;

	while (getline(cin, command_line))
	{
		istringstream command_stream(command_line);
		command_stream >> command;

		if (command == "LOAD")
		{
			command_stream >> argument;
			cout << "success" << endl;
		}
		else if (command == "INSERT")
		{
			string classification;
			if (getline(command_stream, classification))
			{
				cout << classification << endl;
			}
		}
		else if (command == "CLASSIFY")
		{
			string input, output;
			if (getline(command_stream, input))
			{
				cout << input << endl;
			}
		}
		else if (command == "ERASE")
		{
			string classification;
			if (getline(command_stream, classification))
			{
				cout << classification << endl;
			}
		}
		else if (command == "PRINT")
		{
			cout << "print" << endl;
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
