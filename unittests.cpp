#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "tokenize.hpp"
#include "expression.hpp"
#include "environment.hpp"
#include "interpreter.hpp"

#include <string>
#include <deque>
#include <cmath>

TEST_CASE( "Test tokenizer parse with expected input", "[tokenizer]" ) {
	
  std::string program = "(begin (define r 10) (* pi (* r r)))";

  std::istringstream iss(program);
 
  Tokenize tokenizer1;
  
  tokenizer1.parse(iss);
  std::deque<std::string> tokenList = tokenizer1.getTokenList();

  REQUIRE(tokenList.size() == 17);
  REQUIRE(tokenList[0] == "(");
  REQUIRE(tokenList[1] == "begin");
  REQUIRE(tokenList[2] == "(");
  REQUIRE(tokenList[3] == "define");
  REQUIRE(tokenList[4] == "r");
  REQUIRE(tokenList[5] == "10");
  REQUIRE(tokenList[6] == ")");
  REQUIRE(tokenList[7] == "(");
  REQUIRE(tokenList[8] == "*");
  REQUIRE(tokenList[9] == "pi");
  REQUIRE(tokenList[10] == "(");
  REQUIRE(tokenList[11] == "*");
  REQUIRE(tokenList[12] == "r");
  REQUIRE(tokenList[13] == "r");
  REQUIRE(tokenList[14] == ")");
  REQUIRE(tokenList[15] == ")");
  REQUIRE(tokenList[16] == ")");
  
}

TEST_CASE( "Test tokenizer buildAST with expected input", "[tokenizer]" ) {
	
  std::string program = "(begin (define r 10) (* pi (* r r)))";

  std::istringstream iss(program);
 
  Tokenize tokenizer1;
  
  tokenizer1.parse(iss);
  
  tokenizer1.buildAST();
  Expression tree;
  tree = tokenizer1.getSyntaxTree();
  
  
  REQUIRE(tree.getSymbolValue() == "begin");
  REQUIRE(tree.getNumArgs() == 2);

  REQUIRE(tree.children.front().getSymbolValue() == "define");
  REQUIRE(tree.children.front().getNumArgs() == 2);

  REQUIRE(tree.children.front().children.front().getSymbolValue() == "r");
  REQUIRE(tree.children.front().children.front().getNumArgs() == 0);

  REQUIRE(tree.children.front().children.back().getDoubleValue() == 10);
  REQUIRE(tree.children.front().children.back().getNumArgs() == 0);

  REQUIRE(tree.children.back().getSymbolValue() == "*");
  REQUIRE(tree.children.back().getNumArgs() == 2);

  REQUIRE(tree.children.back().children[0].getSymbolValue() == "pi");
  REQUIRE(tree.children.back().children[0].getNumArgs() == 0);

  REQUIRE(tree.children.back().children[1].getSymbolValue() == "*");
  REQUIRE(tree.children.back().children[1].getNumArgs() == 2);

  REQUIRE(tree.children.back().children[1].children.front().getSymbolValue() == "r");
  REQUIRE(tree.children.back().children[1].children.front().getNumArgs() == 0);

  REQUIRE(tree.children.back().children[1].children.back().getSymbolValue() == "r");
  REQUIRE(tree.children.back().children[1].children.back().getNumArgs() == 0);
 
}

TEST_CASE( "Test expression", "[expression]" ) {
	
  std::string str = "test";
  Expression exp0(str);
  REQUIRE(exp0.getSymbolValue() == str);
  
  double d0 = 10.0;
  Expression exp1(d0);
  REQUIRE(exp1.getDoubleValue() == 10.0);
  
  double d1 = 10;
  Expression exp2(d1);
  REQUIRE(exp2.getDoubleValue() == 10);

  
  bool b1 = false;
  Expression exp3(b1);
  REQUIRE(!exp3.getBoolValue());
  
}

TEST_CASE("Test environment NOT", "[environment]") {

	std::string program = "(not True)";
	std::istringstream iss(program);

	Interpreter interp;
	interp.parse(iss);
	Expression exp;
	exp = interp.eval();
	REQUIRE(!exp.getBoolValue());
}

