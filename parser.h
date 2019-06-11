#ifndef __PARSER_H__
#define __PARSER_H__
#include "lexer.h"

class Parser {
public:
	Parser(Lexer *lexer);
	virtual ~Parser();

	virtual void Parse() = 0;

protected:
	void Match(int token_type);

	Lexer *lexer_;
	Token ct_;
};
#endif//__PARSER_H__
