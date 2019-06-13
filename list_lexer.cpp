#include "list_lexer.h"
#include "my_except.h"

using std::string;

//static 
const char *ListLexer::token_name[] = {
		"<EOF>", "n/a", "NAME", "NUMBER", "LS_BRACK", "RS_BRACK", "COMMA"
};	

ListLexer::ListLexer(const char *s) : Lexer(s) {

}

ListLexer::~ListLexer() {
}

Token ListLexer::GetNextToken() {

	while (c_ != CHAR_EOF) {
	
		if (IsDigit(c_)) {
			return Number();

		} else if (IsLetter(c_)) {
			return Name();

		} else if (IsWhiteSpace(c_)) {
			WS();
			continue;

		} else if (c_ == '[') {
			Consume();
			return Token(TOKEN_LSBRACK, "[");

		} else if (c_ == ']') {
			Consume();
			return Token(TOKEN_RSBRACK, "]");
		
		} else if (c_ == ',') {
			Consume();
			return Token(TOKEN_COMMA, ",");

		} else if (c_ == '=') {
			Consume();
			return Token(TOKEN_ASSIGN, "=");

		} else {
			std::string s;
			s += c_;
			throw InvalidCharException(s.c_str(), __FILE__, __LINE__);
		}
	}
	
	return Token(TOKEN_EOF, "");
}

const char *ListLexer::GetTokenName(int token_type) {
	return token_name[token_type];
}

Token ListLexer::Number() {
	string name;

	while(IsDigit(c_)) {
		name += c_;
		Consume();
	}

	return Token(TOKEN_NUMBER, name);
}

Token ListLexer::Name() {
	string name;
	while (IsLetter(c_)) {
		name += c_;
		Consume();
	}

	return Token(TOKEN_NAME, name);
}
