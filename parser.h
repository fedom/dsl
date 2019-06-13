#ifndef __PARSER_H__
#define __PARSER_H__
#include "lexer.h"

class Parser {
public:
	Parser(Lexer *lexer, int k);
	virtual ~Parser();

	virtual void Parse() = 0;

	Token LA(int i);
	int LT(int i);


protected:
	void Match(int token_type);

	Lexer *lexer_;
	Token *ct_;
	int size_;
	int i_;
};
#endif//__PARSER_H__
