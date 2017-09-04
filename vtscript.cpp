#include <iostream>
#include <fstream>
#include <sstream>

#include "interpreter.hpp"
#include "expression.hpp"

void cOutputExp(const Expression& expres);

void cOutputExp(const Expression& expres)
{
	if (expres.getType() == Boolean)
	{
		if (expres.getBoolValue()) {
			std::cout << "(True)" << std::endl;
		}
		else {
			std::cout << "(False)" << std::endl;
		}
	}
	else if (expres.getType() == Number) {
		std::cout << '(' << expres.getDoubleValue() << ')' << std::endl;
	}
	else {
		std::cout << '(' << expres.getSymbolValue() << ')' << std::endl;
	}
}

int main(int argc, char * argv[])
{

	if (argc == 1) //repl
	{
		
		std::string program;
		
		Interpreter repl;
		
		std::cout << "vtscript> ";
		getline(std::cin, program);
		while (!std::cin.eof())
		{
			std::istringstream iss(program);
			if (!repl.parse(iss))
				std::cerr << "Error: parse error" << std::endl;
			else
			{
				Expression result;
				try {
					result = repl.eval();
				}
				catch (const InterpreterSemanticError ex)
				{
					std::cerr << ex.what();
				}
				cOutputExp(result);
			}
			std::cout << "vtscript> ";
			getline(std::cin, program);
		}
	}
	else if (argc == 2 && argv[2] != "-e") //input file
	{
		std::string fileName;
		fileName = argv[1];
		std::ifstream ifs(fileName);
		Interpreter repl;
		if (!repl.parse(ifs))
		{
			std::cerr << "Error: parse error" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		Expression exp;
		try {
			exp = repl.eval();
		}
		catch (const InterpreterSemanticError ex)
		{
			std::cerr << ex.what();
			std::exit(EXIT_FAILURE);
		}
		cOutputExp(exp);

	}
	else //immediate script
	{
		std::string arg2(argv[1]);
		if (arg2 == "-e")
		{
			std::string program = argv[2];
			std::istringstream iss(program);
			Interpreter repl;
			if (!repl.parse(iss))
			{
				std::cerr << "Error: parse error" << std::endl;
				std::exit(EXIT_FAILURE);
			}
			Expression exp;
			try {
				exp = repl.eval();
			}
			catch (const InterpreterSemanticError ex)
			{
				std::cerr << ex.what();
				std::exit(EXIT_FAILURE);
			}
			cOutputExp(exp);
		}
	}
	std::exit(EXIT_SUCCESS);
	return 0;
}