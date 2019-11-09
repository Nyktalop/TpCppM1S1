#include "Token.hpp"

//~~~~~~~~~~~~~~~~~~~~ExprToken~~~~~~~~~~~~~~~~~~~~~~~~
ExprToken::ExprToken(TokenType type) : _type{type} {};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~ExprTokenNumber~~~~~~~~~~~~~~~~~~~~~
ExprTokenNumber::ExprTokenNumber(double i) : ExprToken{NUMBER}, _number{i} {}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~ExprTokenChar~~~~~~~~~~~~~~~~~~~~~~~
ExprTokenChar::ExprTokenChar(char c) : ExprToken{CHAR}, _char{c} {}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~