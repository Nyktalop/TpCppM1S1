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

  // double& number
  const double number() const {return 0;}
  // char& op
  const char op() const {return 'o';}
};

class ExprTokenNumber : public ExprToken {
private :
  double _number;
public :
  const double  number() const {return _number;}

  ExprTokenNumber(const double& i) : ExprToken{NUMBER}, _number{i} {
  }
  
};

class ExprTokenOp : public ExprToken {
private :
  char _op;
  
public :
  const char  op() const {return _op;}
  
  ExprTokenOp(const char& c) : ExprToken{OP}, _op{c} {
  }

  bool operator<(const ExprToken& t) {
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

std::vector<std::shared_ptr<ExprToken>> toRPN (std::vector<std::string> vec);
std::vector<std::string> split (const std::string& s, const char delim);
bool isNumber(std::string s);
bool isOp(std::string s);


class Expr {
public:

  Expr(const char* str) : s{str} {};

  int eval() {
    std::vector<std::shared_ptr<ExprToken>> tokens = toRPN(split(s, ' '));
    std::stack<std::shared_ptr<ExprTokenNumber>> stack;

    for(auto t : tokens) {
      if(t->type()==NUMBER) {
	stack.push(std::make_shared<ExprTokenNumber>(t->number())); // TODO ICI
      } else if (t->type()==OP) {
	std::shared_ptr<ExprTokenNumber> b = std::static_pointer_cast<ExprTokenNumber>(stack.top());
	stack.pop();
	std::shared_ptr<ExprTokenNumber> a = std::static_pointer_cast<ExprTokenNumber>(stack.top());
	stack.pop();

	std::cout << b->number() << a->number() << std::endl;
	
	std::shared_ptr<ExprTokenOp> t2 = std::static_pointer_cast<ExprTokenOp>(t);
	
	switch(t2->op()) {
	case '+' :
	  stack.push(std::make_shared<ExprTokenNumber>(a->number()+b->number()));
	  break;

	case '-' :
	  stack.push(std::make_shared<ExprTokenNumber>(a->number()-b->number()));
	  break;

	case '*' :
	  stack.push(std::make_shared<ExprTokenNumber>(a->number()*b->number()));
	  break;

	case '/' :
	  stack.push(std::make_shared<ExprTokenNumber>(a->number()/b->number()));
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
    //std::cout << toRPN(split(s, ' ')) << std::endl;
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

std::vector<std::shared_ptr<ExprToken>> toRPN (std::vector<std::string> vec) {
  std::vector<std::shared_ptr<ExprToken>> res;
  std::stack<std::shared_ptr<ExprToken>> stack;
  
  for(const auto& t : vec) {
    if(isNumber(t)) {
      res.push_back(std::make_shared<ExprTokenNumber>(stod(t)));

    } else if (isOp(t)) {
      std::shared_ptr<ExprTokenOp> token = std::make_shared<ExprTokenOp>(t[0]);
      while(!stack.empty() && *token < *stack.top()) {
	res.push_back(stack.top());
	stack.pop();
      }
      stack.push(token);
      
    } else {
      std::cerr << "not a valid expression" << std::endl;
      exit(255);
    }
  }

  while(!stack.empty()) {
    res.push_back(stack.top());
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
  
  return 0;
}