TEST_CASE("Test environment AND", "[environment]") {

	std::string program0 = "(and True True)";
	std::istringstream iss0(program0);
	Interpreter interp0;
	interp0.parse(iss0);
	Expression exp0;
	exp0 = interp0.eval();
	REQUIRE(exp0.getType() == Boolean);
	REQUIRE(exp0.getBoolValue() );

	std::string program1 = "(and True False)";
	std::istringstream iss1(program1);
	Interpreter interp1;
	interp1.parse(iss1);
	Expression exp1;
	exp1 = interp1.eval();
	REQUIRE(exp1.getType() == Boolean);
	REQUIRE(!exp1.getBoolValue());
}

TEST_CASE("Test environment OR", "[environment]") {

	std::string program0 = "(or True False)";
	std::istringstream iss0(program0);
	Interpreter interp0;
	interp0.parse(iss0);
	Expression exp0;
	exp0 = interp0.eval();
	REQUIRE(exp0.getType() == Boolean);
	REQUIRE(exp0.getBoolValue() );

	std::string program1 = "(or False False)";
	std::istringstream iss1(program1);
	Interpreter interp1;
	interp1.parse(iss1);
	Expression exp1;
	exp1 = interp1.eval();
	REQUIRE(exp1.getType() == Boolean);
	REQUIRE(!exp1.getBoolValue());
}

TEST_CASE("Test environment <", "[environment]") {

	std::string program0 = "(< (+ 1 3) (+ 1 (+ 2 2)))";
	std::istringstream iss0(program0);
	Interpreter interp0;
	interp0.parse(iss0);
	Expression exp0;
	exp0 = interp0.eval();
	REQUIRE(exp0.getType() == Boolean);
	REQUIRE(exp0.getBoolValue() );

	std::string program1 = "(< 5 4)";
	std::istringstream iss1(program1);
	Interpreter interp1;
	interp1.parse(iss1);
	Expression exp1;
	exp1 = interp1.eval();
	REQUIRE(exp1.getType() == Boolean);
	REQUIRE(!exp1.getBoolValue());
}

TEST_CASE("Test environment <=", "[environment]") {

	std::string program0 = "(<= 4 5)";
	std::istringstream iss0(program0);
	Interpreter interp0;
	interp0.parse(iss0);
	Expression exp0;
	exp0 = interp0.eval();
	REQUIRE(exp0.getType() == Boolean);
	REQUIRE(exp0.getBoolValue() );

	std::string program1 = "(<= 5 5)";
	std::istringstream iss1(program1);
	Interpreter interp1;
	interp1.parse(iss1);
	Expression exp1;
	exp1 = interp1.eval();
	REQUIRE(exp1.getType() == Boolean);
	REQUIRE(exp1.getBoolValue() );

	std::string program2 = "(<= 5 4)";
	std::istringstream iss2(program2);
	Interpreter interp2;
	interp2.parse(iss2);
	Expression exp2;
	exp2 = interp2.eval();
	REQUIRE(exp2.getType() == Boolean);
	REQUIRE(!exp2.getBoolValue());
}

TEST_CASE("Test environment >", "[environment]") {

	std::string program0 = "(> 5 4)";
	std::istringstream iss0(program0);
	Interpreter interp0;
	interp0.parse(iss0);
	Expression exp0;
	exp0 = interp0.eval();
	REQUIRE(exp0.getType() == Boolean);
	REQUIRE(exp0.getBoolValue() );

	std::string program1 = "(> 5 5)";
	std::istringstream iss1(program1);
	Interpreter interp1;
	interp1.parse(iss1);
	Expression exp1;
	exp1 = interp1.eval();
	REQUIRE(exp1.getType() == Boolean);
	REQUIRE(!exp1.getBoolValue());

	std::string program2 = "(> 4 5)";
	std::istringstream iss2(program2);
	Interpreter interp2;
	interp2.parse(iss2);
	Expression exp2;
	exp2 = interp2.eval();
	REQUIRE(exp2.getType() == Boolean);
	REQUIRE(!exp2.getBoolValue());
}

TEST_CASE("Test environment >=", "[environment]") {

	std::string program0 = "(>= 5 4)";
	std::istringstream iss0(program0);
	Interpreter interp0;
	interp0.parse(iss0);
	Expression exp0;
	exp0 = interp0.eval();
	REQUIRE(exp0.getType() == Boolean);
	REQUIRE(exp0.getBoolValue() );

	std::string program1 = "(>= 5 5)";
	std::istringstream iss1(program1);
	Interpreter interp1;
	interp1.parse(iss1);
	Expression exp1;
	exp1 = interp1.eval();
	REQUIRE(exp1.getType() == Boolean);
	REQUIRE(exp1.getBoolValue() );

	std::string program2 = "(>= 4 5)";
	std::istringstream iss2(program2);
	Interpreter interp2;
	interp2.parse(iss2);
	Expression exp2;
	exp2 = interp2.eval();
	REQUIRE(exp2.getType() == Boolean);
	REQUIRE(!exp2.getBoolValue());
}

