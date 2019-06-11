#include "lexer.h"

using std::string;

Lexer::Lexer(const char *s) {
	s_ = s;

	// Setting index_ to -1 cause Consume() working properly on init 
	index_ = -1;
	Consume();
}

Lexer::~Lexer() {
}

bool Lexer::IsLetter(char ch) const {
 	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) 
		return true;

	return false;
}

bool Lexer::IsDigit(char ch) const  {
 	if (ch >= '0' && ch <= '9') 
		return true;

	return false;
}

bool Lexer::IsWhiteSpace(char ch) const {
	return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

// Move char ptr forward and update the current letter c_
void Lexer::Consume() {
	++index_;	

	if (index_ >= s_.length()) {
		c_ = CHAR_EOF;
	} else {
		c_ = s_[index_];
	}
}

void Lexer::WS() {
	while(IsWhiteSpace(c_)) 
		Consume();
}
