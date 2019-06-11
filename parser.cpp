#include "parser.h"
#include "my_except.h"

Parser::Parser(Lexer *lexer) : lexer_(lexer) {
	ct_ = lexer_->GetNextToken();
}

Parser::~Parser() {}


void Parser::Match(int token_type) {

	if (token_type == ct_.type) {
		ct_ = lexer_->GetNextToken();	
	} else {
		throw ParserUnwantedTokenException((ct_.name + "given, expect " + lexer_->GetTokenName(token_type)).c_str(), __FILE__, __LINE__);
	}	
}

