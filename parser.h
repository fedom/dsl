#ifndef __PARSER_H__
#define __PARSER_H__
#include "lexer.h"
#include <stack>
#include <vector>

class Parser {
public:
	Parser(Lexer *lexer);
	virtual ~Parser();

	virtual void Parse() = 0;


protected:
	Token LA(int i);
	int LT(int i);

	void MarkBase();
	void RestoreBase();
	
	void Match(int token_type);
	void Consume();
	void Sync(int i);
	bool IsSpeculating();

	Lexer *lexer_;
	std::vector<Token> lookahead_tokens_;
	std::stack<int> base_i_;
	
	int i_;
};
#endif//__PARSER_H__
