#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <memory>

enum TokenType {
  NONE,
  NUMBER,
  OP
};


class ExprToken {
private:
  TokenType _type;

public:
  ExprToken(TokenType type=NONE) : _type{type} {};

  const TokenType type() const {return _type;}
  
  bool operator<(const ExprToken& t) {
    return false;
  }
  
  const virtual double number() = 0;

  const virtual char op() = 0;
};

using vecToken = std::vector<std::unique_ptr<ExprToken>>; 

class ExprTokenNumber : public ExprToken {
private :
  double _number;
public :
  const double number() override {return _number;}

  const char op() override {return 'o';}
  
  ExprTokenNumber(const double i) : ExprToken{NUMBER}, _number{i} {
  }
  
};

class ExprTokenOp : public ExprToken {
private :
  char _op;
  
public :
  const char op() override {return _op;}

  const double number() override {return 0;}
  
  ExprTokenOp(const char c) : ExprToken{OP}, _op{c} {
  }

  bool operator<(ExprToken& t) {
    if(t.type() != OP)
      return false;

    return (_op == '+' || _op == '-') && ( t.op() == '*' || t.op() == '/');
  }
};

/*
std::ostream& operator<<(std::ostream& out, const ExprToken& t) {
  if(t.type() == NUMBER) {
    out << static_cast<ExprTokenNumber>(t).number;
  }
  else if (t.type() == OP) {
    out << static_cast<ExprTokenOp>(t).op;
  }
  else {
    out << "None";
  }
  return out;
}
*/

vecToken toRPN (std::vector<std::string> vec);
std::vector<std::string> split (const std::string& s, const char delim);
bool isNumber(std::string s);
bool isOp(std::string s);


class Expr {
public:

  Expr(const char* str) : s{str} {};

  int eval() {
    vecToken tokens = toRPN(split(s, ' '));
    std::stack<std::unique_ptr<ExprToken>> stack;

    for(auto& t : tokens) {
      if(t->type()==NUMBER) {
	stack.push(std::move(t)); // TODO ICI
      } else if (t->type()==OP) {
	std::unique_ptr<ExprToken> b = std::move(stack.top());
	stack.pop();
	std::unique_ptr<ExprToken> a = std::move(stack.top());
	stack.pop();
	
	switch(t->op()) {
	case '+' :
	  stack.push(std::make_unique<ExprTokenNumber>(a->number()+b->number()));
	  break;

	case '-' :
	  stack.push(std::make_unique<ExprTokenNumber>(a->number()-b->number()));
	  break;

	case '*' :
	  stack.push(std::make_unique<ExprTokenNumber>(a->number()*b->number()));
	  break;

	case '/' :
	  stack.push(std::make_unique<ExprTokenNumber>(a->number()/b->number()));
	  break;
	  
	default :
	  std::cerr << "??? : " << t->op() << std::endl;
	  exit(255);
	  break;
	}
      }
    }
    return stack.top()->number();
  }
    
  void print() {
    for(auto& t : toRPN(split(s, ' ')) ) {
      if (t->type()==OP) {
	std::cout << t->op();
      } else if (t->type()==NUMBER) {
	std::cout << t->number();
      } else if (t->type()==NONE) {
	std::cout << "NONE";
      }
      std::cout << " ";
    }
    std::cout << std::endl;
  }

private:

  std::string s;
  
};

bool isOp(std::string s) {
  return s.length() == 1 && ( !s.compare("+") ||
			      !s.compare("-") ||
			      !s.compare("*") ||
			      !s.compare("/") );
}

bool isNumber(std::string s) {
  std::string::const_iterator it = s.begin();

  while( it != s.end() && std::isdigit(*it))
    ++it;

  return !s.empty() && it == s.end();
}

vecToken toRPN (std::vector<std::string> vec) {
  vecToken res;
  std::stack<std::unique_ptr<ExprToken>> stack;
  
  for(const auto& t : vec) {
    if(isNumber(t)) {
      res.push_back(std::make_unique<ExprTokenNumber>(stod(t)));

    } else if (isOp(t)) {
      std::unique_ptr<ExprTokenOp> token = std::make_unique<ExprTokenOp>(t[0]);
      while(!stack.empty() && *token < *stack.top()) {
	res.push_back(std::move(stack.top()));
	stack.pop();
      }
      stack.push(std::move(token));
      
    } else {
      std::cerr << "not a valid expression" << std::endl;
      exit(255);
    }
  }

  while(!stack.empty()) {
    res.push_back(std::move(stack.top()));
    stack.pop();
  }
  
  return res;
}



std::vector<std::string> split (const std::string& s, const char delim) {
  std::stringstream stream = std::stringstream(s);
  std::string token;
  std::vector<std::string> vector;
    
  while(std::getline(stream,token,delim)) {
    vector.push_back(token);
    //std::cout << token << std::endl;
  }
  
  return vector;
}

  
int main() {

  Expr exp = Expr("17 - 24 / 4 * 3 + 2");
  
  exp.print();

  std::cout << exp.eval() << std::endl;
  
  exp = Expr("1 + 1 + 1 - 1 * 2");

  exp.print();
  
  std::cout << exp.eval() << std::endl;

  
  return 0;
}