TEST_CASE("Test environment =", "[environment]") {

	std::string program0 = "(= (+ 1 2) 3)";
	std::istringstream iss0(program0);
	Interpreter interp0;
	interp0.parse(iss0);
	Expression exp0;
	exp0 = interp0.eval();
	REQUIRE(exp0.getType() == Boolean);
	REQUIRE(exp0.getBoolValue() );

	std::string program1 = "(= 5 5)";
	std::istringstream iss1(program1);
	Interpreter interp1;
	interp1.parse(iss1);
	Expression exp1;
	exp1 = interp1.eval();
	REQUIRE(exp1.getType() == Boolean);
	REQUIRE(exp1.getBoolValue() );

	std::string program2 = "(= -5 5)";
	std::istringstream iss2(program2);
	Interpreter interp2;
	interp2.parse(iss2);
	Expression exp2;
	exp2 = interp2.eval();
	REQUIRE(exp2.getType() == Boolean);
	REQUIRE(!exp2.getBoolValue());
}

TEST_CASE("Test environment +", "[environment]") {

	std::string program0 = "(+ (+ 1 3) (+ 1 (+ 2 2)))";
	std::istringstream iss0(program0);
	Interpreter interp0;
	interp0.parse(iss0);
	Expression exp0;
	exp0 = interp0.eval();
	REQUIRE(exp0.getType() == Number);
	REQUIRE(exp0.getDoubleValue() == 9);
	
	std::string program1 = "(+ 5 5)";
	std::istringstream iss1(program1);
	Interpreter interp1;
	interp1.parse(iss1);
	Expression exp1;
	exp1 = interp1.eval();
	REQUIRE(exp1.getType() == Number);
	REQUIRE(exp1.getDoubleValue() == 10);
	
	std::string program2 = "(+ 1.0 4.0)";
	std::istringstream iss2(program2);
	Interpreter interp2;
	interp2.parse(iss2);
	Expression exp2;
	exp2 = interp2.eval();
	REQUIRE(exp2.getType() == Number);
	REQUIRE(exp2.getDoubleValue() == 5.0);

	std::string program3 = "(+ 1e-4 0 0)";
	std::istringstream iss3(program3);
	Interpreter interp3;
	interp3.parse(iss3);
	Expression exp3;
	exp3 = interp3.eval();
	REQUIRE(exp3.getType() == Number);
	REQUIRE(exp3.getDoubleValue() == 1e-4);
	
	std::string program4 = "(+ -1.0 0.0)";
	std::istringstream iss4(program4);
	Interpreter interp4;
	interp4.parse(iss4);
	Expression exp4;
	exp4 = interp4.eval();
	REQUIRE(exp4.getType() == Number);
	REQUIRE(fabs(exp4.getDoubleValue() + 1.0) < 0.0001);
	
	std::string program5 = "(+ 1 (+ 1 2))";
	std::istringstream iss5(program5);
	Interpreter interp5;
	interp5.parse(iss5);
	Expression exp5;
	exp5 = interp5.eval();
	REQUIRE(exp5.getType() == Number);
	REQUIRE(exp5.getDoubleValue() == 4);
}

TEST_CASE("Test environment -", "[environment]") {

	std::string program0 = "(- 5)";
	std::istringstream iss0(program0);
	Interpreter interp0;
	interp0.parse(iss0);
	Expression exp0;
	exp0 = interp0.eval();
	REQUIRE(exp0.getType() == Number);
	REQUIRE(fabs(exp0.getDoubleValue() + 5) < 0.00001);
	
	std::string program1 = "(- 5 5)";
	std::istringstream iss1(program1);
	Interpreter interp1;
	interp1.parse(iss1);
	Expression exp1;
	exp1 = interp1.eval();
	REQUIRE(exp1.getType() == Number);
	REQUIRE(fabs(exp1.getDoubleValue()) < 0.00001);
	
	std::string program2 = "(- 1.0 4.0)";
	std::istringstream iss2(program2);
	Interpreter interp2;
	interp2.parse(iss2);
	Expression exp2;
	exp2 = interp2.eval();
	REQUIRE(exp2.getType() == Number);
	REQUIRE(fabs(exp2.getDoubleValue() + 3) < 0.00001);

	std::string program3 = "(- 1e-4)";
	std::istringstream iss3(program3);
	Interpreter interp3;
	interp3.parse(iss3);
	Expression exp3;
	exp3 = interp3.eval();
	REQUIRE(exp3.getType() == Number);
	REQUIRE(fabs(exp3.getDoubleValue() + 1e-4) < 1e-8);

	std::string program4 = "(- 5 3)";
	std::istringstream iss4(program4);
	Interpreter interp4;
	interp4.parse(iss4);
	Expression exp4;
	exp4 = interp4.eval();
	REQUIRE(exp4.getType() == Number);
	REQUIRE(fabs(exp4.getDoubleValue() - 2) < 0.00001);
}

