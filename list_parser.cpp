#include "list_parser.h"
#include "list_lexer.h"
#include "my_except.h"

ListParser::ListParser(ListLexer *lexer, int k) : Parser(lexer, k) {
	
}

ListParser::~ListParser() {

}

void ListParser::Parse() {

	try {
		List();
	} catch (const ParserUnwantedTokenException &e) {
		printf("Parse token error: %s\n", e.what());
	} catch (const InvalidCharException &e) {
		printf("InvalidCharException error: %s\n", e.what());
	}
}


void ListParser::List() {
	if (LT(1) == TOKEN_EOF)
		return;

	Match(TOKEN_LSBRACK);
	Elements();
	Match(TOKEN_RSBRACK);
}

void ListParser::Elements() {
	// empty list
	if (LT(1) == TOKEN_RSBRACK)
		return;

	Element();
	while (LT(1) == TOKEN_COMMA) {
		Match(TOKEN_COMMA);
		Element();	
	}
}

void ListParser::Element() {
	if (LT(1) == TOKEN_NAME && LT(2) == TOKEN_ASSIGN) {
		Match(TOKEN_NAME);
		Match(TOKEN_ASSIGN);
		Match(TOKEN_NAME);
	} else if (LT(1) == TOKEN_NAME) {
		Match(TOKEN_NAME);	
	} else if (LT(1) == TOKEN_NUMBER) {
		Match(TOKEN_NUMBER);	
	} else if (LT(1) == TOKEN_LSBRACK) {
		List();	
	} else {
		throw ParserUnwantedTokenException(LA(1).name.c_str(), __FILE__, __LINE__);
	}

}


