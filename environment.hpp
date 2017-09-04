#ifndef ENVIRONMENT_HPP_
#define ENVIRONMENT_HPP_

#include "tokenize.hpp"
#include "expression.hpp"
#include "interpreter_semantic_error.hpp"

#include <string>
#include <unordered_map>
#include <cmath>

typedef Expression(*functPtr)(Expression);

Expression notFunct(Expression exp);

Expression andFunct(Expression exp);

Expression orFunct(Expression exp);

Expression lessThanFunct(Expression exp);

Expression lessThanEqFunct(Expression exp);

Expression greatThanFunct(Expression exp);

Expression greatThanEqFunct(Expression exp);

Expression eqFunct(Expression exp);

Expression plusFunct(Expression exp);

Expression minusFunct(Expression exp);

Expression timesFunct(Expression exp);

Expression divideFunct(Expression exp);



class Environment
{
private:


	functPtr logicNot = notFunct;
	functPtr logicAnd = andFunct;
	functPtr logicOr = orFunct;
	functPtr lessThan = lessThanFunct;
	functPtr lessThanEq = lessThanEqFunct;
	functPtr greatThan = greatThanFunct;
	functPtr greatThanEq = greatThanEqFunct;
	functPtr eq = eqFunct;
	functPtr plus = plusFunct;
	functPtr minus = minusFunct;
	functPtr times = timesFunct;
	functPtr divide = divideFunct;

public:	
	//Default construct an Environment
	Environment();
	

	std::unordered_map<std::string, functPtr> procedureMap;
	std::unordered_map<std::string, Expression> symbolMap;
	
		
	
};



#endif