TEST_CASE("Test environment *", "[environment]") {

	std::string program0 = "(* 5 1)";
	std::istringstream iss0(program0);
	Interpreter interp0;
	interp0.parse(iss0);
	Expression exp0;
	exp0 = interp0.eval();
	REQUIRE(exp0.getType() == Number);
	REQUIRE(exp0.getDoubleValue() == 5);

	std::string program1 = "(* 5 5)";
	std::istringstream iss1(program1);
	Interpreter interp1;
	interp1.parse(iss1);
	Expression exp1;
	exp1 = interp1.eval();
	REQUIRE(exp1.getType() == Number);
	REQUIRE(exp1.getDoubleValue() == 25);

	std::string program2 = "(* 1.0 4.0)";
	std::istringstream iss2(program2);
	Interpreter interp2;
	interp2.parse(iss2);
	Expression exp2;
	exp2 = interp2.eval();
	REQUIRE(exp2.getType() == Number);
	REQUIRE(exp2.getDoubleValue() == 4.0);

	std::string program3 = "(* 1e-4 1 2)";
	std::istringstream iss3(program3);
	Interpreter interp3;
	interp3.parse(iss3);
	Expression exp3;
	exp3 = interp3.eval();
	REQUIRE(exp3.getType() == Number);
	REQUIRE(exp3.getDoubleValue() == 2e-4);

	std::string program4 = "(* 5 3)";
	std::istringstream iss4(program4);
	Interpreter interp4;
	interp4.parse(iss4);
	Expression exp4;
	exp4 = interp4.eval();
	REQUIRE(exp4.getType() == Number);
	REQUIRE(exp4.getDoubleValue() == 15);
}

TEST_CASE("Test environment /", "[environment]") {

	std::string program0 = "(/ 5 1)";
	std::istringstream iss0(program0);
	Interpreter interp0;
	interp0.parse(iss0);
	Expression exp0;
	exp0 = interp0.eval();
	REQUIRE(exp0.getType() == Number);
	REQUIRE(exp0.getDoubleValue() == 5);

	std::string program1 = "(/ 5 5)";
	std::istringstream iss1(program1);
	Interpreter interp1;
	interp1.parse(iss1);
	Expression exp1;
	exp1 = interp1.eval();
	REQUIRE(exp1.getType() == Number);
	REQUIRE(exp1.getDoubleValue() == 1);

	std::string program2 = "(/ 1.0 4.0)";
	std::istringstream iss2(program2);
	Interpreter interp2;
	interp2.parse(iss2);
	Expression exp2;
	exp2 = interp2.eval();
	REQUIRE(exp2.getType() == Number);
	REQUIRE(exp2.getDoubleValue() == 0.25);

	std::string program3 = "(/ -5 10)";
	std::istringstream iss3(program3);
	Interpreter interp3;
	interp3.parse(iss3);
	Expression exp3;
	exp3 = interp3.eval();
	REQUIRE(exp3.getType() == Number);
	REQUIRE(fabs(exp3.getDoubleValue() + 0.5) < 0.000001);
}

TEST_CASE("Test environment define", "[environment]") {

	std::string program0 = "(define a 1)";
	std::istringstream iss0(program0);
	Interpreter interp0;
	interp0.parse(iss0);
	Expression exp0;
	exp0 = interp0.eval();
	REQUIRE(exp0.getType() == Number);
	REQUIRE(exp0.getDoubleValue() == 1);

	std::string program1 = "(+ a 2)";
	std::istringstream iss1(program1);
	interp0.parse(iss1);
	Expression exp1;
	exp1 = interp0.eval();
	REQUIRE(exp1.getType() == Number);
	REQUIRE(exp1.getDoubleValue() == 3);
}