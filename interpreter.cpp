#include "interpreter.hpp"

Interpreter::Interpreter()
{
	
}

bool Interpreter::parse(std::istream & expression) noexcept
{
	if (!expression.good()) {
		return false;
	}
	
	if (!tokenizer.parse(expression)) {
		return false;
	}
	return(tokenizer.buildAST());
}


Expression Interpreter::eval()
{
	return evaluate(tokenizer.getSyntaxTree());;
}

Expression Interpreter::evaluate(const Expression& tree)
{
	if (tree.getType() == Symbol)
	{
		std::string token = tree.getSymbolValue();
		if (defaultEnviron.symbolMap.find(token) != defaultEnviron.symbolMap.end()) {
			return defaultEnviron.symbolMap.at(token);
		}
		else if (token == "define")
		{
			if (tree.children.size() != 2) {
				throw InterpreterSemanticError("Error: define takes 2 arguments");
			}
			std::string symbol = tree.children.front().getSymbolValue();
			if (symbol == "if" || symbol == "define" || symbol == "begin") {
				throw InterpreterSemanticError("Error: attempted redefinition of special form");
			}
			if (symbol == "pi") {
				throw InterpreterSemanticError("Error: attempted redefinition of pi");
			}
			Expression exp(evaluate(tree.children.back()));
			defaultEnviron.symbolMap.insert(std::pair<std::string, Expression>(symbol, exp));
			return exp;
		}
		else if (token == "begin")
		{
			Expression ret;
			for (unsigned int i = 0; i < tree.children.size(); ++i)
			{
				if (i == tree.children.size() - 1) {
					ret = evaluate(tree.children[i]);
				}
				else
					evaluate(tree.children[i]);
			}
			return ret;
		}
		else if (token == "if")
		{
			bool b;
			Expression exp;
			exp = evaluate(tree.children[0]);
			b = exp.getBoolValue();
			if (b) {
				return evaluate(tree.children[1]);
			}
			else {
				return evaluate(tree.children[2]);
			}
		}
		else
		{
			std::vector<Expression> evalArgs;
			for (unsigned int i = 0; i < tree.children.size(); ++i)
			{
				Expression exp = evaluate(tree.children[i]);
				evalArgs.push_back(exp);
			}
			Expression temp(token);
			temp.children = evalArgs;
			if (temp.children.size() == 0) {
				throw InterpreterSemanticError("Error: unknown symbol");
			}
			return defaultEnviron.procedureMap[token](temp);

		}
	}
	else
		return tree;
}