#include "ece250_socket.h"
#include <iostream>
#include <sstream> //new include!

int main()
{
	// Just for fun, let's reclassify "Dog"
	std::string text_to_classify = "Dog";
	std::string candidate_labels = "mamal,bird,fish";
	std::cout << labelText(text_to_classify, candidate_labels) << std::endl;

	return 0;
}