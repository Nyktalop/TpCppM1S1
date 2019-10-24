#include "Token.hpp"

//~~~~~~~~~~~~~~~~~~~~ExprToken~~~~~~~~~~~~~~~~~~~~~~~~
ExprToken::ExprToken(TokenType type) : _type{type} {};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~ExprTokenNumber~~~~~~~~~~~~~~~~~~~~~
ExprTokenNumber::ExprTokenNumber(double i) : ExprToken{NUMBER}, _number{i} {}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~ExprTokenOp~~~~~~~~~~~~~~~~~~~~~~~
ExprTokenOp::ExprTokenOp(char c) : ExprToken{OP}, _op{c} {}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~