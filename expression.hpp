#ifndef EXPRESSION_HPP_
#define EXPRESSION_HPP_

#include <string>
#include <vector>

enum lispType { None, Boolean, Number, Symbol };

class Expression
{
private:
	
	lispType type;

	
	struct S
	{
		bool bVal;
		double dVal;
		std::string sVal;
	} s;
	
public:
	std::string originalToken;
	std::vector<Expression> children;
	inline void insert(Expression x)
	{
		children.push_back(x);
	}

	//Default construction of an Expression of type None
	Expression();
	
	//Construct an Expression with a single Boolean atom with value
	Expression(bool value);
	
	//Construct an Expression with a single Number atom with value
	Expression(double value);
	
	//Construct an Expression with a single Symbol atom with value
	Expression(const std::string value);
	
	//Equality operator for two Expressions, two expressions are equal if they have the same
	//type, atom value, and number of arguments
	bool operator==(const Expression  & exp) const noexcept;

	lispType getType() const;

	bool getBoolValue() const;

	double getDoubleValue() const;

	std::string getSymbolValue() const;

	int getNumArgs() const;

	
};	



#endif