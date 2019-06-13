#ifndef __LIST_LEXER_H__
#define __LIST_LEXER_H__
#include "lexer.h"

#define TOKEN_NAME			2
#define TOKEN_NUMBER		3
#define TOKEN_LSBRACK		4
#define TOKEN_RSBRACK		5
#define	TOKEN_COMMA			6
#define	TOKEN_EQUAL			7



class ListLexer : public Lexer {
public:
	ListLexer(const char *s);
	virtual ~ListLexer();

	virtual Token GetNextToken();
	virtual const char *GetTokenName(int token_type);

private:

	static const char *token_name[];

	Token Number();
	Token Name();
};
#endif//__LIST_LEXER_H__
