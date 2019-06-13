#ifndef __LIST_PARSER_H__
#define __LIST_PARSER_H__
#include "parser.h"
#include "list_lexer.h"

class ListParser : public Parser {
public:
	ListParser(ListLexer *lexer, int k);
	virtual ~ListParser();

	virtual void Parse();

private:
	void List();
	void Element();
	void Elements();


};
#endif//__LIST_PARSER_H__
