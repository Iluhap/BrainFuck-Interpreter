#include <iostream>
#include "BrainFuck.h"

int main()
{
	std::cout << "Input BrainFuck code:\n";

	std::string input_program;

	std::cin >> input_program;

	BrainFuck::Interpreter program(input_program);

	program.ExecuteProgram();

	std::cout << program.GetOutput() << std::endl;

	return 0;
}
