#include "expression.hpp"

Expression::Expression()
{
	type = None;
	
}

Expression::Expression(bool value) 
{
	type = Boolean;
	s.bVal = value;

}

Expression::Expression(double value) 
{
	type = Number;
	s.dVal = value;
}

Expression::Expression(const std::string value)
{
	type = Symbol;
	s.sVal = value;
}

bool Expression::operator==(const Expression & exp) const noexcept
{
	if (this->type != exp.type) {
		return false;
	}

	if (this->getNumArgs() != exp.getNumArgs()) {
		return false;
	}

	if (type == Boolean){
		return(s.bVal == exp.s.bVal);
	}
	else if (type == Number){
		return(s.dVal == exp.s.dVal);
	}
	else if (type == Symbol){
		return(s.sVal == exp.s.sVal);
	}
	return true;
}


lispType Expression::getType() const
{
	return type;
}

bool Expression::getBoolValue() const
{
	return s.bVal;
}

double Expression::getDoubleValue() const
{
	return s.dVal;
}

std::string Expression::getSymbolValue() const
{
	return s.sVal;
}

int Expression::getNumArgs() const
{
	return children.size();
}