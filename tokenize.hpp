#ifndef TOKENIZE_HPP_
#define TOKENIZE_HPP_

#include "expression.hpp"

#include <string>
#include <istream>
#include <deque>
#include <queue>
#include <cstddef>
#include <typeinfo>
#include <algorithm>


bool checkValidList(std::deque<std::string> list);

class Tokenize
{
private:

	Expression syntaxTree;


	std::deque<std::string> listOfTokens;

	Expression createTree(std::deque<std::string>& list);

	//may throw std::invalid_argument
	Expression createAtom(std::string token);

	//void setNumArgsInTree(AST& tree);
	

public:
	//construct a tokenizer
	Tokenize();
	
	bool parse(std::istream  & stream); //creates token list

	bool buildAST();

	Expression getSyntaxTree();
	std::deque<std::string> getTokenList();
	
	
	
};





#endif