#include "tokenize.hpp"

bool checkValidList(std::deque<std::string> list)
{
	int numOpenParen = std::count(std::begin(list), std::end(list), "(");
	int numClosedParen = std::count(std::begin(list), std::end(list), ")");
	if (numOpenParen != numClosedParen || numOpenParen == 0) {
		return false;
	}
	if (list.size() == 2) {
		return false;
	}
	for (size_t i = 0; i < list.size(); ++i)
	{
		std::string temp = list[i];
		char frontChar = temp.front();
		char backChar = temp.back();
		if (isdigit(frontChar) && !isdigit(backChar)) {
			return false;
		}
	}
	return true;
}

Tokenize::Tokenize()
{
	
	
}

bool Tokenize::parse(std::istream & stream)
{
	listOfTokens.erase(listOfTokens.begin(), listOfTokens.end());
	
	std::string token;

	stream >> token;
	while (!stream.fail())
	{
		if (token[0] == ';'){
			token.erase(0, token.length());
			stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (token[0] == '(')
		{
			listOfTokens.push_back("(");
			token.erase(0, 1);
		}
		if (!token.empty())
		{
			if (token[token.length() - 1] == ')')
			{
				int loc = token.find_first_of(')');
				std::string sub = token.substr(0, loc);
				if (!sub.empty())
					listOfTokens.push_back(sub);
				token.erase(0, loc);
				for (unsigned int i = 0; i < token.size(); i++) {
					listOfTokens.push_back(")");
				}
			}
			else
			{
				listOfTokens.push_back(token);
			}
		}
		stream >> token;
	}
	return checkValidList(listOfTokens);
}

Expression Tokenize::createTree(std::deque<std::string>& list)
{
	Expression localTree;
	if (list.size() == 0) {
		std::exit(EXIT_FAILURE);
	}
	std::string temp;
	temp = list.front();
	list.pop_front();

	if (temp == "(")
	{
		localTree = createAtom(list.front());
		list.pop_front();
		while (list.front() != ")")
			localTree.insert(createTree(list));
		list.pop_front();
		return localTree;
	}
	else if (temp == ")")
	{
		std::exit(EXIT_FAILURE);
	}
	else
	{
		Expression leaf = createAtom(temp);
		return leaf;
	}
	
}

bool Tokenize::buildAST()
{
	syntaxTree = createTree(listOfTokens);
	return(listOfTokens.empty());
}

Expression Tokenize::createAtom(std::string token)
{
	if (token.empty())
	{
		Expression empty;
		return empty;
	}

	int frontChar = token.front();
	int secChar = token[1];
	if (token == "True" || token == "False" || token == "true" || token == "false" || token == "TRUE" || token == "FALSE") 
	{
		bool b;
		b = (token == "True" || token == "true" || token == "TRUE");

		Expression atom(b);
		atom.originalToken = token;
		return atom;
	}
	bool frontCharDigit = (isdigit(frontChar) != 0);
	bool secCharDigit = (isdigit(secChar) != 0);
	if (frontCharDigit || secCharDigit)
	{
		double d = std::stod(token);
		Expression atom(d);
		atom.originalToken = token;
		return d;
	}
	Expression atom(token);
	atom.originalToken = token;
	return atom;

}
Expression Tokenize::getSyntaxTree()
{
	return syntaxTree;
}

std::deque<std::string> Tokenize::getTokenList()
{
	return listOfTokens;
}
