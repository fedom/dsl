#ifndef __LIST_PARSER_H__
#define __LIST_PARSER_H__
#include "parser.h"
#include "list_lexer.h"
#include <map>

									
			

class ListParser : public Parser {
public:
	ListParser(ListLexer *lexer);
	virtual ~ListParser();

	virtual void Parse();

private:
	void Stat();
	void Assign();
	void List();
	void _List();
	void Element();
	void Elements();
	bool SpeculateStatAlt1();
	bool SpeculateStatAlt2();

	std::map<int, int> list_speculate_cache_;

};
#endif//__LIST_PARSER_H__
