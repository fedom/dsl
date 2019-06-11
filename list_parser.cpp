#include "list_parser.h"
#include "list_lexer.h"
#include "my_except.h"

ListParser::ListParser(ListLexer *lexer) : Parser(lexer) {
	
}

ListParser::~ListParser() {

}

void ListParser::Parse() {

	try {
		List();
	
	} catch (const ParserUnwantedTokenException &e) {
		printf("Parse token error: %s\n", e.what());
	}
}


void ListParser::List() {
	if (ct_.type == TOKEN_EOF)
		return;

	Match(TOKEN_LSBRACK);
	Elements();
	Match(TOKEN_RSBRACK);
}

void ListParser::Elements() {
	// empty list
	if (ct_.type == TOKEN_RSBRACK)
		return;

	Element();
	while (ct_.type == TOKEN_COMMA) {
		Match(TOKEN_COMMA);
		Element();	
	}

}

void ListParser::Element() {
	if (ct_.type == TOKEN_NAME) {
		Match(TOKEN_NAME);
	} else if (ct_.type == TOKEN_NUMBER) {
		Match(TOKEN_NUMBER);	
	} else if (ct_.type == TOKEN_LSBRACK) {
		List();	
	} else {
		throw ParserUnwantedTokenException(ct_.name.c_str(), __FILE__, __LINE__);
	}

}


